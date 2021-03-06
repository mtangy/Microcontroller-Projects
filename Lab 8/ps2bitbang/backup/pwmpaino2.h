//*****************************************************************************
//*****************************************************************************
//  FILENAME: PWMPaino2.h
//   Version: 2.5, Updated on 2013/5/19 at 10:44:6
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION: PWM16 User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef PWMPaino2_INCLUDE
#define PWMPaino2_INCLUDE

#include <m8c.h>

#pragma fastcall16 PWMPaino2_EnableInt
#pragma fastcall16 PWMPaino2_DisableInt
#pragma fastcall16 PWMPaino2_Start
#pragma fastcall16 PWMPaino2_Stop
#pragma fastcall16 PWMPaino2_wReadCounter              // Read  DR0
#pragma fastcall16 PWMPaino2_WritePeriod               // Write DR1
#pragma fastcall16 PWMPaino2_wReadPulseWidth           // Read  DR2
#pragma fastcall16 PWMPaino2_WritePulseWidth           // Write DR2

// The following symbols are deprecated.
// They may be omitted in future releases
//
#pragma fastcall16 wPWMPaino2_ReadCounter              // Read  DR0 (Deprecated)
#pragma fastcall16 wPWMPaino2_ReadPulseWidth           // Read  DR2 (Deprecated)


//-------------------------------------------------
// Prototypes of the PWMPaino2 API.
//-------------------------------------------------

extern void PWMPaino2_EnableInt(void);                  // Proxy Class 1
extern void PWMPaino2_DisableInt(void);                 // Proxy Class 1
extern void PWMPaino2_Start(void);                      // Proxy Class 1
extern void PWMPaino2_Stop(void);                       // Proxy Class 1
extern WORD PWMPaino2_wReadCounter(void);               // Proxy Class 2
extern void PWMPaino2_WritePeriod(WORD wPeriod);        // Proxy Class 1
extern WORD PWMPaino2_wReadPulseWidth(void);            // Proxy Class 1
extern void PWMPaino2_WritePulseWidth(WORD wPulseWidth);// Proxy Class 1

// The following functions are deprecated.
// They may be omitted in future releases
//
extern WORD wPWMPaino2_ReadCounter(void);            // Deprecated
extern WORD wPWMPaino2_ReadPulseWidth(void);         // Deprecated


//-------------------------------------------------
// Constants for PWMPaino2 API's.
//-------------------------------------------------

#define PWMPaino2_CONTROL_REG_START_BIT        ( 0x01 )
#define PWMPaino2_INT_REG_ADDR                 ( 0x0e1 )
#define PWMPaino2_INT_MASK                     ( 0x02 )


//--------------------------------------------------
// Constants for PWMPaino2 user defined values
//--------------------------------------------------

#define PWMPaino2_PERIOD                       ( 0x0 )
#define PWMPaino2_PULSE_WIDTH                  ( 0x0 )


//-------------------------------------------------
// Register Addresses for PWMPaino2
//-------------------------------------------------

#pragma ioport  PWMPaino2_COUNTER_LSB_REG:  0x020          //DR0 Count register LSB
BYTE            PWMPaino2_COUNTER_LSB_REG;
#pragma ioport  PWMPaino2_COUNTER_MSB_REG:  0x024          //DR0 Count register MSB
BYTE            PWMPaino2_COUNTER_MSB_REG;
#pragma ioport  PWMPaino2_PERIOD_LSB_REG:   0x021          //DR1 Period register LSB
BYTE            PWMPaino2_PERIOD_LSB_REG;
#pragma ioport  PWMPaino2_PERIOD_MSB_REG:   0x025          //DR1 Period register MSB
BYTE            PWMPaino2_PERIOD_MSB_REG;
#pragma ioport  PWMPaino2_COMPARE_LSB_REG:  0x022          //DR2 Compare register LSB
BYTE            PWMPaino2_COMPARE_LSB_REG;
#pragma ioport  PWMPaino2_COMPARE_MSB_REG:  0x026          //DR2 Compare register MSB
BYTE            PWMPaino2_COMPARE_MSB_REG;
#pragma ioport  PWMPaino2_CONTROL_LSB_REG:  0x023          //Control register LSB
BYTE            PWMPaino2_CONTROL_LSB_REG;
#pragma ioport  PWMPaino2_CONTROL_MSB_REG:  0x027          //Control register MSB
BYTE            PWMPaino2_CONTROL_MSB_REG;
#pragma ioport  PWMPaino2_FUNC_LSB_REG: 0x120              //Function register LSB
BYTE            PWMPaino2_FUNC_LSB_REG;
#pragma ioport  PWMPaino2_FUNC_MSB_REG: 0x124              //Function register MSB
BYTE            PWMPaino2_FUNC_MSB_REG;
#pragma ioport  PWMPaino2_INPUT_LSB_REG:    0x121          //Input register LSB
BYTE            PWMPaino2_INPUT_LSB_REG;
#pragma ioport  PWMPaino2_INPUT_MSB_REG:    0x125          //Input register MSB
BYTE            PWMPaino2_INPUT_MSB_REG;
#pragma ioport  PWMPaino2_OUTPUT_LSB_REG:   0x122          //Output register LSB
BYTE            PWMPaino2_OUTPUT_LSB_REG;
#pragma ioport  PWMPaino2_OUTPUT_MSB_REG:   0x126          //Output register MSB
BYTE            PWMPaino2_OUTPUT_MSB_REG;
#pragma ioport  PWMPaino2_INT_REG:       0x0e1             //Interrupt Mask Register
BYTE            PWMPaino2_INT_REG;


//-------------------------------------------------
// PWMPaino2 Macro 'Functions'
//-------------------------------------------------

#define PWMPaino2_Start_M \
   ( PWMPaino2_CONTROL_LSB_REG |=  PWMPaino2_CONTROL_REG_START_BIT )

#define PWMPaino2_Stop_M  \
   ( PWMPaino2_CONTROL_LSB_REG &= ~PWMPaino2_CONTROL_REG_START_BIT )

#define PWMPaino2_EnableInt_M   \
   M8C_EnableIntMask(  PWMPaino2_INT_REG, PWMPaino2_INT_MASK )

#define PWMPaino2_DisableInt_M  \
   M8C_DisableIntMask( PWMPaino2_INT_REG, PWMPaino2_INT_MASK )

#endif
// end of file PWMPaino2.h
