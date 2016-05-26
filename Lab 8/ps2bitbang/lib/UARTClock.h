//*****************************************************************************
//*****************************************************************************
//  FILENAME: UARTClock.h
//   Version: 2.5, Updated on 2013/5/19 at 10:42:30
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION: Counter16 User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef UARTClock_INCLUDE
#define UARTClock_INCLUDE

#include <m8c.h>

#pragma fastcall16 UARTClock_EnableInt
#pragma fastcall16 UARTClock_DisableInt
#pragma fastcall16 UARTClock_Start
#pragma fastcall16 UARTClock_Stop
#pragma fastcall16 UARTClock_wReadCounter              // Read  DR0
#pragma fastcall16 UARTClock_WritePeriod               // Write DR1
#pragma fastcall16 UARTClock_wReadCompareValue         // Read  DR2
#pragma fastcall16 UARTClock_WriteCompareValue         // Write DR2

// The following symbols are deprecated.
// They may be omitted in future releases
//
#pragma fastcall16 wUARTClock_ReadCounter              // Read  DR0 (Deprecated)
#pragma fastcall16 wUARTClock_ReadCompareValue         // Read  DR2 (Deprecated)

//-------------------------------------------------
// Prototypes of the UARTClock API.
//-------------------------------------------------
extern void UARTClock_EnableInt(void);                           // Proxy Class 1
extern void UARTClock_DisableInt(void);                          // Proxy Class 1
extern void UARTClock_Start(void);                               // Proxy Class 1
extern void UARTClock_Stop(void);                                // Proxy Class 1
extern WORD UARTClock_wReadCounter(void);                        // Proxy Class 2
extern void UARTClock_WritePeriod(WORD wPeriod);                 // Proxy Class 1
extern WORD UARTClock_wReadCompareValue(void);                   // Proxy Class 1
extern void UARTClock_WriteCompareValue(WORD wCompareValue);     // Proxy Class 1

// The following functions are deprecated.
// They may be omitted in future releases
//
extern WORD wUARTClock_ReadCounter(void);            // Deprecated
extern WORD wUARTClock_ReadCompareValue(void);       // Deprecated


//--------------------------------------------------
// Constants for UARTClock API's.
//--------------------------------------------------

#define UARTClock_CONTROL_REG_START_BIT        ( 0x01 )
#define UARTClock_INT_REG_ADDR                 ( 0x0df )
#define UARTClock_INT_MASK                     ( 0x20 )


//--------------------------------------------------
// Constants for UARTClock user defined values
//--------------------------------------------------

#define UARTClock_PERIOD                       ( 0x33 )
#define UARTClock_COMPARE_VALUE                ( 0x19 )


//-------------------------------------------------
// Register Addresses for UARTClock
//-------------------------------------------------

#pragma ioport  UARTClock_COUNTER_LSB_REG:  0x050          //DR0 Counter register LSB
BYTE            UARTClock_COUNTER_LSB_REG;
#pragma ioport  UARTClock_COUNTER_MSB_REG:  0x054          //DR0 Counter register MSB
BYTE            UARTClock_COUNTER_MSB_REG;
#pragma ioport  UARTClock_PERIOD_LSB_REG:   0x051          //DR1 Period register LSB
BYTE            UARTClock_PERIOD_LSB_REG;
#pragma ioport  UARTClock_PERIOD_MSB_REG:   0x055          //DR1 Period register MSB
BYTE            UARTClock_PERIOD_MSB_REG;
#pragma ioport  UARTClock_COMPARE_LSB_REG:  0x052          //DR2 Compare register LSB
BYTE            UARTClock_COMPARE_LSB_REG;
#pragma ioport  UARTClock_COMPARE_MSB_REG:  0x056          //DR2 Compare register MSB
BYTE            UARTClock_COMPARE_MSB_REG;
#pragma ioport  UARTClock_CONTROL_LSB_REG:  0x053          //Control register LSB
BYTE            UARTClock_CONTROL_LSB_REG;
#pragma ioport  UARTClock_CONTROL_MSB_REG:  0x057          //Control register MSB
BYTE            UARTClock_CONTROL_MSB_REG;
#pragma ioport  UARTClock_FUNC_LSB_REG: 0x150              //Function register LSB
BYTE            UARTClock_FUNC_LSB_REG;
#pragma ioport  UARTClock_FUNC_MSB_REG: 0x154              //Function register MSB
BYTE            UARTClock_FUNC_MSB_REG;
#pragma ioport  UARTClock_INPUT_LSB_REG:    0x151          //Input register LSB
BYTE            UARTClock_INPUT_LSB_REG;
#pragma ioport  UARTClock_INPUT_MSB_REG:    0x155          //Input register MSB
BYTE            UARTClock_INPUT_MSB_REG;
#pragma ioport  UARTClock_OUTPUT_LSB_REG:   0x152          //Output register LSB
BYTE            UARTClock_OUTPUT_LSB_REG;
#pragma ioport  UARTClock_OUTPUT_MSB_REG:   0x156          //Output register MSB
BYTE            UARTClock_OUTPUT_MSB_REG;
#pragma ioport  UARTClock_INT_REG:       0x0df             //Interrupt Mask Register
BYTE            UARTClock_INT_REG;


//-------------------------------------------------
// UARTClock Macro 'Functions'
//-------------------------------------------------

#define UARTClock_Start_M \
   ( UARTClock_CONTROL_LSB_REG |=  UARTClock_CONTROL_REG_START_BIT )

#define UARTClock_Stop_M  \
   ( UARTClock_CONTROL_LSB_REG &= ~UARTClock_CONTROL_REG_START_BIT )

#define UARTClock_EnableInt_M   \
   M8C_EnableIntMask(  UARTClock_INT_REG, UARTClock_INT_MASK )

#define UARTClock_DisableInt_M  \
   M8C_DisableIntMask( UARTClock_INT_REG, UARTClock_INT_MASK )

#endif
// end of file UARTClock.h
