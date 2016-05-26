//*****************************************************************************
//*****************************************************************************
//  FILENAME: SW2Buf.h
//  Version: 1.3, Updated on 2013/5/19 at 10:43:26
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION: DigitalBuffers User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef SW2Buf_INCLUDE
#define SW2Buf_INCLUDE

#include <m8c.h>

#pragma fastcall16 SW2Buf_EnableInt
#pragma fastcall16 SW2Buf_DisableInt
#pragma fastcall16 SW2Buf_Start
#pragma fastcall16 SW2Buf_Stop

//-------------------------------------------------
// Prototypes of the SW2Buf API.
//-------------------------------------------------

extern void SW2Buf_EnableInt(void);
extern void SW2Buf_DisableInt(void);
extern void SW2Buf_Start(void);
extern void SW2Buf_Stop(void);


//--------------------------------------------------
// Constants for SW2Buf API's.
//--------------------------------------------------
#define SW2Buf_CONTROL_REG_START_BIT           ( 0x01 )
#define SW2Buf_INT_REG_ADDR                    ( 0x0e1 )
#define SW2Buf_INT_MASK                        ( 0x10 )


//--------------------------------------------------
// Constants for SW2Buf user defined values
//--------------------------------------------------
#pragma ioport  SW2Buf_DATA_0_REG:  0x030                  //DR0 Count register
BYTE            SW2Buf_DATA_0_REG;
#pragma ioport  SW2Buf_DATA_1_REG:  0x031                  //DR1 Period register
BYTE            SW2Buf_DATA_1_REG;
#pragma ioport  SW2Buf_DATA_2_REG:  0x032                  //DR2 Compare register
BYTE            SW2Buf_DATA_2_REG;
#pragma ioport  SW2Buf_CONTROL_REG: 0x033                  //Control register
BYTE            SW2Buf_CONTROL_REG;
#pragma ioport  SW2Buf_FUNC_REG:    0x130                  //Function register
BYTE            SW2Buf_FUNC_REG;
#pragma ioport  SW2Buf_INPUT_REG:   0x131                  //Input register
BYTE            SW2Buf_INPUT_REG;
#pragma ioport  SW2Buf_OUTPUT_REG:  0x132                  //Output register
BYTE            SW2Buf_OUTPUT_REG;
#pragma ioport  SW2Buf_INT_REG:       0x0e1                //Interrupt Mask Register
BYTE            SW2Buf_INT_REG;


//-------------------------------------------------
// Register Addresses for SW2Buf
//-------------------------------------------------


//-------------------------------------------------
// SW2Buf Macro 'Functions'
//-------------------------------------------------

#define SW2Buf_Start_M \
   SW2Buf_CONTROL_REG |=  SW2Buf_CONTROL_REG_START_BIT

#define SW2Buf_Stop_M  \
   SW2Buf_CONTROL_REG &= ~SW2Buf_CONTROL_REG_START_BIT

#define SW2Buf_EnableInt_M   \
   M8C_EnableIntMask(SW2Buf_INT_REG, SW2Buf_INT_MASK)

#define SW2Buf_DisableInt_M  \
   M8C_DisableIntMask(SW2Buf_INT_REG, SW2Buf_INT_MASK)

#endif
// end of file SW2Buf.h