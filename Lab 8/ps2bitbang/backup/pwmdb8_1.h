//*****************************************************************************
//*****************************************************************************
//  FILENAME: PWMDB8_1.h
//   Version: 2.5, Updated on 2010/9/19 at 23:40:55
//  Generated by PSoC Designer 5.1.1875.0
//
//  DESCRIPTION: PWMDB8 User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2010. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef PWMDB8_1_INCLUDE
#define PWMDB8_1_INCLUDE

#include <m8c.h>

#pragma fastcall16  PWMDB8_1_EnableInt
#pragma fastcall16  PWMDB8_1_DisableInt
#pragma fastcall16  PWMDB8_1_Start
#pragma fastcall16  PWMDB8_1_Stop
#pragma fastcall16  PWMDB8_1_WritePeriod
#pragma fastcall16  PWMDB8_1_WritePulseWidth
#pragma fastcall16  PWMDB8_1_WriteDeadTime
#pragma fastcall16  PWMDB8_1_bReadPulseWidth

//-------------------------------------------------
// Prototypes of the PWMDB8_1 API.
//-------------------------------------------------
extern void  PWMDB8_1_EnableInt(void);                    // Proxy class 1
extern void  PWMDB8_1_DisableInt(void);                   // Proxy class 1
extern void  PWMDB8_1_Start(void);                        // Proxy class 1
extern void  PWMDB8_1_Stop(void);                         // Proxy class 1
extern void  PWMDB8_1_WritePeriod(BYTE bPeriod);          // Proxy class 1
extern void  PWMDB8_1_WritePulseWidth(BYTE bPulseWidth);  // Proxy class 1
extern void  PWMDB8_1_WriteDeadTime(BYTE bDeadTime);      // Proxy class 1
extern BYTE  PWMDB8_1_bReadPulseWidth(void);              // Proxy class 1

//-------------------------------------------------
// Do not use! For backwards compatibility only.
#pragma fastcall16 bPWMDB8_1_ReadPulseWidth
extern BYTE bPWMDB8_1_ReadPulseWidth(void);
//-------------------------------------------------


//--------------------------------------------------
// Constants for PWMDB8_1 user defined values
//--------------------------------------------------

#define PWMDB8_1_PERIOD                        ( 0xc7 )
#define PWMDB8_1_PULSE_WIDTH                   ( 0x63 )


//-------------------------------------------------
// Register Addresses for PWMDB8_1
//-------------------------------------------------
#pragma ioport  PWMDB8_1_PWM_CONTROL_REG:   0x023          //PWM Control register
BYTE            PWMDB8_1_PWM_CONTROL_REG;
#pragma ioport  PWMDB8_1_PWM_COUNTER_REG:   0x020          //PWM Counter register
BYTE            PWMDB8_1_PWM_COUNTER_REG;
#pragma ioport  PWMDB8_1_PWM_PERIOD_REG:    0x021          //PWM Period value register
BYTE            PWMDB8_1_PWM_PERIOD_REG;
#pragma ioport  PWMDB8_1_PULSE_WIDTH_REG:   0x022          //PWM PulseWidth register
BYTE            PWMDB8_1_PULSE_WIDTH_REG;
#pragma ioport  PWMDB8_1_PWM_FUNC_REG:  0x120              //Function register
BYTE            PWMDB8_1_PWM_FUNC_REG;
#pragma ioport  PWMDB8_1_PWM_INPUT_REG: 0x121              //Input register
BYTE            PWMDB8_1_PWM_INPUT_REG;
#pragma ioport  PWMDB8_1_PWM_OUTPUT_REG:    0x122          //Output register
BYTE            PWMDB8_1_PWM_OUTPUT_REG;
#pragma ioport  PWMDB8_1_DB_CONTROL_REG:    0x027          //DB Control register
BYTE            PWMDB8_1_DB_CONTROL_REG;
#pragma ioport  PWMDB8_1_DB_COUNTER_REG:    0x024          //DB Counter register
BYTE            PWMDB8_1_DB_COUNTER_REG;
#pragma ioport  PWMDB8_1_DEAD_TIME_REG: 0x025              //DB Dead Timer register
BYTE            PWMDB8_1_DEAD_TIME_REG;
#pragma ioport  PWMDB8_1_DB_FUNC_REG:   0x124              //Function register
BYTE            PWMDB8_1_DB_FUNC_REG;
#pragma ioport  PWMDB8_1_DB_INPUT_REG:  0x125              //Input register
BYTE            PWMDB8_1_DB_INPUT_REG;
#pragma ioport  PWMDB8_1_DB_OUTPUT_REG: 0x126              //Output register
BYTE            PWMDB8_1_DB_OUTPUT_REG;
#pragma ioport  PWMDB8_1_DB_DR2_REG:    0x026              //DB DR2 register
BYTE            PWMDB8_1_DB_DR2_REG;

#endif
// end of file PWMDB8_1.h
