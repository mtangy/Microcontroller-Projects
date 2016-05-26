//----------------------------------------------------------------------------
// XXX - Create the comments for this.
//
// B. Noble - 18 October 2010
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "ps2.h"
#include "keyboard.h"

//// State names used in the KeyboardDecodeData() function
#define KBD_START_SEQ	0
#define KBD_BREAK_SEQ	1
#define KBD_E0_SEQ		2
#define	KBD_E0_F0_SEQ	3
#define KBD_PAUSE_A		4
#define KBD_PAUSE_B		5
#define	KBD_PAUSE_C		6
#define KBD_PAUSE_D		7

//// All external global variables (identified by names in LeadingCaps)
extern BYTE NumLock;
extern BYTE CapsLock;
extern BYTE ScrollLock;
extern BYTE ShiftDown;
extern BYTE CtrlDown;
extern BYTE AltDown;
extern BYTE PianoMode;
extern BYTE DeleteDown;
extern const unsigned char LEDBrightness[];

//----------------------------------------------------------------------------
// PS/2 Keyboard Scan Code Mapping Arrays
//
// NOTE: by making theses arrays constant (const) the compiler will place
// them in the PSoC's EEPROM so we don't waste RAM space on things that
// won't be changing.
//
// B. Noble - 18 October 2010
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Scan Code to printable ASCII mapping
//
// Defines an array variable that maps all single-byte scan codes to their
// respective ASCII values.
//
// The 1st column is the the scan code value.
// The 2nd column gives the ASCII scan code value with Shift pressed.
// The 3rd column gives the ASCII scan code value without Shift pressed.
//----------------------------------------------------------------------------
unsigned char const ShiftableScancode[ ][3] = {
	'`',	'~',	0x0E,
	'1',	'!',	0x16,
	'2',	'@',	0x1E,
	'3',	'#',	0x26,
	'4',	'$',	0x25,
	'5',	'%',	0x2E,
	'6',	'^',	0x36,
	'7',	'&',	0x3D,
	'8',	'*',	0x3E,
	'9',	'(',	0x46,
	'0',	')',	0x45,
	'-',	'_',	0x4E,
	'=',	'+',	0X55,
	'[',	'{',	0x54,
	']',	'}',	0x5B,
	'\\',	'|',	0x5D,
	';',	':',	0x4C,
	'\'',	'\"',	0x52,
	',',	'<',	0x41,
	'.',	'>',	0x49,
	'/',	'?',	0x4A,
	' ',	' ',	0x29, // Space
	0x09,	0x09,	0x0D, // Tab
	0x00,	0x00,	0x00  // Indicates end of this array while searching
};

//----------------------------------------------------------------------------
// Scan Code to printable alphabet ASCII mapping
//
// Defines an array variable that maps all single-byte scan codes to their
// respective ASCII values.
//
// The 1st column is the the scan code value.
// The 2nd column gives the ASCII scan code value with Shift pressed.
// The 3rd column gives the ASCII scan code value without Shift pressed.
//----------------------------------------------------------------------------
unsigned char const AlphabetScancode[ ][3] = {
	'a',	'A',	0x1C,
	'b',	'B',	0x32,
	'c',	'C',	0x21,
	'd',	'D',	0x23,
	'e',	'E',	0x24,
	'f',	'F',	0x2B,
	'g',	'G',	0x34,
	'h',	'H',	0x33,
	'i',	'I',	0x43,
	'j',	'J',	0x3B,
	'k',	'K',	0x42,
	'l',	'L',	0x4B,
	'm',	'M',	0x3A,
	'n',	'N',	0x31,
	'o',	'O',	0x44,
	'p',	'P',	0x4D,
	'q',	'Q',	0x15,
	'r',	'R',	0x2D,
	's',	'S',	0x1B,
	't',	'T',	0x2C,
	'u',	'U',	0x3C,
	'v',	'V',	0x2A,
	'w',	'W',	0x1D,
	'x',	'X',	0x22,
	'y',	'Y',	0x35,
	'z',	'Z',	0x1A,
	0x00,	0x00,	0x00  // Indicates end of this array while searching
};

