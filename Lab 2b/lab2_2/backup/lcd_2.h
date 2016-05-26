//*****************************************************************************
//*****************************************************************************
//  FILENAME:  LCD_2.h
//  Version: 1.60, Updated on 2013/5/19 at 10:43:48
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION:  LCD User Module C Language interface file.
//-----------------------------------------------------------------------------
//      Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef LCD_2_INCLUDE
#define LCD_2_INCLUDE

#include <m8c.h>

#define LCD_2_BARGRAPH_ENABLE 1

/* Create pragmas to support proper argument and return value passing */
#pragma fastcall16  LCD_2_Start
#pragma fastcall16  LCD_2_Init
#pragma fastcall16  LCD_2_Control
#pragma fastcall16  LCD_2_WriteData
#pragma fastcall16  LCD_2_PrString
#pragma fastcall16  LCD_2_PrCString
#pragma fastcall16  LCD_2_PrHexByte
#pragma fastcall16  LCD_2_PrHexInt
#pragma fastcall16  LCD_2_Position
#pragma fastcall16  LCD_2_Delay50uTimes
#pragma fastcall16  LCD_2_Delay50u

#if ( LCD_2_BARGRAPH_ENABLE )
#pragma fastcall16  LCD_2_InitBG
#pragma fastcall16  LCD_2_DrawBG
#pragma fastcall16  LCD_2_InitVBG
#pragma fastcall16  LCD_2_DrawVBG
#endif

//-------------------------------------------------
// Prototypes of the LCD_2 API.
//-------------------------------------------------

extern void  LCD_2_Start(void);
extern void  LCD_2_Init(void);
extern void  LCD_2_Control(BYTE bData);
extern void  LCD_2_WriteData(BYTE bData);
extern void  LCD_2_PrString(char * sRamString);
extern void  LCD_2_PrCString(const char * sRomString);
extern void  LCD_2_Position(BYTE bRow, BYTE bCol);
extern void  LCD_2_PrHexByte(BYTE bValue);
extern void  LCD_2_PrHexInt(INT iValue);

extern void  LCD_2_Delay50uTimes(BYTE bTimes);
extern void  LCD_2_Delay50u(void);

// Do not use, will be removed in future version.
extern void  LCD_2_Write_Data(BYTE bData);
#pragma fastcall16 LCD_2_Write_Data
//


#if ( LCD_2_BARGRAPH_ENABLE )
extern void  LCD_2_InitBG(BYTE bBGType);
extern void  LCD_2_InitVBG(void);
extern void  LCD_2_DrawVBG(BYTE bRow, BYTE bCol, BYTE bHeight, BYTE bPixelRowEnd);
extern void  LCD_2_DrawBG(BYTE bRow, BYTE bCol, BYTE bLen, BYTE bPixelColEnd);


#define LCD_2_SOLID_BG                      0x00
#define LCD_2_LINE_BG                       0x01


#endif

//-------------------------------------------------
// Defines for LCD_2 API's.
//-------------------------------------------------
#define LCD_2_DISP_ON                       0x0C
#define LCD_2_DISP_OFF                      0x08
#define LCD_2_DISP_BLANK                    0x0A
#define LCD_2_DISP_CLEAR_HOME               0x01
#define LCD_2_CURSOR_ON                     0x0E
#define LCD_2_CURSOR_OFF                    0x0C
#define LCD_2_CURSOR_WINK                   0x0D
#define LCD_2_CURSOR_BLINK                  0x0F
#define LCD_2_CURSOR_SH_LEFT                0x10
#define LCD_2_CURSOR_SH_RIGHT               0x14
#define LCD_2_CURSOR_HOME                   0x02
#define LCD_2_CURSOR_LEFT                   0x04
#define LCD_2_CURSOR_RIGHT                  0x06

#define LCD_2_PORT_MASK                     0x7F
//------------------------------------------------------
//  Register Address Constants for  LCD_2
//------------------------------------------------------

#define LCD_2_Port                        PRT0DR
#define LCD_2_PortMode0                   PRT0DM0
#define LCD_2_PortMode1                   PRT0DM1

#endif
// end of file LCD_2.h
