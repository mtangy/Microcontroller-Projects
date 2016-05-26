;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: SW2Buf.asm
;;  Version: 1.3, Updated on 2013/5/19 at 10:43:26
;;  Generated by PSoC Designer 5.4.2946
;;
;;  DESCRIPTION: DigitalBuffers User Module software implementation file
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
;;  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"
include "memory.inc"
include "SW2Buf.inc"

;-----------------------------------------------
;  Global Symbols
;-----------------------------------------------
export  SW2Buf_EnableInt
export _SW2Buf_EnableInt
export  SW2Buf_DisableInt
export _SW2Buf_DisableInt
export  SW2Buf_Start
export _SW2Buf_Start
export  SW2Buf_Stop
export _SW2Buf_Stop

AREA bss (RAM,REL)

;-----------------------------------------------
;  Constant Definitions
;-----------------------------------------------


;-----------------------------------------------
; Variable Allocation
;-----------------------------------------------


AREA UserModules (ROM, REL)

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SW2Buf_EnableInt
;
;  DESCRIPTION:
;     Enables the DigBuf's interrupt by setting the interrupt enable mask bit
;     associated with this User Module. This function has no effect until and
;     unless the global interrupts are enabled (for example by using the
;     macro M8C_EnableGInt).
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None.
;  RETURNS:      Nothing.
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 SW2Buf_EnableInt:
_SW2Buf_EnableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1   
   SW2Buf_EnableInt_M
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret

.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SW2Buf_DisableInt
;
;  DESCRIPTION:
;     Disables the DigBuf's interrupt by clearing the interrupt enable mask bit
;     associated with this User Module. 
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None.
;  RETURNS:      Nothing.
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 SW2Buf_DisableInt:
_SW2Buf_DisableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1   
   SW2Buf_DisableInt_M
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret

.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SW2Buf_Start
;
;  DESCRIPTION:
;     Starts the Digital Buffers within the block.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None
;  RETURNS:      Nothing
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 SW2Buf_Start:
_SW2Buf_Start:
   RAM_PROLOGUE RAM_USE_CLASS_1
   SW2Buf_Start_M
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret

.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SW2Buf_Stop
;
;  DESCRIPTION:
;     Stops the Digital Buffers within the block. The outputs are driven low.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:    None
;  RETURNS:      Nothing
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 SW2Buf_Stop:
_SW2Buf_Stop:
   RAM_PROLOGUE RAM_USE_CLASS_1
   SW2Buf_Stop_M
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret

.ENDSECTION


; End of File SW2Buf.asm