//----------------------------------------------------------------------------
// Scan Code to control character ASCII mapping
//
// Defines an array variable that maps all single-byte scan codes to their
// respective ASCII values.
//
// The 1st column is the the scan code value.
// The 2nd column gives the ASCII scan code value with Shift pressed.
// The 3rd column gives the ASCII scan code value without Shift pressed.
//----------------------------------------------------------------------------
unsigned char const ControlScancode[ ][2] = {
	0x01,	0x1C, // ^A, SOH
	0x02,	0x32, // ^B, STX
	0x03,	0x21, // ^C, ETX
	0x04,	0x23, // ^D, EOT
	0x05,	0x24, // ^E, ENQ
	0x06,	0x2B, // ^F, ACK
	0x07,	0x34, // ^G, BEL
	0x08,	0x33, // ^H, BS
	0x09,	0x43, // ^I, HT
	0x0A,	0x3B, // ^J, NL
	0x0B,	0x42, // ^K, VT
	0x0C,	0x4B, // ^L, NP
	0x0D,	0x3A, // ^M, CR
	0x0E,	0x31, // ^N, SO
	0x0F,	0x44, // ^O, SI
	0x10,	0x4D, // ^P, DLE
	0x11,	0x15, // ^Q, DC1
	0x12,	0x2D, // ^R, DC2
	0x13,	0x1B, // ^S, DC3
	0x14,	0x2C, // ^T, DC4
	0x15,	0x3C, // ^U, NAK
	0x16,	0x2A, // ^V, SYN
	0x17,	0x1D, // ^W, ETB
	0x18,	0x22, // ^X, CAN
	0x19,	0x35, // ^Y, EM
	0x1A,	0x1A, // ^Z, SUB
	0x1B,	0x54, // ^[, ESC
	0x1C,	0x5D, // ^\, FS
	0x1D,	0x5B, // ^], GS
	0x1E,	0x36, // ^^, RS
	0x1F,	0x4E, // ^_, US
	0x00,	0x00  // Indicates end of this array while searching
};

//----------------------------------------------------------------------------
// Scan Code to control character ASCII mapping
//
// Defines an array variable that maps all single-byte scan codes to their
// respective ASCII values.
//
// The 1st column is the the scan code value.
// The 2nd column gives the ASCII scan code value with Shift pressed.
//----------------------------------------------------------------------------
unsigned char const KeypadScancode[ ][2] = {
	'0',	0x70,
	'1',	0x69,
	'2',	0x72,
	'3',	0x7A,
	'4',	0x6B,
	'5',	0x73,
	'6',	0x74,
	'7',	0x6C,
	'8',	0x75,
	'9',	0x7D,
	'.',	0x71,
	0x00,	0x00  // Indicates end of this array while searching
};

//----------------------------------------------------------------------------
// Scan Code to 3-octave diatonic musical scale.
//
// Defines an array variable that maps all single-byte scan codes to their
// respective period and pulse widths for a 16-bit PWM User Module utilizing
// an 8MHz clock .
//
// The 1st column is the the scan code value.
// The 2nd column gives the 16-bit PWM Period.
// The 3rd column gives the 16-bit PWM Pulse Width.
//----------------------------------------------------------------------------
unsigned int const PianoScancode[ ][3] = {
	//// Lower Octave
	0x1A,	61155,	30577,	// 'z' C3 Low C
	0x22,	54483,	27241,	// 'x' D3
	0x21,	48539,	24269,	// 'c' E3
	0x2A,	45814,	22907,	// 'v' F3
	0x32,	40816,	20407,	// 'b' G3
	0x31,	36363,	18181,	// 'n' A3
	0x3A,	32395,	16197,	// 'm' B3
	0x41,	30577,	15288,	// ',' C4 Middle C
	//// Middle Octave
	0x1C,	30577,	15288,	// 'a' C4 Middle C
	0x1B,	27241,	13620,	// 's' D4
	0x23,	24269,	12134,	// 'd' E4
	0x2B,	22907,	11453,	// 'f' F4
	0x34,	20407,	10203,	// 'g' G4
	0x33,	18181,	9090,	// 'h' A4
	0x3B,	16197,	8098,	// 'j' B4
	0x42,	15288,	7644,	// 'k' C5 Tenor C
	//// Tenor Octave
	0x15,	15288,	7644,	// 'q' C5 Tenor C
	0x1D,	13620,	6809,	// 'w' D5
	0x24,	12134,	6066,	// 'e' E5
	0x2D,	11453,	5726,	// 'r' F5
	0x2C,	10203,	5101,	// 't' G5
	0x35,	9090,	4544,	// 'y' A5
	0x3C,	8098,	4049,	// 'u' B5
	0x43,	7644,	3821,	// 'i' C6 Soprano C
	//// End of array
	0x00,	0x00,	0x00	// Indicates end of this array while searching
};

