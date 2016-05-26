;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: PWM8LED.inc
;;   Version: 2.60, Updated on 2013/5/19 at 10:44:7
;;  Generated by PSoC Designer 5.4.2946
;;
;;  DESCRIPTION: Assembler declarations for the PWM8 user module interface
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"


;--------------------------------------------------
; Constants for PWM8LED API's.
;--------------------------------------------------

PWM8LED_CONTROL_REG_START_BIT:             equ 0x01    ; Control register start bit
PWM8LED_INT_REG:                           equ 0x0df
PWM8LED_INT_MASK:                          equ 0x01


;--------------------------------------------------
; Constants for PWM8LED user defined values
;--------------------------------------------------

PWM8LED_PERIOD:                            equ 0xff
PWM8LED_PULSE_WIDTH:                       equ 0x7f


;--------------------------------------------------
; Register Address Constants for PWM8LED
;--------------------------------------------------

PWM8LED_COUNTER_REG:                   equ 0x40   ; DR0 Count register
PWM8LED_PERIOD_REG:                    equ 0x41   ; DR1 Period register
PWM8LED_COMPARE_REG:                   equ 0x42   ; DR2 Compare register
PWM8LED_CONTROL_REG:                   equ 0x43   ; Control register
PWM8LED_FUNC_REG:                      equ 0x40   ; Function register
PWM8LED_INPUT_REG:                     equ 0x41   ; Input register
PWM8LED_OUTPUT_REG:                    equ 0x42   ; Output register


;--------------------------------------------------
; PWM8LED Macro 'Functions'
;--------------------------------------------------

   macro PWM8LED_Start_M
   or    reg[PWM8LED_CONTROL_REG],  PWM8LED_CONTROL_REG_START_BIT
   endm

   macro PWM8LED_Stop_M
   and   reg[PWM8LED_CONTROL_REG], ~PWM8LED_CONTROL_REG_START_BIT
   endm

   macro PWM8LED_EnableInt_M
   M8C_EnableIntMask PWM8LED_INT_REG, PWM8LED_INT_MASK
   endm

   macro PWM8LED_DisableInt_M
   M8C_DisableIntMask PWM8LED_INT_REG, PWM8LED_INT_MASK
   endm


; end of file PWM8LED.inc