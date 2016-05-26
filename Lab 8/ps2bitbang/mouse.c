//----------------------------------------------------------------------------
// XXX - Create the comments for this.
//
// B. Noble - 18 October 2010
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "ps2.h"
#include "mouse.h"

extern BYTE PS2RxBuffer[];
extern BYTE PS2RxBufIn;
extern BYTE PS2RxBufOut;

void MouseInit(void)
{
	//// Mouse init stuff
	//// XXX - Document these!
	PS2_Send_Command_Process_Response(0xF3);
	PS2_Send_Command_Process_Response(0x0A);
	PS2_Send_Command_Process_Response(0xE8);
	PS2_Send_Command_Process_Response(0x03);
	PS2_Send_Command_Process_Response(0xE6);
	PS2_Send_Command_Process_Response(0xF4);
}

void MousePrintRawData(void)
{
	BYTE scancode;
	static int i = 0;

	while(PS2RxBufOut == PS2RxBufIn); // Spin until we get data
	scancode = PS2RxBuffer[PS2RxBufOut];
	PS2RxBufOut++;
	// Wrap around the circular buffer pointer at 16 
	if (PS2RxBufOut & 0x10) PS2RxBufOut = 0;
	// If Bit 3 isn't set, then this isn't Byte 1
	if ((i==0)&&(!(scancode & 0x08))) return;
	LCD_Position(1,i);
	LCD_PrHexByte(scancode);
	if (i==0) i=3;
	else if (i==3) i=6;
	else if (i==6) i=0;
	return;
}

void MouseCursor(void)
{
	signed char i;
	BYTE scancode;
	BYTE yov;
	BYTE xov;
	BYTE ysign;
	BYTE xsign;
	BYTE mbtn;
	BYTE rbtn;
	BYTE lbtn;
	BYTE xstep = 0;
	BYTE ystep = 0;
	static int xcount = 0;
	static int ycount = 0;
	static BYTE xpos = 0;
	static BYTE ypos = 0;
	static BYTE xopos = 0;
	static BYTE yopos = 0;

	//// Byte 1 - X&Y overflow, X&Y sign, and 3-button data
	while(PS2RxBufOut == PS2RxBufIn); // Spin until we get data
	scancode = PS2RxBuffer[PS2RxBufOut];
	PS2RxBufOut++;
	// Wrap around the circular buffer pointer at 16
	if (PS2RxBufOut & 0x10) PS2RxBufOut = 0;
	//// If Bit 3 isn't set, then this isn't Byte 1
	if (!(scancode & 0x08)) return;
	yov = (scancode & 0x80) >> 7;
	xov = (scancode & 0x40) >> 6;
	ysign = (scancode & 0x20) >> 5;
	xsign = (scancode & 0x10) >> 4;
	mbtn = (scancode & 0x04) >> 2;
	rbtn = (scancode & 0x02) >> 1;
	lbtn = (scancode & 0x01);
	//// Byte 2 - X Movement
	while(PS2RxBufOut == PS2RxBufIn); // Spin until we get data
	scancode = PS2RxBuffer[PS2RxBufOut];
	PS2RxBufOut++;
	// Wrap around the circular buffer pointer at 16 
	if (PS2RxBufOut & 0x10) PS2RxBufOut = 0;
	// Update the X counts
	if (xsign) { // Negative
		xstep = (~scancode)+1; // Make the 2s-complement negative a positive
		if (xcount - xstep > 0)	xcount -= xstep;
		else xcount = 0;
	}
	else {
		xstep = scancode;
		if (xcount + xstep < 0x01FF) xcount += xstep;
		else xcount = 0x01FF;
	}
	//// Byte 3 - Y Movement
	while(PS2RxBufOut == PS2RxBufIn); // Spin until we get data
	scancode = PS2RxBuffer[PS2RxBufOut];
	PS2RxBufOut++;
	// Wrap around the circular buffer pointer at 16 
	if (PS2RxBufOut & 0x10) PS2RxBufOut = 0;
	// Update the Y counts
	if (ysign) { // Negative
		ystep = (~scancode)+1; // Make the 2s-complement negative a positive
		if (ycount - ystep > 0)	ycount -= ystep;
		else ycount = 0;
	}
	else {
		ystep = scancode;
		if (ycount + ystep < 0x07FF) ycount += ystep;
		else ycount = 0x07FF;
	}
	//// Print the buttons' status and the X and Y counts to the LCD
	LCD_Position(1,0);
	if (lbtn) LCD_PrCString("L"); else LCD_PrCString(" ");
	if (mbtn) LCD_PrCString("M"); else LCD_PrCString(" ");
	if (rbtn) LCD_PrCString("RX:"); else LCD_PrCString(" X:");
	LCD_PrHexInt(xcount);
	LCD_PrCString(" Y:");
	LCD_PrHexInt(ycount);
	//// Control the brightness of the PWM8LED with the Y-axis
	yopos = ypos;
	ypos = (BYTE)(ycount>>4);
	if (ypos != yopos) {
		PWM8LED_WritePulseWidth(ypos);
	}
	//// Pilot the cursor around the LCD with the X-axis
	xopos = xpos;
	xpos = (BYTE)(xcount>>5);
	if (lbtn) {
		if (xpos >= xopos) {
			for(i=xopos ; i<=xpos ; i++) {
				LCD_Position(0,i);
				LCD_WriteData(0xDB); // Square
				LCD_Control(LCD_CURSOR_SH_LEFT);
			}
		}
		else {
			for(i=xopos ; i>=xpos ; i--) {
				LCD_Position(0,i);
				LCD_WriteData(0xDB); // Square
				LCD_Control(LCD_CURSOR_SH_LEFT);
			}
		}
	}
	else {
		LCD_Position(0,xpos);
	}
	if (rbtn) {
		if (xpos >= xopos) {
			for(i=xopos ; i<=xpos ; i++) {
				LCD_Position(0,i);
				LCD_WriteData(' ');
				LCD_Control(LCD_CURSOR_SH_LEFT);
			}
		}
		else {
			for(i=xopos ; i>=xpos ; i--) {
				LCD_Position(0,i);
				LCD_WriteData(' ');
				LCD_Control(LCD_CURSOR_SH_LEFT);
			}
		}
	}
	else {
		LCD_Position(0,xpos);
	}
}