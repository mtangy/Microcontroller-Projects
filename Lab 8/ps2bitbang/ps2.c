#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "ps2.h"

//// All external global variables (identified by names in LeadingCaps)
extern BYTE PS2FrameStatus; // Note: This only changes at the end of a complete frame or when the PS2OneShot fires (due to incomplete clock)
extern BYTE PS2RxBuffer[16]; // Receive buffer
extern BYTE PS2RxBufIn; // Bytes in receive buffer
extern BYTE PS2RxBufOut; // Bytes in receive buffer
extern BYTE TenMicroSecTimerReps;

//// Global Variables unique to this file (identified by names in LeadingCaps)
static BYTE PS2FrameState = 0;
static BYTE PS2DataIn = 0;
static BYTE PS2DataOut = 0;
static BYTE XXXForceBadRxParity = 0; // XXX - Testing
static BYTE XXXForceBadTxParity = 0; // XXX - Testing

//// State names used in the PS/2 bit-banging state machine implemented
//// in PS2DigBuf_ISR and PS2OneShot_ISR.
#define PS2_START_BIT_IN	0
#define PS2_D0_BIT_IN		1
#define PS2_D1_BIT_IN		2
#define PS2_D2_BIT_IN		3
#define PS2_D3_BIT_IN		4
#define PS2_D4_BIT_IN		5
#define PS2_D5_BIT_IN		6
#define PS2_D6_BIT_IN		7
#define PS2_D7_BIT_IN		8
#define PS2_PARITY_BIT_IN	9
#define PS2_STOP_BIT_IN		10
#define PS2_TRANSMIT_BEGIN	11
#define PS2_D0_BIT_OUT		12
#define PS2_D1_BIT_OUT		13
#define PS2_D2_BIT_OUT		14
#define PS2_D3_BIT_OUT		15
#define PS2_D4_BIT_OUT		16
#define PS2_D5_BIT_OUT		17
#define PS2_D6_BIT_OUT		18
#define PS2_D7_BIT_OUT		19
#define PS2_PARITY_BIT_OUT	20
#define PS2_STOP_BIT_OUT	21
#define PS2_ACK_BIT_IN		22

