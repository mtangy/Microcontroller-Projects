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