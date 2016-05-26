;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: DACUpdate.inc
;;   Version: 2.60, Updated on 2015/3/4 at 22:23:47
;;  Generated by PSoC Designer 5.4.3191
;;
;;  DESCRIPTION: Assembler declarations for the Counter8 user module interface
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2015. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"


;--------------------------------------------------
; Constants for DACUpdate API's.
;--------------------------------------------------

DACUpdate_CONTROL_REG_START_BIT:           equ 0x01    ; Control register start bit
DACUpdate_INT_REG:                         equ 0x0e1
DACUpdate_INT_MASK:                        equ 0x02


;--------------------------------------------------
; Constants for DACUpdate user defined values
;--------------------------------------------------

DACUpdate_PERIOD:                          equ 0x7f
DACUpdate_COMPARE_VALUE:                   equ 0x04


;--------------------------------------------------
; Register Address Constants for DACUpdate
;--------------------------------------------------

DACUpdate_COUNTER_REG:                 equ 0x24   ; DR0 Counter register
DACUpdate_PERIOD_REG:                  equ 0x25   ; DR1 Period register
DACUpdate_COMPARE_REG:                 equ 0x26   ; DR2 CompareValue register
DACUpdate_CONTROL_REG:                 equ 0x27   ; Control register
DACUpdate_FUNC_REG:                    equ 0x24   ; Function register
DACUpdate_INPUT_REG:                   equ 0x25   ; Input register
DACUpdate_OUTPUT_REG:                  equ 0x26   ; Output register


;--------------------------------------------------
; DACUpdate Macro 'Functions'
;--------------------------------------------------

   macro DACUpdate_Start_M
   or    reg[DACUpdate_CONTROL_REG],  DACUpdate_CONTROL_REG_START_BIT
   endm

   macro DACUpdate_Stop_M
   and   reg[DACUpdate_CONTROL_REG], ~DACUpdate_CONTROL_REG_START_BIT
   endm

   macro DACUpdate_EnableInt_M
   M8C_EnableIntMask DACUpdate_INT_REG, DACUpdate_INT_MASK
   endm

   macro DACUpdate_DisableInt_M
   M8C_DisableIntMask DACUpdate_INT_REG, DACUpdate_INT_MASK
   endm


; end of file DACUpdate.inc