//-----------------------------------------------------------------------------
// Transmit a byte to the PS/2 device
//
// Returns:
//	0						No error in transmission or reception
//	DEVICE_TX_TIMEOUT		Timeout in transmission waiting for Clock
//	DEVICE_TX_FRAME_ERROR	A TX frame error occured while sending
//	DEVICE_ERROR			The device didn't generate enough clock transitions
//
// XXX - Implement this!
// From http://www.networktechinc.com/ps2-prots.html:
// The system checks for an PS/2 device transmission in process.
// If a transmission is in process and beyond the 10th clock, the
// system must receive the data.
// XXX - Sort-of implemented in the first line of this function.
//-----------------------------------------------------------------------------
BYTE PS2_Write_Byte(BYTE ps2data)
{
	BYTE delay;

	//// If we're receiving something, wait until the transmission is done.
	while(PS2FrameState != PS2_START_BIT_IN);
	//// Copy the byte-to-be-sent to the PS2DataOut global variable used by
	//// the PS/2 communication ISR
	PS2DataOut = ps2data;
	//// XXX - Diagnostics: Make a trigger pulse for the oscilloscope
	//TRIGGER_LOW;
	//delay = 1;
	//while(delay--);
	//TRIGGER_HIGH;
	//
	//// Initialize the state machine to transmit mode.
	PS2FrameState = PS2_TRANSMIT_BEGIN;
	//// Bring the PS/2 Clock line LOW. This will trigger an interrupt
	//// on PS2DigBuf which will advance the state machine to PS2_D0_BIT_OUT.
	PS2CLOCK_LOW;
	//// Hold the clock line LOW for a min/max of 90us/100us total (min 60us)
	//// Set up the timer to let us know when 60us have elapsed.
	//// Note: Timer setup, polling, and ISR can add up to 10us of latency.
	TenMicroSecTimerReps = 1;
	TenMicroSecTimer_WritePeriod(5); // (5+1) * 10us = 60us
	TenMicroSecTimer_Start();
	while(TenMicroSecTimerReps);
	TenMicroSecTimer_Stop();
	//// Bring the PS/2 Data line LOW (note: this is also the Start bit out)
	PS2DATA_LOW;
	//// Set up the timer to let us know when 30us have elapsed.
	//// Note: Timer setup, polling, and ISR can add up to 10us of latency.
	TenMicroSecTimerReps = 1;
	TenMicroSecTimer_WritePeriod(2); // (2+1) * 10us = 30us
	TenMicroSecTimer_Start();
	while(TenMicroSecTimerReps);
	TenMicroSecTimer_Stop();
	//// Bring the clock line HIGH which should cause the device to generate
	//// a clock signal.
	//// Note: Normally, a HIGH level on the Clock line causes the PS2OneShot
	//// to start its relax interval timing, however, interrupts for the
	//// PS2OneShot are only enabled when actively transmitting or receiving.
	PS2CLOCK_HIGH;
	//// Per Adam Chapweske: Wait here for 15ms or until we've transitioned
	//// out of the PS2_D0_BIT_OUT state. If this time is exceeded, it is a
	//// Transmit Timeout.
	TenMicroSecTimerReps = 1;
	TenMicroSecTimer_WritePeriod(1499); // (1499+1) * 10us = 15ms
	TenMicroSecTimer_Start();
	while(TenMicroSecTimerReps&&(PS2FrameState == PS2_D0_BIT_OUT));
	TenMicroSecTimer_Stop();
	//// If we've timed out, without moving from the PS2_D0_BIT_OUT state,
	//// it means the device never sent us a clock signal after our
	//// transmission request. Return a Transmit Timeout Error code.
	if (PS2FrameState == PS2_D0_BIT_OUT) {
		PS2DATA_HIGH; // Since we've timed-out, bring the Data line HIGH again
		PS2FrameState = PS2_START_BIT_IN; // Reset the state machine
		return(DEVICE_TX_TIMEOUT);
	}
	//// We've transitioned out of the PS2_D0_BIT_OUT state so wait until
	//// we return to the PS2_START_BIT_IN state, either because we completed
	//// transmitting a full frame or the PS2OneShot reset us.
	while(PS2FrameState != PS2_START_BIT_IN);
	//// If the transmission was successful, return 0.
	if (PS2FrameStatus & FRAME_BYTE_TRANSMITTED) {
		PS2FrameStatus = 0; // Clear PS2FrameStatus
		return(0);
	}
	//// If the transmission had a frame error, notify the calling function.
	if (PS2FrameStatus & FRAME_TX_FRAME_ERROR) {
		PS2FrameStatus = 0; // Clear PS2FrameStatus
		return(DEVICE_TX_FRAME_ERROR);
	}
	//// The only other condition, FRAME_INCOMPLETE, means device error.
	PS2FrameStatus = 0; // Clear PS2FrameStatus
	return(DEVICE_ERROR);
}

