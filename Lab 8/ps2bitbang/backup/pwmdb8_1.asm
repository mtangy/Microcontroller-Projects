;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: PWMDB8_1.asm
;;   Version: 2.5, Updated on 2010/9/19 at 23:40:55
;;  Generated by PSoC Designer 5.1.1875.0
;;
;;  DESCRIPTION: PWMDB8 User Module software implementation file
;;
;;  NOTE: User Module APIs conform to the fastcall16 convention for marshalling
;;        arguments and observe the associated "Registers are volatile" policy.
;;        This means it is the caller's responsibility to preserve any values
;;        in the X and A registers that are still needed after the API functions
;;        returns. For Large Memory Model devices it is also the caller's 
;;        responsibility to perserve any value in the CUR_PP, IDX_PP, MVR_PP and 
;;        MVW_PP registers. Even though some of these registers may not be modified
;;        now, there is no guarantee that will remain the case in future releases.
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2010. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"
include "memory.inc"
include "PWMDB8_1.inc"


;-----------------------------------------------
;  Global Symbols
;-----------------------------------------------

export   PWMDB8_1_EnableInt
export  _PWMDB8_1_EnableInt
export   PWMDB8_1_DisableInt
export  _PWMDB8_1_DisableInt
export   PWMDB8_1_Start
export  _PWMDB8_1_Start
export   PWMDB8_1_Stop
export  _PWMDB8_1_Stop
export   PWMDB8_1_WritePeriod
export  _PWMDB8_1_WritePeriod
export   PWMDB8_1_WritePulseWidth
export  _PWMDB8_1_WritePulseWidth
export   PWMDB8_1_WriteDeadTime
export  _PWMDB8_1_WriteDeadTime
export   PWMDB8_1_bReadPulseWidth
export  _PWMDB8_1_bReadPulseWidth

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;       WARNING WARNING WARNING
; The following exports are for backwards
; compatibility only and should not be used
; for new designs.
export   bPWMDB8_1_ReadPulseWidth
export  _bPWMDB8_1_ReadPulseWidth
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;-----------------------------------------------
;  Constant Definitions
;-----------------------------------------------
bfCONTROL_REG_START_BIT:   equ   1  ; Control register start bit

;-----------------------------------------------
; Variable Allocation
;-----------------------------------------------


area UserModules (ROM, REL)

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWMDB8_1_EnableInt
;
;  DESCRIPTION:
;     Enables this PWM's interrupt by setting the interrupt enable mask bit
;     associated with this User Module. Remember to call the global interrupt
;     enable function by using the macro: M8C_EnableGInt.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:  None
;
;  RETURNS: None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWMDB8_1_EnableInt:
_PWMDB8_1_EnableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
   M8C_EnableIntMask PWMDB8_1_INT_REG, PWMDB8_1_bINT_MASK
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWMDB8_1_DisableInt
;
;  DESCRIPTION:
;     Disables this PWM's interrupt by clearing the interrupt enable mask bit
;     associated with this User Module.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS: None
;
;  RETURNS: None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWMDB8_1_DisableInt:
_PWMDB8_1_DisableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
   M8C_DisableIntMask PWMDB8_1_INT_REG, PWMDB8_1_bINT_MASK
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWMDB8_1_Start
;
;  DESCRIPTION:
;     Sets the start bit in the Control registers of this user module.  The
;     PWM will begin counting on the next input clock as soon as the
;     enable input is asserted high.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS: None
;
;  RETURNS:  None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWMDB8_1_Start:
_PWMDB8_1_Start:
   RAM_PROLOGUE RAM_USE_CLASS_1
   or    REG[PWMDB8_1_PWM_CONTROL_REG], bfCONTROL_REG_START_BIT
   or    REG[PWMDB8_1_DB_CONTROL_REG], bfCONTROL_REG_START_BIT
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWMDB8_1_Stop
;
;  DESCRIPTION:
;     Disables PWMDB8 operation.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS: None
;
;  RETURNS: None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
;    After this function completes:
;       1) The PWM Counter register will latch any data written to the Period
;          register
;       2) The DB Counter register will latch any data written to the DeadTime
;          Counter register.
;
 PWMDB8_1_Stop:
_PWMDB8_1_Stop:
   RAM_PROLOGUE RAM_USE_CLASS_1
   and   REG[PWMDB8_1_PWM_CONTROL_REG], ~bfCONTROL_REG_START_BIT
   and   REG[PWMDB8_1_DB_CONTROL_REG], ~bfCONTROL_REG_START_BIT
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWMDB8_1_WritePeriod
;
;  DESCRIPTION:
;     Write the period value into the Period register.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     BYTE  bPeriodValue - period count - passed in the Accumulator.
;
;  RETURNS:  None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
;    If the PWMDB8 user module is stopped, then this value will also be
;    latched into the Counter register.
;
 PWMDB8_1_WritePeriod:
_PWMDB8_1_WritePeriod:
   RAM_PROLOGUE RAM_USE_CLASS_1
   mov   REG[PWMDB8_1_PWM_PERIOD_REG], A
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWMDB8_1_WritePulseWidth
;
;  DESCRIPTION:
;     Writes compare value into the PulseWidth register.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     BYTE  bPWidthValue - Pulse Width value count - passed in Accumulator.
;
;  RETURNS: None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;

 PWMDB8_1_WritePulseWidth:
_PWMDB8_1_WritePulseWidth:
   RAM_PROLOGUE RAM_USE_CLASS_1
   mov   REG[PWMDB8_1_PULSE_WIDTH_REG], A
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWMDB8_1_WriteDeadTime
;
;  DESCRIPTION:
;     Writes Dead Time counter value into the DeadTimeCounter register.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     BYTE  bDeadTime - dead time counter value count - passed in Accumulator.
;
;  RETURNS: None
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWMDB8_1_WriteDeadTime:
_PWMDB8_1_WriteDeadTime:
   RAM_PROLOGUE RAM_USE_CLASS_1
   mov   REG[PWMDB8_1_DEAD_TIME_REG], A
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: PWMDB8_1_bReadPulseWidth
;
;  DESCRIPTION:
;     Reads the PulseWidth register.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS: None
;
;  RETURNS:
;     BYTE  bPulseWidth - value read from PulseWidth register - returned
;                           in the Accumulator.
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 PWMDB8_1_bReadPulseWidth:
_PWMDB8_1_bReadPulseWidth:
 bPWMDB8_1_ReadPulseWidth:  ; For backwards compatibility only.
_bPWMDB8_1_ReadPulseWidth:  ; For backwards compatibility only.
   RAM_PROLOGUE RAM_USE_CLASS_1
   mov   A, REG[PWMDB8_1_PULSE_WIDTH_REG]
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret

.ENDSECTION

; End of File PWMDB8_1.asm
