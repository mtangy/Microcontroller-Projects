//*****************************************************************************
//*****************************************************************************
//  FILENAME:  UART.h
//  Version: 5.3, Updated on 2013/5/19 at 10:44:49
//  Generated by PSoC Designer 5.4.2946
//
//  DESCRIPTION:  UART User Module C Language interface file.
//-----------------------------------------------------------------------------
//      Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef UART_INCLUDE
#define UART_INCLUDE

// include the global header file
#include <m8c.h>

#define UART_RXBUF_ENABLE 0

//-------------------------------------------------
// Prototypes of the UART API.
//-------------------------------------------------

#if ( UART_RXBUF_ENABLE )
extern char UART_aRxBuffer[];
extern BYTE UART_bRxCnt;
extern BYTE UART_fStatus;
#endif



// Create pragmas to support proper argument and return value passing

#pragma fastcall16  UART_SetTxIntMode
#pragma fastcall16  UART_EnableInt
#pragma fastcall16  UART_DisableInt
#pragma fastcall16  UART_Start
#pragma fastcall16  UART_Stop
#pragma fastcall16  UART_SendData
#pragma fastcall16  UART_bReadTxStatus
#pragma fastcall16  UART_bReadRxData
#pragma fastcall16  UART_bReadRxStatus
#pragma fastcall16  UART_PutSHexByte
#pragma fastcall16  UART_PutSHexInt
#pragma fastcall16  UART_CPutString
#pragma fastcall16  UART_PutString
#pragma fastcall16  UART_PutChar
#pragma fastcall16  UART_Write
#pragma fastcall16  UART_CWrite

#pragma fastcall16  UART_cGetChar
#pragma fastcall16  UART_cReadChar
#pragma fastcall16  UART_iReadChar
#pragma fastcall16  UART_IntCntl
#pragma fastcall16  UART_TxIntMode
#pragma fastcall16  UART_PutCRLF

#if ( UART_RXBUF_ENABLE )
#pragma fastcall16  UART_CmdReset
#pragma fastcall16  UART_bCmdCheck
#pragma fastcall16  UART_bErrCheck
#pragma fastcall16  UART_bCmdLength
#pragma fastcall16  UART_szGetParam
#pragma fastcall16  UART_szGetRestOfParams
#endif

//**************************************************
// Prototypes of UART API.
//**************************************************
extern void  UART_SetTxIntMode(BYTE bTxIntMode);
extern void  UART_EnableInt(void);
extern void  UART_DisableInt(void);
extern void  UART_Start(BYTE bParitySetting);
extern void  UART_Stop(void);
extern void  UART_SendData(BYTE bTxData);
extern BYTE  UART_bReadTxStatus(void);
extern BYTE  UART_bReadRxData(void);
extern BYTE  UART_bReadRxStatus(void);

// High level TX functions
extern void   UART_CPutString(const BYTE * szRomString);
extern void   UART_PutString(BYTE * szRamString);
extern void   UART_PutChar(CHAR cData);
extern void   UART_Write(BYTE * szRamString, BYTE bCount);
extern void   UART_CWrite(const BYTE * szRomString, INT iCount);
extern void   UART_PutSHexByte(BYTE bValue);
extern void   UART_PutSHexInt(INT iValue);
extern void   UART_PutCRLF(void);
extern void   UART_TxIntMode(BYTE bMask);

// High level RX functions
extern CHAR   UART_cGetChar(void);
extern CHAR   UART_cReadChar(void);
extern INT    UART_iReadChar(void);
extern void   UART_IntCntl(BYTE bMask);

#if ( UART_RXBUF_ENABLE )
extern void   UART_CmdReset(void);
extern BYTE   UART_bCmdCheck(void);
extern BYTE   UART_bErrCheck(void);
extern BYTE   UART_bCmdLength(void);
extern BYTE * UART_szGetParam(void);
extern BYTE * UART_szGetRestOfParams(void);
#endif

//-------------------------------------------------
// Defines for UART API's.
//-------------------------------------------------



//------------------------------------
//  Parity masks
//------------------------------------
#define  UART_PARITY_NONE        0x00
#define  UART_PARITY_EVEN        0x02
#define  UART_PARITY_ODD         0x06
//------------------------------------
//  Transmitter Status Register masks
//------------------------------------
#define  UART_TX_COMPLETE        0x20
#define  UART_TX_BUFFER_EMPTY    0x10

//------------------------------------
//  Receiver Status Register masks
//------------------------------------
#define  UART_RX_ACTIVE          0x10
#define  UART_RX_COMPLETE        0x08
#define  UART_RX_REG_FULL        0x08
#define  UART_RX_PARITY_ERROR    0x80
#define  UART_RX_OVERRUN_ERROR   0x40
#define  UART_RX_FRAMING_ERROR   0x20
#define  UART_RX_ERROR           0xE0
#define  UART_RX_NO_ERROR        0xE0          // This symbol is deprecated and will removed in the future

