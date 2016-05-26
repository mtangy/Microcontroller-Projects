;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: PWMPiano2.inc
;;   Version: 2.5, Updated on 2013/5/19 at 10:44:6
;;  Generated by PSoC Designer 5.4.2946
;;
;;  DESCRIPTION: Assembler declarations for the PWM16 user module interface
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"


;--------------------------------------------------
; Constants for PWMPiano2 API's.
;--------------------------------------------------

PWMPiano2_CONTROL_REG_START_BIT:           equ 0x01    ; Control register start bit
PWMPiano2_INT_REG:                         equ 0x0e1
PWMPiano2_INT_MASK:                        equ 0x02


;--------------------------------------------------
; Constants for PWMPiano2 user defined values
;--------------------------------------------------

PWMPiano2_PERIOD:                          equ 0x0
PWMPiano2_PULSE_WIDTH:                     equ 0x0


;--------------------------------------------------
; Register Address Constants for PWMPiano2
;--------------------------------------------------

PWMPiano2_COUNTER_LSB_REG:             equ 0x20   ; DR0 Count register
PWMPiano2_COUNTER_MSB_REG:             equ 0x24
PWMPiano2_PERIOD_LSB_REG:              equ 0x21   ; DR1 Period register
PWMPiano2_PERIOD_MSB_REG:              equ 0x25
PWMPiano2_COMPARE_LSB_REG:             equ 0x22   ; DR2 Compare register
PWMPiano2_COMPARE_MSB_REG:             equ 0x26
PWMPiano2_CONTROL_LSB_REG:             equ 0x23   ; Control register
PWMPiano2_CONTROL_MSB_REG:             equ 0x27
PWMPiano2_FUNC_LSB_REG:                equ 0x20   ; Function register
PWMPiano2_FUNC_MSB_REG:                equ 0x24
PWMPiano2_INPUT_LSB_REG:               equ 0x21   ; Input register
PWMPiano2_INPUT_MSB_REG:               equ 0x25
PWMPiano2_OUTPUT_LSB_REG:              equ 0x22   ; Output register
PWMPiano2_OUTPUT_MSB_REG:              equ 0x26


;--------------------------------------------------
; PWMPiano2 Macro 'Functions'
;--------------------------------------------------

   macro PWMPiano2_Start_M
   or    reg[PWMPiano2_CONTROL_LSB_REG],  PWMPiano2_CONTROL_REG_START_BIT
   endm

   macro PWMPiano2_Stop_M
   and   reg[PWMPiano2_CONTROL_LSB_REG], ~PWMPiano2_CONTROL_REG_START_BIT
   endm

   macro PWMPiano2_EnableInt_M
   M8C_EnableIntMask PWMPiano2_INT_REG, PWMPiano2_INT_MASK
   endm

   macro PWMPiano2_DisableInt_M
   M8C_DisableIntMask PWMPiano2_INT_REG, PWMPiano2_INT_MASK
   endm


; end of file PWMPiano2.inc