//-----------------------------------------------------------------------------
// Send a command to the PS/2 device and process the device's response.
//
// Returns:
//	0						No error in transmission or reception
//	DEVICE_TX_TIMEOUT		Timeout in transmission waiting for Clock
//	DEVICE_RX_TIMEOUT		No device response to our command
//	DEVICE_TX_FRAME_ERROR	A TX frame error occured while sending
//	DEVICE_RX_FRAME_ERROR	An RX frame error occured while receiving
//	DEVICE_INVALID_RESPONSE	The device response to our command was not valid
//	DEVICE_ERROR			The device didn't generate enough clock transitions
//-----------------------------------------------------------------------------
// From: The AT-PS/2 Keyboard Interface, Copyright 2001, Adam Chapweske:
//
// Every byte sent to the keyboard gets a response of 0xFA ("acknowledge")
// from the keyboard.  The only exceptions to this are the keyboard's response
// to the "Resend" and "Echo" commands.  The host should wait for an
// "acknowledge" before sending the next byte to the keyboard.  The keyboard
// clears its output buffer in response to any command.
//-----------------------------------------------------------------------------
BYTE PS2_Send_Command_Process_Response(BYTE ps2data)
{
	BYTE dataout;
	BYTE txstatus;

	//// Loop in case we get a RESEND response from the PS/2 device.
	//// XXX - Should we put an upper bound on how many Resends we're willing
	//// to do for writing a single byte? (e.g. i=3; while(i--) { ... })
	dataout = ps2data;
	while(1) {
		txstatus = PS2_Write_Byte(dataout);
		//// A non-zero return value means there was an transmission error:
		//// DEVICE_TX_TIMEOUT, DEVICE_TX_FRAME_ERROR, or DEVICE_ERROR
		if (txstatus) {
			return(txstatus);
		}
		///////////////////////////////////////////////////////////////////////
		//// A response should come from the keyboard within 20ms from now.
		TenMicroSecTimerReps = 1;
		TenMicroSecTimer_WritePeriod(1999); // (1999+1) * 10us = 20ms
		TenMicroSecTimer_Start();
		while(TenMicroSecTimerReps&&(!PS2FrameStatus));
		TenMicroSecTimer_Stop();
		//// If the device sent us a response, process it.
		if (PS2FrameStatus & FRAME_DATA_AVAILABLE) {
			//// Clear PS2FrameStatus
			PS2FrameStatus = 0x00;
			//// Remove the response from the RX Buffer
			if (PS2RxBufIn) PS2RxBufIn--; else PS2RxBufIn = 15;
			//// Valid responses: ACK (0xFA), Resend (0xFE), or Echo (0xEE)
			switch(PS2DataIn) {
			case 0xFA: // ACK: The device correctly received our command
				return(0);
			case 0xFE: // RESEND: The device wants us to resend the last byte
				//// Caused by the device getting a parity error.
				//// If we break out of this switch, the while() loop we're in
				//// will resend our command.
				// XXX - Should we keep a count of resend requests received from
				// the device? Should we give up after many back-to-back Resends?
				break;
			case 0xEE: // ECHO: The device responded with an Echo
				//// This should be because we sent it an Echo
				if (ps2data == 0xEE) {
					return(0);
				}
				//// If we received an Echo but didn't send one, it's invalid.
				return(DEVICE_INVALID_RESPONSE);
			//// XXX - What if we get an error code from the device? Can we? 
			////       Test what happens when we send a bogus command.
			//case 0xFC: // ERROR: The device indicated an error
			default:
				LCD_Position(0,14);
				LCD_PrHexByte(PS2DataIn);
				// We should never get here. This can only happen if the
				// device sent us a response to a command that wasn't one
				// of the three listed above.
				return(DEVICE_INVALID_RESPONSE);
			}
		}
		//// If the response frame from the device had a parity error,
		//// send a RESEND command.
		if (PS2FrameStatus & FRAME_RX_PARITY_ERROR) {
			PS2FrameStatus = 0x00; // Clear PS2FrameStatus
			dataout = 0xFE;
			continue;
		}
		//// If we didn't get any change in frame status in response to our
		//// transmission then return a Receive Timeout Error code.
		//// Per Adam Chapweske: Device is probably broken.
		//// XXX - Then should this return DEVICE_ERROR instead?
		////       If so, just change the return() to a break
		if (!PS2FrameStatus) {
			return(DEVICE_RX_TIMEOUT);
		}
		//// If we have an incomplete number of clock transitions in the
		//// response from the device, it is broken or was unplugged.
		if (PS2FrameStatus & FRAME_INCOMPLETE) {
			PS2FrameStatus = 0x00; // Clear PS2FrameStatus
			break;
		}
		//// XXX - What should we do if we get an FRAME_RX_FRAME_ERROR?
		////       The specs aren't clear on what to do with framing errors.
		if (PS2FrameStatus & FRAME_RX_FRAME_ERROR) {
			PS2FrameStatus = 0x00; // Clear PS2FrameStatus
			return(DEVICE_RX_FRAME_ERROR);
		}
	}
	//// If we get here, the device is faulty (incomplete frame).
	PS2FrameStatus = 0x00;
	return(DEVICE_ERROR);
}

