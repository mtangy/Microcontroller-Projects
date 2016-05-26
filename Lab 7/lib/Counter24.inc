;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: Counter24.inc
;;   Version: 2.5, Updated on 2014/7/14 at 8:8:54
;;  Generated by PSoC Designer 5.4.2946
;;
;;  DESCRIPTION: Assembler declarations for the Counter24 user module interface
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2014. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"


;--------------------------------------------------
; Constants for Counter24 API's.
;--------------------------------------------------

Counter24_CONTROL_REG_START_BIT:           equ 0x01    ; Control register start bit
Counter24_INT_REG:                         equ 0x0e1
Counter24_INT_MASK:                        equ 0x40


;--------------------------------------------------
; Constants for Counter24 user defined values
;--------------------------------------------------

Counter24_PERIOD:                          equ 0x12c7b
Counter24_COMPARE_VALUE:                   equ 0x12c7a


;--------------------------------------------------
; Register Address Constants for Counter24
;--------------------------------------------------

Counter24_COUNTER_LSB_REG:             equ 0x30   ; DR0 Counter register
Counter24_COUNTER_ISB_REG:             equ 0x34
Counter24_COUNTER_MSB_REG:             equ 0x38
Counter24_PERIOD_LSB_REG:              equ 0x31   ; DR1 Period register
Counter24_PERIOD_ISB_REG:              equ 0x35
Counter24_PERIOD_MSB_REG:              equ 0x39
Counter24_COMPARE_LSB_REG:             equ 0x32   ; DR2 CompareValue register
Counter24_COMPARE_ISB_REG:             equ 0x36
Counter24_COMPARE_MSB_REG:             equ 0x3a
Counter24_CONTROL_LSB_REG:             equ 0x33   ; Control register
Counter24_CONTROL_ISB_REG:             equ 0x37
Counter24_CONTROL_MSB_REG:             equ 0x3b
Counter24_FUNC_LSB_REG:                equ 0x30   ; Function register
Counter24_FUNC_ISB_REG:                equ 0x34
Counter24_FUNC_MSB_REG:                equ 0x38
Counter24_INPUT_LSB_REG:               equ 0x31   ; Input register
Counter24_INPUT_ISB_REG:               equ 0x35
Counter24_INPUT_MSB_REG:               equ 0x39
Counter24_OUTPUT_LSB_REG:              equ 0x32   ; Output register
Counter24_OUTPUT_ISB_REG:              equ 0x36
Counter24_OUTPUT_MSB_REG:              equ 0x3a


;--------------------------------------------------
; Counter24 Macro 'Functions'
;--------------------------------------------------

   macro Counter24_Start_M
   or    reg[Counter24_CONTROL_LSB_REG],  Counter24_CONTROL_REG_START_BIT
   endm

   macro Counter24_Stop_M
   and   reg[Counter24_CONTROL_LSB_REG], ~Counter24_CONTROL_REG_START_BIT
   endm

   macro Counter24_EnableInt_M
   M8C_EnableIntMask Counter24_INT_REG, Counter24_INT_MASK
   endm

   macro Counter24_DisableInt_M
   M8C_DisableIntMask Counter24_INT_REG, Counter24_INT_MASK
   endm


; end of file Counter24.inc