//-----------------------------------------------------------------------------
// Software state machine to decode the PS/2 keyboard scan codes into
// meaningful actions. See the state diagram in the lab description.
//
// XXX - The shift keys have a special response when they are held down
//       and one of the "gray" (Insert, Delete, Pg Up, Pg Dn, Home, End, etc.)
//       keys are pressed.
//       As soon as a gray key is pressed, the shift key pressed gets an E0F0 break
//       sequence, followed by the gray key (autorepeated if necessary).
//       When the gray key is released, the keyboard generates an E0 followed
//       by the scancode for the shift key still down.
//       Example: This is what happens when Left Shift then Page Down
//       are pressed, followed by Page Down and then Left Shift being released
//       12 E0 F0 12 E0 7A E0 F0 7A E0 12 F0 12
//       Note: This behavior is only true when Num Lock LED is off.
//       When Num Lock LED is on, they Shift Key behaves normally.
//
// XXX - Document PRNT_SCRN's weirdness: PRNT_SCRN's sequence "E0 12" only occurs if no other key is pressed
// PRNT_SCRN's sequence "E0 F0 12" occurs either at the end of the
// PRNT_SCRN sequence if there were no other keys pressed -OR- if
// another key was pressed while PRNT_SCRN was held down.
// PRNT_SCRN's "E0 12" is basically a fake-shift
//
// Note: This function assumes all keyboard-to-host commands have been handled!
//-----------------------------------------------------------------------------
BYTE KeyboardDecodeData(BYTE scancode)
{
	static BYTE state = 0;
	BYTE codetype = 0;
	
	switch(state) {
	case KBD_START_SEQ:
		if (scancode == 0xF0) {
			state = KBD_BREAK_SEQ;
			break;
		}
		if (scancode == 0xE0) {
			state = KBD_E0_SEQ;
			break;
		}
		if (scancode == 0xE1) {
			state = KBD_PAUSE_A;
			break;
		}
		codetype = KEY_MAKE;
		break;
	case KBD_BREAK_SEQ:
		state = KBD_START_SEQ;
		codetype = KEY_BREAK;
		break;
	case KBD_E0_SEQ:
		if (scancode == 0xF0) {
			state = KBD_E0_F0_SEQ;
			break;
		}
		state = KBD_START_SEQ;
		// See if this is a fake-shift MAKE.
		if ((scancode == 0x12)||(scancode == 0x59)) {
				codetype = KEY_FAKE_SHIFT|KEY_MAKE;
				break;
		}
		codetype = KEY_E0|KEY_MAKE;
		break;
	case KBD_E0_F0_SEQ:
		state = KBD_START_SEQ;
		// See if this is a fake-shift BREAK.
		if ((scancode == 0x12)||(scancode == 0x59)) {
			codetype = KEY_FAKE_SHIFT|KEY_BREAK;
			break;
		}
		codetype = KEY_E0|KEY_BREAK;
		break;
	case KBD_PAUSE_A:
		if (scancode == 0x14) {
			state = KBD_PAUSE_B;
			break;
		}
		if (scancode == 0xF0) {
			state = KBD_PAUSE_D;
			break;
		}
		state = KBD_START_SEQ;
		break;
	case KBD_PAUSE_B:
		if (scancode == 0x77) {
			state = KBD_PAUSE_C;
			break;
		}
		if (scancode == 0xF0) {
			state = KBD_PAUSE_D;
			break;
		}
		state = KBD_START_SEQ;
		break;
	case KBD_PAUSE_C:
		if (scancode == 0xE1) {
			state = KBD_PAUSE_A;
			break;
		}
		state = KBD_START_SEQ;
		break;
	case KBD_PAUSE_D:
		if (scancode == 0x14) {
			state = KBD_PAUSE_B;
			break;
		}
		if (scancode == 0x77) {
			codetype = KEY_PAUSE;
		}
		state = KBD_START_SEQ;
		break;
	}
	return(codetype);
}