//-----------------------------------------------------------------------------
// Determines if a PS/2 keyboard or mouse is present by detecting either the
// Basic Assurance Test (BAT) completion code at power-on or, failing that,
// sending a RESET command to the device and detecting the subsequent BAT code.
// Also waits 20ms after receiving a valid BAT code for the device to send a
// Mouse ID (0x00) code. If this is detected, the function identifies the
// device as a mouse in the return value.
//
//	0						No error in transmission or reception
//	DEVICE_TX_TIMEOUT		Timeout in transmission waiting for Clock
//	DEVICE_RX_TIMEOUT		The device didn't respond to our command
//	DEVICE_TX_FRAME_ERROR	A TX frame error occured while sending
//	DEVICE_RX_FRAME_ERROR	An RX frame error occured while receiving
//	DEVICE_IS_MOUSE			A mouse is detected. If not set, assume keyboard
//	DEVICE_BAD_BAT			Device responded with a bad BAT self-test
//	DEVICE_INVALID_RESPONSE	The device response to our command was not valid
//	DEVICE_ERROR			The device didn't generate enough clock transitions
//-----------------------------------------------------------------------------
BYTE PS2_Detect_Device(void)
{
	BYTE power_on_bat = 0;
	BYTE status;

	///////////////////////////////////////////////////////////////////////////
	// Determine if the device has just powered on, i.e. we receive an 0xAA
	// within 750ms (we'll wait 1000ms).
	///////////////////////////////////////////////////////////////////////////
	//// Set up the timer to let us know when 1000ms has elapsed.
	TenMicroSecTimerReps = 2;
	TenMicroSecTimer_WritePeriod(49999); // 2*((49999+1) * 10us) = 1000ms
	TenMicroSecTimer_Start();
	//// Wait until we either get a change in frame status or the timer elapses
	while(TenMicroSecTimerReps&&(!PS2FrameStatus));
	TenMicroSecTimer_Stop();
	//// If we got a valid frame, check to see if it is a BAT code
	if (PS2FrameStatus & FRAME_DATA_AVAILABLE) {
		PS2FrameStatus = 0x00; // Clear PS2FrameStatus
		if (PS2DataIn == 0xAA) { // Good BAT
			power_on_bat = 1;
			status = 0;
		}
		else if (PS2DataIn == 0xFC) { // Bad BAT
			power_on_bat = 1;
			status = DEVICE_BAD_BAT;
		}
		//// Remove the response from the RX Buffer
		if (PS2RxBufIn) PS2RxBufIn--; else PS2RxBufIn = 15;
	}
	//// If we didn't get a BAT code, got a response that is not a BAT code, or
	//// we got a frame with an error status, send the device a RESET command.
	if (!power_on_bat) {
		status = PS2_Send_Command_Process_Response(0xFF); // Send RESET
		//// If we get an error, exit and return the error type
		if (status) {
			return(status);
		}
		//// Spin until we either get a change in frame status in response to
		//// the RESET/ACK, or 1000ms has elapsed, whichever comes first.
		TenMicroSecTimerReps = 2;
		TenMicroSecTimer_WritePeriod(49999); // 2*((49999+1) * 10us) = 1000ms
		TenMicroSecTimer_Start();
		while(TenMicroSecTimerReps&&(!PS2FrameStatus));
		TenMicroSecTimer_Stop();
		//// If we got a response, determine BAT type
		if (PS2FrameStatus & FRAME_DATA_AVAILABLE) {
			PS2FrameStatus = 0x00; // Clear PS2FrameStatus
			if (PS2DataIn == 0xAA) { // Good BAT
				status = 0;
			}
			else if (PS2DataIn == 0xFC) { // Bad BAT
				status = DEVICE_BAD_BAT;
			}
			else { // Error: Not a BAT code
				LCD_Position(0,12);
				LCD_PrHexByte(PS2DataIn);
				return(DEVICE_INVALID_RESPONSE);
			}
			//// Remove the response from the RX Buffer
			if (PS2RxBufIn) PS2RxBufIn--; else PS2RxBufIn = 15;
		}
		//// If we either didn't receive a BAT code or had any frame error,
		//// return a DEVICE_ERROR to the calling function; it can try again.
		else {
			PS2FrameStatus = 0x00; // Clear PS2FrameStatus
			return(DEVICE_ERROR);
		}
	}
	//// A mouse will send a Mouse ID of 0x00 after the BAT completion code.
	//// We assume this should take no more than 20ms; same as an RX timeout.
	TenMicroSecTimerReps = 1;
	TenMicroSecTimer_WritePeriod(1999); // (1999+1) * 10us = 20ms
	TenMicroSecTimer_Start();
	while(TenMicroSecTimerReps&&(!PS2FrameStatus));
	TenMicroSecTimer_Stop();
	if (!PS2FrameStatus) {
		//// If we didn't receive an additional byte within 20ms after
		//// the BAT code, assume the device is a keyboard
		return(status);
	}
	if (PS2FrameStatus & FRAME_DATA_AVAILABLE) {
		PS2FrameStatus = 0x00; // Clear PS2FrameStatus
		//// Remove the response from the RX Buffer
		if (PS2RxBufIn) PS2RxBufIn--; else PS2RxBufIn = 15;
		//// If we got a byte and it is 0x00, the device is a mouse
		if (PS2DataIn == 0x00) {
			return(status|DEVICE_IS_MOUSE);
		}
		//// If it isn't 0x00, the response isn't valid
		return(DEVICE_INVALID_RESPONSE);
	}
	//// If we had any frame error in the response, return a DEVICE_ERROR
	//// to the calling function; it can try again.
	PS2FrameStatus = 0x00; // Clear PS2FrameStatus
	return(DEVICE_ERROR);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//// Interrupt Service Routines (ISRs) follow
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

#pragma interrupt_handler PS2DigBuf_ISR PS2OneShot_ISR TenMicroSecTimer_ISR

//----------------------------------------------------------------------------------------
// PS/2 Clock ISR
//
// A primary objective in writing this PS/2 bit-banging interface was to make it as general
// as possible so that it could be incorporated into many different designs that could benefit
// from a keyboard (or mouse, for that matter).
//
// The PS/2 protocol says that the data line is valid on the falling-edge of the clock signal.
// While using a falling-edge GPIO interrupt would certainly work, the GPIO ISR would have
// to be shared by any other GPIO interrupts and would require the ISR to determine which
// pin it was supposed to be handling (e.g. optical encoder interrupt or keyboard interrupt).
//
// By passing the PS/2 Clock line into Input 1 of a DigBuf User Module (named PS2DigBuf here),
// and by setting the InvertInput1 parameter to Invert, the DigBuf User Module will call a
// unique ISR whenever the PS/2 clock falling-edge occurs. Inside the ISR, we use a simple
// port pin read operation to get the value of the data line when this occurs.
//
// A simple state machine can verify a valid frame is present, extract the data therein,
// confirm parity is matched, and finally set a global variable indicating a scan code
// was received.
//
// XXX - Update these comments to discuss how this ISR is also used to transmit data.
//
// Global variables used:
//   PS2FrameState - 
//   PS2DataIn      - where this ISR places a reassembled scan code
//   PS2GotFrame   - set to 1 in this ISR when a valid PS2 frame is found
//                   set to 0 by other functions in the program after PS2DataIn is processed
//----------------------------------------------------------------------------------------
void PS2DigBuf_ISR(void)
{
	static BYTE data;	// Note: declaring a variable as static in a function causes the
	static BYTE bit;	// compiler to keep it in RAM and not the stack. This means it
	static BYTE parity;	// retains its value between calls to the function.

	//// Read the PS/2 Data bit every time we enter this ISR
	if (PS2DATA_Data_ADDR & PS2DATA_MASK)
		bit = 0x01;
	else
		bit = 0x00;
	//// Step through the state machine to decode the frame
	switch (PS2FrameState) {
	case PS2_START_BIT_IN: // Start of PS/2 frame
		// Reset the frame status
		PS2FrameStatus = 0x00;
		// Clear the frame data reassembly byte
		data = 0;
		//// If this bit is 0, assume this is the Start bit of the frame and go to the state 1
		if (bit == 0) {
			// Reset our computed parity to 1
			parity = 1;
			// Enable interrupts on the OneShot so that if we don't get enough
			// clock transistions for a valid frame, the OneShot will reset
			// this state machine and report a FRAME_INCOMPLETE error.
			PS2OneShot_ClearInt();
			PS2OneShot_EnableInt();
			// Look for the D0 bit.
			PS2FrameState = PS2_D0_BIT_IN;
		}
		// If this bit is 1, it cannot be the Start bit so remain in this state.
		// Treat it as a glitch and ignore it (don't even bother reporting it).
		break;
	case PS2_D0_BIT_IN: // Get D0
		data|=bit; parity^=bit; PS2FrameState=PS2_D1_BIT_IN; break;
	case PS2_D1_BIT_IN: // Get D1
		data|=bit<<1; parity^=bit; PS2FrameState=PS2_D2_BIT_IN; break;
	case PS2_D2_BIT_IN: // Get D2
		data|=bit<<2; parity^=bit; PS2FrameState=PS2_D3_BIT_IN; break;
	case PS2_D3_BIT_IN: // Get D3
		data|=bit<<3; parity^=bit; PS2FrameState=PS2_D4_BIT_IN; break;
	case PS2_D4_BIT_IN: // Get D4
		data|=bit<<4; parity^=bit; PS2FrameState=PS2_D5_BIT_IN; break;
	case PS2_D5_BIT_IN: // Get D5
		data|=bit<<5; parity^=bit; PS2FrameState=PS2_D6_BIT_IN; break;
	case PS2_D6_BIT_IN: // Get D6
		data|=bit<<6; parity^=bit; PS2FrameState=PS2_D7_BIT_IN; break;
	case PS2_D7_BIT_IN: // Get D7
		data|=bit<<7; parity^=bit; PS2FrameState=PS2_PARITY_BIT_IN; break;
	case PS2_PARITY_BIT_IN: // Get parity. ODD:parity=0, EVEN:parity=1
		parity^=bit; PS2FrameState=PS2_STOP_BIT_IN; break;
//		//// XXX - Force a bad receive parity bit periodically for testing.
//		if (XXXForceBadRxParity++ > 3) { // bad parity every N+1 transmissions
//			XXXForceBadRxParity = 0;
//			parity = 1;
//		}
//		PS2FrameState=PS2_STOP_BIT_IN;
//		break;
	case PS2_STOP_BIT_IN: // Check the Stop bit
		//// If Stop bit is 0, this is a framing error
		//// Note: A frame error overrides a parity error
		//// XXX - Unresolved issue: If the Stop bit is wrong, did we really
		////       get a complete frame? Until I learn more, I'm going to
		////       report we've had an RX framing error.
		////       Should the application request a retransmission if it
		////       get's a frame error? I don't know.
		if (bit == 0) {
			PS2FrameStatus = FRAME_RX_FRAME_ERROR;
		}
		else {
			//// The Stop bit is 1, so the frame is valid. Check the parity.
			if (parity) {
				PS2FrameStatus = FRAME_RX_PARITY_ERROR;
			}
			else {
				PS2DataIn = data;
				PS2FrameStatus = FRAME_DATA_AVAILABLE;
				PS2RxBuffer[PS2RxBufIn] = data;
				PS2RxBufIn++;
				// Wrap around the circular buffer pointer at 16
				if (PS2RxBufIn & 0x10) PS2RxBufIn = 0;
			}
		}
		//// We got a complete frame so reset the state and disable PS2OneShot.
		PS2FrameState = PS2_START_BIT_IN;
		PS2OneShot_DisableInt();
		break;
	///////////////////////////////////////////////////////////////////////////
	//////// States used to send data to keyboard
	///////////////////////////////////////////////////////////////////////////
	case PS2_TRANSMIT_BEGIN:
		// Reset the frame status
		PS2FrameStatus = 0x00;
		PS2FrameState=PS2_D0_BIT_OUT;
		break;
	case PS2_D0_BIT_OUT:
		// Send the D0 bit and initialize parity
		if (PS2DataOut&0x01) { parity = 0; PS2DATA_HIGH; }
		else { parity = 1; PS2DATA_LOW; }
		// Enable interrupts on the OneShot so that if we don't get enough
		// clock transistions for a valid frame, the OneShot will reset
		// this state machine and report a FRAME_INCOMPLETE error.
		PS2OneShot_ClearInt();
		PS2OneShot_EnableInt();
		PS2FrameState=PS2_D1_BIT_OUT;
		break;
	case PS2_D1_BIT_OUT:
		if (PS2DataOut&0x02) { parity ^= 0x01; PS2DATA_HIGH; }
		else { PS2DATA_LOW; }
		PS2FrameState=PS2_D2_BIT_OUT;
		break;
	case PS2_D2_BIT_OUT:
		if (PS2DataOut&0x04) { parity ^= 0x01; PS2DATA_HIGH; }
		else { PS2DATA_LOW;	}
		PS2FrameState=PS2_D3_BIT_OUT;
		break;
	case PS2_D3_BIT_OUT:
		if (PS2DataOut&0x08) { parity ^= 0x01; PS2DATA_HIGH; }
		else { PS2DATA_LOW; }
		PS2FrameState=PS2_D4_BIT_OUT;
		break;
	case PS2_D4_BIT_OUT:
		if (PS2DataOut&0x10) { parity ^= 0x01; PS2DATA_HIGH; }
		else { PS2DATA_LOW; }
		PS2FrameState=PS2_D5_BIT_OUT;
		break;
	case PS2_D5_BIT_OUT:
		if (PS2DataOut&0x20) { parity ^= 0x01; PS2DATA_HIGH; }
		else { PS2DATA_LOW; }
		PS2FrameState=PS2_D6_BIT_OUT;
		break;
	case PS2_D6_BIT_OUT:
		if (PS2DataOut&0x40) { parity ^= 0x01; PS2DATA_HIGH; }
		else { PS2DATA_LOW; }
		PS2FrameState=PS2_D7_BIT_OUT;
		break;
	case PS2_D7_BIT_OUT:
		if (PS2DataOut&0x80) { parity ^= 0x01; PS2DATA_HIGH; }
		else { PS2DATA_LOW; }
		PS2FrameState=PS2_PARITY_BIT_OUT;
		break;
	case PS2_PARITY_BIT_OUT:
		if (parity) { PS2DATA_HIGH; }
		else { PS2DATA_LOW; }
		PS2FrameState=PS2_STOP_BIT_OUT;
		break;
//		//// XXX - Force a bad transmit parity bit periodically for testing
//		if (XXXForceBadTxParity++ > 3) { // Bad parity every N+1 transmissions
//			XXXForceBadTxParity=0;
//			if (parity) {
//				PS2DATA_LOW;
//			}
//			else {
//				PS2DATA_HIGH;
//			}
//			PS2FrameState=PS2_STOP_BIT_OUT;
//			break;
//		}
	case PS2_STOP_BIT_OUT:
		//// Release the Data Line to make the Stop bit
		PS2DATA_HIGH;
		PS2FrameState=PS2_ACK_BIT_IN;
		break;
	case PS2_ACK_BIT_IN:
		if (bit == 0) {
			PS2FrameStatus = FRAME_BYTE_TRANSMITTED;
		}
		//// XXX - I can't find what we should do if we get a bad ACK bit so
		////       I'm declaring a Frame Error.
		else {
			// If we don't get a valid ACK bit, this is a transmission frame error
			PS2FrameStatus = FRAME_TX_FRAME_ERROR;
		}
		//// We sent a complete frame so reset the state and disable PS2OneShot.
		PS2FrameState = PS2_START_BIT_IN;
		PS2OneShot_DisableInt();
		break;
	default: // We should never, ever, get here.
		// XXX - So should we delete it after we're done developing the code?
		break;
	}
	return;
}

//----------------------------------------------------------------------------------------
// PS/2 Bit-Banging State Machine Reset
//
// Since it is possible that a glitch can appear on the PS/2 Clock line to the PSoC
// and cause the state machine to believe it is receiving data from the PS/2 interface,
// a OneShot User Module (named PS2OneShot here) is used to reset the state machine
//
// PS/2 specifications say that acceptable clock frequencies range from 10kHz to 16kHz
// (i.e. clock periods range from 100us to 62.5us).
//
// In this design an 8-bit OneShot User Module is configured with a clock source of VC3
// with the VC3 source of SysClk/1 and divider of 240. This clocks the OneShot at a rate
// of 100kHz. Upon detecting the falling-edge of the PS/2 clock, the OneShot becomes
// active. The OneShot will not generate an interrupt until the PS/2 clock line remains
// high (i.e. PS/2 clock is idle) for 8/100kHz = 80us. This is sufficient time for the
// state machine to read the Stop bit from a valid PS/2 frame before this OneShot ISR
// resets the state machine. One the other hand, if the clock line glitched and the
// state machine was started, this ISR will reset the state machine instead of leaving
// it (incorrectly) in an intermediate state when a valid frame arrives.
//
// XXX - Update these comments to reflect the new behavior of only calling
//       this ISR if we don't get a complete frame.
//----------------------------------------------------------------------------------------
void PS2OneShot_ISR(void)
{
	// Make sure the PS/2 Data line is HIGH (undriven) by the PSoC in case the
	// transmission of a frame was interrupted while it was held LOW.
	// Note: We don't need to make the PS/2 Clock line HIGH since, it something else
	// is driving it LOW, this ISR will never be called since the OneShot will be
	// held in its active state.
	PS2DATA_HIGH;
	//// Reset the frame state machine
	if (PS2FrameState != PS2_START_BIT_IN) {
		PS2FrameStatus = FRAME_INCOMPLETE;
		PS2FrameState = PS2_START_BIT_IN;
	}
	return;
}

//----------------------------------------------------------------------------------------
// Ten Micro Second Timer Interrupt Service Routine
//----------------------------------------------------------------------------------------
void TenMicroSecTimer_ISR(void)
{
	TenMicroSecTimerReps--;
	return;
}