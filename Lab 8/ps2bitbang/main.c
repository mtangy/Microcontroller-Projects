//-----------------------------------------------------------------------------
// PS/2 Keyboard Bit-Banging Interface
//
// Uses the bit-banging technique to receive PS/2 frames from a PS/2 keyboard
// and decode them to extract the key scan codes sent from the keyboard.
//
// Uses a software state machine to decode the frames and verify that the
// Start, Parity, and Stop bits inside the frame have the correct values.
//
// The bit-banging interface is interrupt-driven and a DigBuf User Module is
// used to generate interrupts on the falling-edge of the PS/2 clock. The
// DigBuf ISR contains the frame decoding state machine which sets a global
// variable to indicate that a valid frame has been decoded and a scan code
// is ready for processing. In addition, a OneShot User Module is used to
// reset the state machine if the PS/2 clock line has remained high for 80us.
// This prevents any glitches on the clock line from causing the state machine
// to incorrectly start processing the glitch as a frame.
//
// Another software state machine is used to decode the keyboard scan codes
// to indicate which keys have been pressed or released.
//
// Raw scan codes read from the keyboard are printed on the LCD display.
//
// Scan codes corresponding to printable ASCII characters are sent to the
// UART for display on a terminal program.
//
// Some non-printable scan codes take specific actions. Examine this program
// for more details.
//
// Hardware Note: The PS/2 Clock and Data lines must both have pull-up
// resistors at the PSoC end in case the device is not attached.
//
// NOTE: Comments with an XXX in them refer to either things to be fixed/changed
//       or items I don't have enough information on.
//
// XXX - Some of the comments, including these in the introduction, have not
//       been updated to reflect that host-to-keyboard communication has been
//       implemented.
//
// Pretty-print this with:
// enscript -r -G -T4 -Ec -fCourier7 main.c
//
// B. Noble - 12 October 2011
//-----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "ps2.h"
#include "keyboard.h"
#include "mouse.h"


//// Common Baud Rates for a 16-bit UART clock with a 24MHz clock source.
#define BAUD_57600_PERIOD	52
#define BAUD_38400_PERIOD	78
#define	BAUD_19200_PERIOD	156
#define	BAUD_9600_PERIOD	312

//// Global Variables (identified by names in LeadingCaps)
BYTE PS2FrameStatus = 0; // Note: This only changes at the end of a complete frame or when the PS2OneShot fires (due to incomplete clock)
BYTE PS2RxBuffer[16]; // Receive buffer. We save only up to 16 unprocessed scan codes.
BYTE PS2RxBufIn = 0; // Index of where we insert bytes in receive buffer
BYTE PS2RxBufOut = 0; // Index of where we read bytes out of the receive buffer
BYTE TenMicroSecTimerReps = 0; // Number of repetitions of the 10-microsecond timer
BYTE NumLock = 0; // 0-NumLock is off, 1-NumLock is on
BYTE CapsLock = 0; // 0-CapsLock is off, 1-CapsLock is on
BYTE ScrollLock = 0; // 0-ScrollLock is off, 1-ScrollLock is on
BYTE ShiftDown = 0; // 0-No Shift keys are pressed, 1-At least one Shift key is pressed
BYTE CtrlDown = 0; // 0-No Ctrl keys are pressed, 1-At least one Ctrl key is pressed
BYTE AltDown = 0; // 0-No Alt keys are pressed, 1-At least one Alt key is pressed
BYTE PianoMode = 0; // 0-The keyboard is in regular mode, 1-The keyboard is in piano mode
BYTE IsMouse = 0; // 0-The device is a keyboard, 1-The devices is a mouse
BYTE DeleteDown = 0; 

//// Port/Shadow Register Control Macros
#define LED1_ON			{LED1_DataShadow |=  LED1_MASK; LED1_Data_ADDR = LED1_DataShadow;}
#define LED1_OFF		{LED1_DataShadow &= ~LED1_MASK; LED1_Data_ADDR = LED1_DataShadow;}
#define LED1_TOGGLE		{LED1_DataShadow ^=  LED1_MASK; LED1_Data_ADDR = LED1_DataShadow;}
#define TRIGGER_HIGH	{TRIGGER_DataShadow |=  TRIGGER_MASK; TRIGGER_Data_ADDR = TRIGGER_DataShadow;}
#define TRIGGER_LOW		{TRIGGER_DataShadow &= ~TRIGGER_MASK; TRIGGER_Data_ADDR = TRIGGER_DataShadow;}
#define TRIGGER_TOGGLE	{TRIGGER_DataShadow ^=  TRIGGER_MASK; TRIGGER_Data_ADDR = TRIGGER_DataShadow;}