BYTE KeyboardTotalPressed(BYTE scancode, BYTE codetype)
{
	static BYTE keys[12];
	static BYTE types[12];
	static BYTE pressed = 0;
	BYTE i,j;
	BYTE found=0;

	//// If this is a fake-shift it is not an actual key change.
	if (codetype & KEY_FAKE_SHIFT) {
		return(pressed);
	}
	//// If this is the Pause key, it won't change the number of keys held down.
	if (codetype & KEY_PAUSE) {
		return(pressed);
	}
	//// If this is a key-make, check if it is on the list and add it if not.
	if (codetype & KEY_MAKE) {
		if (pressed == 0) {
			keys[pressed] = scancode;
			types[pressed] = codetype & KEY_E0;
			pressed = 1;
		}
		else {
			found = 0;
			for (i=0 ; i<pressed ; i++) {
				if (keys[i] == scancode) {
					if (types[i] == (codetype & KEY_E0)) {
						found=1;
					}
				}
			}
			if (found==0) {
				keys[pressed] = scancode;
				types[pressed] = codetype & KEY_E0;
				pressed++;
			}
		}
	}
	//// If this is a key-break:
	//// "pressed" should never be zero when we receive a KEY_BREAK
	//// but, since some keyboards may have debouncing problems which
	//// can generate multiple breaks, we will check anyway.
	if (codetype & KEY_BREAK) {
		if (!pressed) {
			return(0);
		}
		// Remove the key from the list
		for (i=0,j=0 ; i<pressed ; i++) {
			// if the key & type matches, skip it
			if (keys[i] == scancode) {
				if (types[i] == (codetype & KEY_E0)) {
					continue;
				}
			}
			keys[j]=keys[i];
			types[j]=types[i];
			j++;
		}
		pressed = j;
	}
	///////////////////////////////////////////////////////////////////////////
	return(pressed);
}