#define  UART_RX_NO_DATA         0x01

#define  UART_RX_BUF_ERROR                0xF0  // Mask for any Rx that may occur.
#define  UART_RX_BUF_OVERRUN              0x10  // This indicates the software buffer has
                                                           // been over run.
#define  UART_RX_BUF_CMDTERM              0x01  // Command terminator has been received.

// Interrupt control used with  UART_IntCntl() function
#define UART_ENABLE_RX_INT  0x01
#define UART_ENABLE_TX_INT  0x02
#define UART_DISABLE_RX_INT 0x00
#define UART_DISABLE_TX_INT 0x00

// Interrupt Modes
#define UART_INT_MODE_TX_REG_EMPTY 0x00
#define UART_INT_MODE_TX_COMPLETE  0x01

//-------------------------------------------------
// Register Address Constants for UART
//-------------------------------------------------

#pragma ioport  UART_TX_CONTROL_REG:    0x05b               // Control register
BYTE            UART_TX_CONTROL_REG;
#pragma ioport  UART_TX_SHIFT_REG:  0x058                   // TX Shift Register register
BYTE            UART_TX_SHIFT_REG;
#pragma ioport  UART_TX_BUFFER_REG: 0x059                   // TX Buffer Register
BYTE            UART_TX_BUFFER_REG;
#pragma ioport  UART_TX_FUNC_REG:   0x158                   // Function register
BYTE            UART_TX_FUNC_REG;
#pragma ioport  UART_TX_INPUT_REG:  0x159                   // Input register
BYTE            UART_TX_INPUT_REG;
#pragma ioport  UART_TX_OUTPUT_REG: 0x15a                   // Output register
BYTE            UART_TX_OUTPUT_REG;
#pragma ioport  UART_RX_CONTROL_REG:    0x05f               // Control register
BYTE            UART_RX_CONTROL_REG;
#pragma ioport  UART_RX_SHIFT_REG:  0x05c                   // RX Shift Register register
BYTE            UART_RX_SHIFT_REG;
#pragma ioport  UART_RX_BUFFER_REG: 0x05e                   // RX Buffer Register
BYTE            UART_RX_BUFFER_REG;
#pragma ioport  UART_RX_FUNC_REG:   0x15c                   // Function register
BYTE            UART_RX_FUNC_REG;
#pragma ioport  UART_RX_INPUT_REG:  0x15d                   // Input register
BYTE            UART_RX_INPUT_REG;
#pragma ioport  UART_RX_OUTPUT_REG: 0x15e                   // Output register
BYTE            UART_RX_OUTPUT_REG;

#pragma ioport  UART_TX_INT_REG:       0x0df               // TX Interrupt Mask Register
BYTE            UART_TX_INT_REG;
#pragma ioport  UART_RX_INT_REG:       0x0df               // RX Interrupt Mask Register
BYTE            UART_RX_INT_REG;

// Masks to use with UART_TX_INT_REG and UART_RX_INT_REG Registers
#define UART_TX_INT_MASK            (0x40) // TX Interrupt register Mask
#define UART_RX_INT_MASK            (0x80) // RX Interrupt register Mask


//-------------------------------------------
//       WARNING WARNING WARNING
// The following defines and function prototypes
// are for backwards compatibility only and
// should not be used for new designs.
//-------------------------------------------
#pragma fastcall16  bUART_ReadTxStatus
#pragma fastcall16  bUART_ReadRxData
#pragma fastcall16  bUART_ReadRxStatus
extern BYTE  bUART_ReadTxStatus(void);
extern BYTE  bUART_ReadRxData(void);
extern BYTE  bUART_ReadRxStatus(void);
//------------------------------------
//  Parity masks
//------------------------------------
#define  UART_PARITY_NONE        0x00
#define  UART_PARITY_EVEN        0x02
#define  UART_PARITY_ODD         0x06

//------------------------------------
//  Transmitter Status Register masks
//------------------------------------
#define  UART_TX_COMPLETE        0x20
#define  UART_TX_BUFFER_EMPTY    0x10

//------------------------------------
//  Receiver Status Register masks
//------------------------------------
#define  UART_RX_ACTIVE          0x10
#define  UART_RX_COMPLETE        0x08
#define  UART_RX_PARITY_ERROR    0x80
#define  UART_RX_OVERRUN_ERROR   0x40
#define  UART_RX_FRAMING_ERROR   0x20
#define  UART_RX_NO_ERROR        0xE0

#endif
//-------------------------------------------
//             END WARNING
//-------------------------------------------
// end of file UART.h