void main(void)
{
	char c;					// Generic character variable
	BYTE status = 0;		// Generic status byte
	BYTE cursor = 0;		// LCD cursor position for printing of scan codes
	BYTE codetype = 0;		// Contains the type of keyboard scancode
	BYTE keyspressed = 0;	// Count of the total number of keys currently held down
	BYTE scancode;			// Keyboard scan code to process

	/////////////////////////////////////////////////////////////////////////////////
	// Since we use a shadow register for Port 1, we need to set all bits in it,
	// controlled by StdCPU, to match the state we want them to be in initially.
	// Write a 1 to our PS/2 Clock Out and Data pins which, in Open Drain Low mode,
	// will let the PS/2 bus be pulled high. Also, turn off the Frame Error LED.
	/////////////////////////////////////////////////////////////////////////////////
	PS2CLOCK_HIGH;
	PS2DATA_HIGH;
	LED1_OFF;
	//TRIGGER_HIGH; //// XXX - Diagnostics
	//
	/////////////////////////////////////////////////////////////////////////////////
	// Start the UART clock and the UART
	/////////////////////////////////////////////////////////////////////////////////
	UARTClock_WritePeriod(BAUD_57600_PERIOD-1);
	UARTClock_WriteCompareValue((BAUD_57600_PERIOD>>1)-1);
	UARTClock_Start();
	UART_Start(UART_PARITY_NONE);
	//
	/////////////////////////////////////////////////////////////////////////////////
	// Start the User Modules that will bit-bang the PS/2 frames in from the keyboard
	/////////////////////////////////////////////////////////////////////////////////
	PS2DigBuf_EnableInt();
	PS2DigBuf_Start();
	PS2OneShot_Start();
	TenMicroSecTimer_EnableInt();
	//
	/////////////////////////////////////////////////////////////////////////////////
	// Start the LCD, print an informational message and get it ready to print scan codes
	/////////////////////////////////////////////////////////////////////////////////
	LCD_Start();
	LCD_Position(0,0);	
	LCD_PrCString("PS/2 Bit-Banging");
	LCD_Position(1,0);	// Print the PS/2 keyboard scan codes on the second line.
//	LCD_Control(LCD_CURSOR_WINK);	// Turn on the LCD cursor. See LCD.h.
	LCD_Control(LCD_CURSOR_BLINK);	// Turn on the LCD cursor. See LCD.h.
	//
	/////////////////////////////////////////////////////////////////////////////////
	// Enable Global Interrupts
	// Needed by the PS/2 bit-banging user modules PS2DigBuf and PS2OneShot
	// and TenMicroSecTimer
	/////////////////////////////////////////////////////////////////////////////////
	M8C_EnableGInt;
	//
	/////////////////////////////////////////////////////////////////////////////////
	// Print an informational message out to the host computer via the UART
	/////////////////////////////////////////////////////////////////////////////////
	UART_CPutString("\r\nPSoC PS/2 Bit-Banging Interface test program.\r\n");
	//
	/////////////////////////////////////////////////////////////////////////////////
	// Loop here until we detect a working PS/2 device.
	/////////////////////////////////////////////////////////////////////////////////
	while(1) {
		LCD_Position(1,0);
		LCD_PrCString("Detecting Device");
		status = PS2_Detect_Device();
		if (!status) {
			IsMouse = 0;
			LCD_Position(1,0);
			LCD_PrCString(" Keyboard Ready ");
			break;
		}
		if (status == DEVICE_IS_MOUSE) {
			IsMouse = 1;
			LCD_Position(1,0);
			LCD_PrCString("  Mouse Ready   ");
			break;
		}
		//// No device if the transmission timed-out.
		if (status & DEVICE_TX_TIMEOUT) {
			LCD_Position(1,0);
			LCD_PrCString("   No Device    ");
		}
		//// A framing error occured while transmitting to the device. (XXX - Force test this)
		else if (status & DEVICE_TX_FRAME_ERROR) {
			LCD_Position(1,0);
			LCD_PrCString(" TX Frame Error ");
		}
		//// A framing error occured while receiving from the device. (XXX - Force test this)
		else if (status & DEVICE_RX_FRAME_ERROR) {
			LCD_Position(1,0);
			LCD_PrCString(" RX Frame Error ");
		}
		//// We should probably consider an RX Timeout to be a device error. (XXX - Force test this)
		else if (status & DEVICE_RX_TIMEOUT) {
			LCD_Position(1,0);
			LCD_PrCString("Receive Timeout ");
		}
		//// The response we received from our RESET command was invalid. (XXX - Force test this)
		else if (status & DEVICE_INVALID_RESPONSE) {
			LCD_Position(1,0);
			LCD_PrCString("Invalid Response");
		}
		//// The device failed a diagnostic self-test (BAT) (XXX - Force test this)
		else if (status & DEVICE_BAD_BAT) {
			LCD_Position(1,0);
			LCD_PrCString("Device BAT Error");
		}
		//// We received a partial frame
		else if (status & DEVICE_ERROR) {
			LCD_Position(1,0);
			LCD_PrCString("  Device Error  ");
		}
		//// If we had an error, wait 1 second and try again.
		TenMicroSecTimerReps = 2;
		TenMicroSecTimer_WritePeriod(49999); // 1000ms
		TenMicroSecTimer_Start();
		while(TenMicroSecTimerReps);
		TenMicroSecTimer_Stop();
	}
	//// The device was detected so wait 1 second before clearing the display.
	TenMicroSecTimerReps = 2;
	TenMicroSecTimer_WritePeriod(49999); // 1000ms
	TenMicroSecTimer_Start();
	while(TenMicroSecTimerReps);
	TenMicroSecTimer_Stop();
	//
	//// XXX - Add capability to both the mouse and keyboard functions that,
	////       upon detecting a BAT code from the device, will reinitialize it
	////       and resume operation.
	//
	///////////////////////////////////////////////////////////////////////////
	//// - Mouse stuff below
	///////////////////////////////////////////////////////////////////////////
	// Enter the main loop, printing mouse button and X/Y data to the LCD
	// scan codes out to the UART.
	///////////////////////////////////////////////////////////////////////////
	if (IsMouse) {
		/////////////////////////////////////////////////////////////////////////////////
		// Start the PWM8 User Module that controls the brightness of the LED on P[1]1
		/////////////////////////////////////////////////////////////////////////////////
		PWM8LED_WritePulseWidth(0);
		PWM8LED_Start();
		//
		MouseInit();
//		//// Print the raw 3-byte mouse data to the LCD
//		LCD_Position(1,0);
//		LCD_PrCString("                ");
//		while(1) {
//			MousePrintRawData();
//		}
		//// Move the LCD cursor around the LCD and display data
		LCD_Position(1,0);
		LCD_PrCString("   X:0000 Y:0000");
		while(1) {
			MouseCursor();
		}
	}
	else {
		/////////////////////////////////////////////////////////////////////////////////
		// Start the PWM8 User Module that controls the brightness of the LED on P[1]1
		/////////////////////////////////////////////////////////////////////////////////
		PWM8LED_WritePulseWidth(127);
		PWM8LED_Start();
		//
		//// - Keyboard stuff below
		/////////////////////////////////////////////////////////////////////////////////
		// Enter the main loop, printing received scan codes out on the LCD and printable
		// scan codes out to the UART.
		/////////////////////////////////////////////////////////////////////////////////
		while(1) {
			//// If we get a parity error, regardless of where we are in the
			//// receive buffer, transmit a resend command
			if (PS2FrameStatus & FRAME_RX_PARITY_ERROR) {
				PS2FrameStatus = 0x00;
				PS2_Write_Byte(0xFE);
				continue;
			}
			//// XXX - We should probably check for other frame error types.
			//// XXX - If we get a FRAME_RX_FRAME_ERROR, lets send a resend
			//// XXX - If we get a FRAME_INCOMPLETE, the keyboard may have
			////       been unplugged so send an ECHO. If we don't get a
			////       valid response, reset the keyboard and restart.
			if (PS2RxBufOut != PS2RxBufIn) {
				scancode = PS2RxBuffer[PS2RxBufOut];
				PS2RxBufOut++;
				// Wrap around the circular buffer pointer at 16 
				if (PS2RxBufOut & 0x10) PS2RxBufOut = 0;
				//// Wrap the cursor around on the second line when printing scan codes.
				if (cursor > 15) cursor = 0;
				LCD_Position(1,cursor);
				LCD_PrHexByte(scancode);
				//// Keep the LCD CURSOR on top of the last character written
				LCD_Control(LCD_CURSOR_SH_LEFT);
				cursor+=2;
				//// Process any keyboard commands
				// Getting a 0x00 from the keyboard means there is either a
				// keyboard buffer overrun or a key detection error.
				if (scancode == 0x00) {
					// XXX - Should we indicate to the user that there is a problem?
					continue;
				}
				// If we get a BAT, assume the keyboard has been powered-on
				// again and reset any appropriate state variables.
				// XXX - Maybe we should handle a bad BAT (0xFC) too.
				if (scancode == 0xAA) { // Power-on BAT
					// XXX - Implement the keyboard power-on sequence
					continue;
				}
				// If we find a Resend in our input buffer, ignore it since
				// we handle resends in PS2_Send_Command_Process_Response().
				// Note: This should never happen.
				if (scancode == 0xFE) {
					continue;
				}
				//// Convert the individual scan codes into meaningful key actions
				codetype = KeyboardDecodeData(scancode);
				//// Keep track of how many keys are pressed
				keyspressed = KeyboardTotalPressed(scancode,codetype);
				KeyboardAction(scancode,codetype,keyspressed);
				if (!PianoMode) {
					c = KeyboardToASCII(scancode,codetype);
					if (!c) continue;
					if (c == 0x0d) {
						UART_PutCRLF();
					} 
					if (c == 0x08) {
						// Send rubout
						UART_PutChar(0x08);
						UART_PutChar(' ');
						UART_PutChar(0x08);
					} else {
						UART_PutChar(c);
					}
				}
			}
		}
	}
}