char KeyboardToASCII(BYTE scancode, BYTE codetype)
{
	int i;
	
	static int print1 = 0;                                                                      // we added this
	static int count = 0;																		// we added this
	static int print2 = 0;																	    // we added this
	static int rst = 0;

	//// Ignore fake-shifts
	if (codetype & KEY_FAKE_SHIFT) {
		return(0);
	}
	if (codetype & KEY_MAKE) {
		//// Convert any two byte (E0) scancodes to their ASCII equivalent
		if (codetype & KEY_E0 && AltDown != 1 && CtrlDown != 1) {
			if (scancode == 0x71) {
				return(0x08);	// Delete (return backspace)
			}
			if (scancode == 0x4A) return('/');	// Keypad /
			if (scancode == 0x5A) { // Keypad Enter
				if (CtrlDown) return(0x0A);	// ^Enter (return line-feed)
				else return(0x0D); // (return carriage-return)
			}
		}
		//// Convert any single byte scancodes to their ASCII equivalent
		else {
			//// Check for special case keys
			if (scancode == 0x5A) { // Enter
				if (CtrlDown) return(0x0A);	// ^Enter (return line-feed)
				else return(0x0D); // (return carriage-return)
			}
			if (scancode == 0x76) return(0x1B);	// ESC key returns ASCII ESC
			if (scancode == 0x7C) return('*');	// KP *
			if (scancode == 0x7B) return('-');	// KP -
			if (scancode == 0x79) return('+');	// KP +
			if (scancode == 0x66) return(0x08); // Backspace (return delete)                       ***We added this***
			//// If one of the Control keys is down, return their ASCII value
			/// 
			
			if (CtrlDown) {
				i = 0;
				while((ControlScancode[i][1] != scancode) && (ControlScancode[i][1] != 0)) {
					i++;
				}
				if (ControlScancode[i][1] > 0) {
					return(ControlScancode[i][0]);
				}
				
				if (AltDown && DeleteDown) {
					
					M8C_Reset;
					
				}
				
//				if (scancode == 0x11) {
//					rst = 1;	w
//				} else if (rst == 1) {
//					UART_CPutString("\r\nSoft Reset\r\n");
//				}
			}
			//// If NumLock is on, return any appropriate key pad ASCII values
			if (NumLock) {
				i = 0;
				while((KeypadScancode[i][1] != scancode) && (KeypadScancode[i][1] != 0)) {
					i++;
				}
				if (KeypadScancode[i][1] > 0) {
					return(KeypadScancode[i][0]);
				}
			}
			
			/* CODE ADDED BY JEREMY AND DAVE      ************************************/
			/************* DON'T BREAK IT ********************************************/
			if (AltDown) {
				
				// FOX PART
				
				if (scancode == 0x16) {
					print1 = 1;
				} else if (scancode == 0x1E && print1 == 1) {
					print1 = 2;
				} else if (scancode == 0x26 && print1 == 2) {
					UART_CPutString("\r\nThe quick brown fox jumps over the lazy dog.\r\n");				// we added this section
					print1 = 0;
				} else if (scancode != 0xF0 && scancode != 0x11) {
					print1 = 0;
				}
				
				// PI PART
				if (scancode == 0x26) {
					print2 = 1;
				} else if (scancode == 0x16 && print2 == 1) {
					print2 =2 ;
				} else if (scancode == 0x25 && print2 == 2) {
					UART_CPutString("\r\n3.1415926535897932386\r\n");
					print2 = 0;
				} else if (scancode != 0xF0 && scancode != 0xF0) {
					print2 = 0;
				}
				
				// THREE ZEROS PART
				if (scancode == 0x45) {
					count++;
					if (count == 3) {
						UART_CPutString("\r\nI love/hate ECE381!.\r\n");	
						count = 0;
					}
				} else if (scancode != 0xF0 && scancode != 0x11) {
					count = 0;
				}
			}
			
			/* END OF CODE ADDED BY JEREMY AND DAVE **********************************/
			/*************************************************************************/
			
			
			//// Keypad ./DEL returns backspace if NumLock is off
			else {
				if (scancode == 0x71) return(0x08);	// KP ./Del (return backspace)
			}
			//// Search for all others in their shifted or CapsLock form
			i = 0;
			while((AlphabetScancode[i][2] != scancode) && (AlphabetScancode[i][2] != 0)) {
				i++;
			}
			if (AlphabetScancode[i][2] > 0) {
				return(AlphabetScancode[i][ShiftDown^CapsLock]);
			}
			else {
				i = 0;
				while((ShiftableScancode[i][2] != scancode) && (ShiftableScancode[i][2] != 0)) {
					i++;
				}
				if (ShiftableScancode[i][2] > 0) {
					return(ShiftableScancode[i][ShiftDown]);
				}
			}
		}
	}
	//// No ASCII match returns zero
	return(0);
}

void KeyboardAction(BYTE scancode, BYTE codetype, BYTE keyspressed)
{
	//// Keyboard variables below
	BYTE status;
	int i;
	static BYTE brightindex = 127;	// PWM LED brightness index
	static BYTE pwm_on = 1;		// PWM User Module on or off
	static BYTE statusLEDs=0;
	static BYTE shiftstatus = 0;
	static BYTE ctrlstatus = 0;
	static BYTE altstatus = 0;
	static BYTE ctrlaltdelete = 0;
	static BYTE delstatus = 0;
	
	static int keycounthigh = 0;    																// we added this
	static int keycountmid = 0;    																// we added this
	static int keycountlow = 0;    																// we added this
	static BYTE lows[] = {0x0, 0x0}; 																		// we added this
	static BYTE mids[] = {0x0, 0x0}; 																		// we added this
	static BYTE highs[] = {0x0, 0x0}; 																		// we added this
	static int m = 0;
	static int n = 0;
	static int o = 0;
	

	//// Ignore fake-shifts (unless you care about them)
	if (codetype & KEY_FAKE_SHIFT) {
		return;
	}
	//// Every other code type is a key change
	if (codetype) {
		//// If the Pause key is pressed, switch to Piano mode
		if (codetype == KEY_PAUSE) {
			PianoMode ^= 0x01;
			if (PianoMode) {
				UART_CPutString("\r\nPiano mode on.\r\n");
				UART_CPutString("\tPress [ZXCVBNM,], [ASDFGHJK], or [QWERTYUI].\r\n");
			}
			else
				UART_CPutString("\r\nPiano mode off.\r\n");
			return;
		}
		//// Things to do when one of the E0 keys is pressed
		if ((codetype & KEY_E0)&&(codetype & KEY_MAKE)) {
			switch(scancode) {
			case 0x7C:	// E0 7C - PRNT SCRN
				// If we successfully send and receive an echo, toggle the PWM LED
				if (!PS2_Send_Command_Process_Response(0xEE)) {
					if (pwm_on) {
						pwm_on = 0;
						PWM8LED_Stop();
					}
					else {
						pwm_on = 1;
						PWM8LED_Start();
					}
				}
				break;
			case 0x14:	// E0 14 - Right Control
				ctrlstatus |= 0x01;
				CtrlDown = 1;
				break;
			case 0x11:	// E0 11 - Right Alt
				altstatus |= 0x01;
				AltDown = 1;
				break;
			case 0x71:  // E0 71 - Delete 
				delstatus |= 0x01;
					//UART_CPutString("\r\nDELETE DELETE DELETE\r\n");
				DeleteDown = 1;
				break;
			//// Any scan codes not handled specially in the above case statements are
			//// handled here:
			default:
				break;
			}
			return;
		}
		//
		//// Things to do when one of the E0 keys is released
		if ((codetype & KEY_E0)&&(codetype & KEY_BREAK)) {
			switch(scancode) {
			case 0x7C:	// E0 F0 7C - PRNT SCRN
				break;
			case 0x14:	// E0 F0 14 - Right Control
				ctrlstatus &= ~0x01;
				if (!ctrlstatus) CtrlDown = 0;
				break;
			case 0x11:	// E0 F0 11 - Right Alt
				altstatus &= ~0x01;
				if (!altstatus) AltDown = 0;
				break;
			case 0x71:
				DeleteDown = 0;
					//UART_CPutString("\r\nSTOP DELETING \r\n");
				break;
					
			//// Any scan codes not handled specially in the above case statements are
			//// handled here:
			default:
				break;
			}
			return;
		}
		//
		//// Things to do when one of the single byte "make" scan code keys is pressed
		if (codetype & KEY_MAKE) {
			switch(scancode) {
			case 0x59:	// Right Shift
				shiftstatus |= 0x01;
				ShiftDown = 1;
				break;
			case 0x12:	// Left Shift
				shiftstatus |= 0x02;
				ShiftDown = 1;
				break;
			case 0x14:	// Left Control
				ctrlstatus |= 0x02;
				CtrlDown = 1;
				break;
			case 0x11:	// Left Alt
				altstatus |= 0x02;
				AltDown = 1;
				break;
			case 0x77:	// Num Lock
				NumLock ^= 0x01;
				if (NumLock) {
					status = PS2_Send_Command_Process_Response(0xED);
					if (!status) {
						statusLEDs |= 0x02;
						status = PS2_Send_Command_Process_Response(statusLEDs);
					}
				}
				else {
					status = PS2_Send_Command_Process_Response(0xED);
					if (!status) {
						statusLEDs &= ~0x02;
						status = PS2_Send_Command_Process_Response(statusLEDs);
					}
				}
				break;
			case 0x58:	// Caps Lock
				//// Send to the keyboard
				CapsLock ^= 0x01;
				if (CapsLock) {
					status = PS2_Send_Command_Process_Response(0xED);
					if (!status) {
						statusLEDs |= 0x04;
						status = PS2_Send_Command_Process_Response(statusLEDs);
					}
				}
				else {
					status = PS2_Send_Command_Process_Response(0xED);
					if (!status) {
						statusLEDs &= ~0x04;
						status = PS2_Send_Command_Process_Response(statusLEDs);
					}
				}
				break;
			case 0x7E:	// Scroll Lock
				//// Send to the keyboard
				ScrollLock ^= 0x01;
				if (ScrollLock) {
					status = PS2_Send_Command_Process_Response(0xED);
					if (!status) {
						statusLEDs |= 0x01;
						status = PS2_Send_Command_Process_Response(statusLEDs);
					}
				}
				else {
					status = PS2_Send_Command_Process_Response(0xED);
					if (!status) {
						statusLEDs &= ~0x01;
						status = PS2_Send_Command_Process_Response(statusLEDs);
					}
				}
				break;
			case 0x05:	// F1 - Dim the LED
				if (brightindex > 31) {
					brightindex -= 32;
					PWM8LED_WritePulseWidth(brightindex);
				}
				else if (brightindex == 31){
					brightindex -= 31;
					PWM8LED_Stop();
				}
				break;
			case 0x06:	// F2 - Brighten the LED
				if (brightindex == 0) {
					brightindex += 31;
					PWM8LED_WritePulseWidth(brightindex);
					PWM8LED_Start();
				}
				else if (brightindex < 255) {
					brightindex += 32;
					PWM8LED_WritePulseWidth(brightindex);
				}
				break;
			//// Any single-byte scan codes not handled specially in the above switch statement
			//// are handled here:
			default:
				if (PianoMode) {
					i = 0;
					while((PianoScancode[i][0] != scancode) && (PianoScancode[i][0] != 0)) {
						i++;
					}
					
					
//					if (PianoScancode[i][0] > 0) {
//						PWMPiano1_WritePeriod(PianoScancode[i][1]);
//						PWMPiano1_WritePulseWidth(PianoScancode[i][2]);
//						PWMPiano1_Start();
//					}
						
					
					
					if (PianoScancode[i][0] > 0 && i <= 7) {
						PWMPiano1_WritePeriod(PianoScancode[i][1]);
						PWMPiano1_WritePulseWidth(PianoScancode[i][2]);
						PWMPiano1_Start();
					} else if (PianoScancode[i][0] > 0 && i > 7 && i <= 15) {
						PWMPiano2_WritePeriod(PianoScancode[i][1]);
						PWMPiano2_WritePulseWidth(PianoScancode[i][2]);
						PWMPiano2_Start();
					} else if (PianoScancode[i][0] > 0 && i > 15 && i <= 23) {
						PWMPiano3_WritePeriod(PianoScancode[i][1]);
						PWMPiano3_WritePulseWidth(PianoScancode[i][2]);
						PWMPiano3_Start();
					} 
				}
			}
			return;
		}
		//// Things to do when one of the single byte "make" scan code keys is released
		if (codetype & KEY_BREAK) {
			switch(scancode) {
			case 0x59:	// Right Shift
				shiftstatus &= ~0x01;
				if (!shiftstatus) ShiftDown = 0;
				break;
			case 0x12:	// Left Shift
				shiftstatus &= ~0x02;
				if (!shiftstatus) ShiftDown = 0;
			case 0x14:	// Left Control
				ctrlstatus &= ~0x02;
				if (!ctrlstatus) CtrlDown = 0;
				break;
			case 0x11:	// Left Alt
				altstatus &= ~0x02;
				if (!altstatus) AltDown = 0;
				break;
			//// Any single-byte scan codes not handled specially in the above switch statement
			//// are handled here:
			default:
				if (scancode == 0x1A || scancode == 0x22 || scancode == 0x21 || scancode == 0x2A ||
					scancode == 0x32 || scancode == 0x31 || scancode == 0x3A || scancode == 0x41 && PianoMode) 
				{
						PWMPiano1_Stop();
				} else if (scancode == 0x1C || scancode == 0x1B || scancode == 0x23 || scancode == 0x2B ||
					scancode == 0x34 || scancode == 0x33 || scancode == 0x3B || scancode == 0x42 && PianoMode) 
				{
						PWMPiano2_Stop();
				} else if (scancode == 0x15 || scancode == 0x1D || scancode == 0x24 || scancode == 0x2D ||
					scancode == 0x2C || scancode == 0x35 || scancode == 0x3C || scancode == 0x43 && PianoMode) 
				{
						PWMPiano3_Stop();
				}
				
//				
//				if (PianoMode && (!keyspressed)) {
//					PWMPiano1_Stop();
//					PWMPiano2_Stop();
//					PWMPiano3_Stop();
//				}
			}
		}
	}
	return;
}
