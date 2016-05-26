Project:      output/ps2bitbang
Build Number: 0
Date:         Thu Mar 19 18:44:27 2015
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   047A =   1146. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01A0  _ShiftableScancode
       01E8  _AlphabetScancode
       0239  _ControlScancode
       0279  _KeypadScancode
       0291  _PianoScancode
       04F2  LoadConfigTBL_ps2bitbang_Bank0
       059B  LoadConfigTBL_ps2bitbang_Bank1
       061A  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   061A   0030 =     48. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       061A  __func_lit_start
       064A  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   064A   0173 =    371. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       064A  LoadConfigTBL_ps2bitbang_Ordered
       074F  _LoadConfigInit
       074F  LoadConfigInit
       0762  _LoadConfig_ps2bitbang
       0762  LoadConfig_ps2bitbang
       07BD  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   07BD   054C =   1356. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       07BD  _UART_TX_ISR
       07BE  _UART_RX_ISR
       07BF  _UARTClock_ISR
       07C0  _UARTClock_EnableInt
       07C0  UARTClock_EnableInt
       07C4  UARTClock_DisableInt
       07C4  _UARTClock_DisableInt
       07C8  _UARTClock_Start
       07C8  UARTClock_Start
       07CC  _UARTClock_Stop
       07CC  UARTClock_Stop
       07D0  _UARTClock_WritePeriod
       07D0  UARTClock_WritePeriod
       07D6  UARTClock_WriteCompareValue
       07D6  _UARTClock_WriteCompareValue
       07DC  UARTClock_wReadCompareValue
       07DC  _wUARTClock_ReadCompareValue
       07DC  _UARTClock_wReadCompareValue
       07DC  wUARTClock_ReadCompareValue
       07E2  _UARTClock_wReadCounter
       07E2  wUARTClock_ReadCounter
       07E2  _wUARTClock_ReadCounter
       07E2  UARTClock_wReadCounter
       0820  _UART_EnableInt
       0820  UART_EnableInt
       0827  _UART_DisableInt
       0827  UART_DisableInt
       082E  _UART_SetTxIntMode
       082E  UART_SetTxIntMode
       0840  _UART_Start
       0840  UART_Start
       0847  _UART_Stop
       0847  UART_Stop
       084E  _UART_SendData
       084E  UART_SendData
       0851  bUART_ReadTxStatus
       0851  UART_bReadTxStatus
       0851  _UART_bReadTxStatus
       0851  _bUART_ReadTxStatus
       0854  bUART_ReadRxData
       0854  _UART_bReadRxData
       0854  UART_bReadRxData
       0854  _bUART_ReadRxData
       0857  UART_bReadRxStatus
       0857  _bUART_ReadRxStatus
       0857  _UART_bReadRxStatus
       0857  bUART_ReadRxStatus
       085A  _UART_TxIntMode
       085A  UART_TxIntMode
       086D  UART_IntCntl
       086D  _UART_IntCntl
       0898  UART_PutSHexByte
       0898  _UART_PutSHexByte
       08AB  UART_PutSHexInt
       08AB  _UART_PutSHexInt
       08B2  _UART_PutChar
       08B2  UART_PutChar
       08BA  UART_cGetChar
       08BA  _UART_cGetChar
       08C2  UART_cReadChar
       08C2  _UART_cReadChar
       08D9  UART_iReadChar
       08D9  _UART_iReadChar
       08EF  UART_PutString
       08EF  _UART_PutString
       0901  _UART_Write
       0901  UART_Write
       0929  UART_CWrite
       0929  _UART_CWrite
       0955  _UART_CPutString
       0955  UART_CPutString
       0967  UART_PutCRLF
       0967  _UART_PutCRLF
       0970  TenMicroSecTimer_EnableInt
       0970  _TenMicroSecTimer_EnableInt
       0974  _TenMicroSecTimer_DisableInt
       0974  TenMicroSecTimer_DisableInt
       0978  _TenMicroSecTimer_Start
       0978  TenMicroSecTimer_Start
       097C  _TenMicroSecTimer_Stop
       097C  TenMicroSecTimer_Stop
       0980  TenMicroSecTimer_WritePeriod
       0980  _TenMicroSecTimer_WritePeriod
       0986  TenMicroSecTimer_WriteCompareValue
       0986  _TenMicroSecTimer_WriteCompareValue
       098C  _TenMicroSecTimer_wReadCompareValue
       098C  _wTenMicroSecTimer_ReadCompareValue
       098C  TenMicroSecTimer_wReadCompareValue
       098C  wTenMicroSecTimer_ReadCompareValue
       0992  TenMicroSecTimer_wReadTimerSaveCV
       0992  wTenMicroSecTimer_ReadTimerSaveCV
       0992  _TenMicroSecTimer_wReadTimerSaveCV
       0992  _wTenMicroSecTimer_ReadTimerSaveCV
       0992  wTenMicroSecTimer_ReadCounter
       0992  _wTenMicroSecTimer_ReadCounter
       09C8  wTenMicroSecTimer_ReadTimer
       09C8  wTenMicroSecTimer_CaptureCounter
       09C8  TenMicroSecTimer_wReadTimer
       09C8  _wTenMicroSecTimer_CaptureCounter
       09C8  _TenMicroSecTimer_wReadTimer
       09C8  _wTenMicroSecTimer_ReadTimer
       09D0  _PWMPiano3_ISR
       09D1  PWMPiano3_EnableInt
       09D1  _PWMPiano3_EnableInt
       09D5  PWMPiano3_DisableInt
       09D5  _PWMPiano3_DisableInt
       09D9  PWMPiano3_Start
       09D9  _PWMPiano3_Start
       09DD  _PWMPiano3_Stop
       09DD  PWMPiano3_Stop
       09E1  _PWMPiano3_WritePeriod
       09E1  PWMPiano3_WritePeriod
       09E7  _PWMPiano3_WritePulseWidth
       09E7  PWMPiano3_WritePulseWidth
       09ED  _wPWMPiano3_ReadPulseWidth
       09ED  PWMPiano3_wReadPulseWidth
       09ED  _PWMPiano3_wReadPulseWidth
       09ED  wPWMPiano3_ReadPulseWidth
       09F3  _wPWMPiano3_ReadCounter
       09F3  _PWMPiano3_wReadCounter
       09F3  wPWMPiano3_ReadCounter
       09F3  PWMPiano3_wReadCounter
       0A2D  _PWMPiano2_ISR
       0A2E  PWMPiano2_EnableInt
       0A2E  _PWMPiano2_EnableInt
       0A32  PWMPiano2_DisableInt
       0A32  _PWMPiano2_DisableInt
       0A36  _PWMPiano2_Start
       0A36  PWMPiano2_Start
       0A3A  PWMPiano2_Stop
       0A3A  _PWMPiano2_Stop
       0A3E  PWMPiano2_WritePeriod
       0A3E  _PWMPiano2_WritePeriod
       0A44  PWMPiano2_WritePulseWidth
       0A44  _PWMPiano2_WritePulseWidth
       0A4A  PWMPiano2_wReadPulseWidth
       0A4A  _wPWMPiano2_ReadPulseWidth
       0A4A  _PWMPiano2_wReadPulseWidth
       0A4A  wPWMPiano2_ReadPulseWidth
       0A50  _wPWMPiano2_ReadCounter
       0A50  PWMPiano2_wReadCounter
       0A50  _PWMPiano2_wReadCounter
       0A50  wPWMPiano2_ReadCounter
       0A8A  _PWMPiano1_ISR
       0A8B  PWMPiano1_EnableInt
       0A8B  _PWMPiano1_EnableInt
       0A8F  _PWMPiano1_DisableInt
       0A8F  PWMPiano1_DisableInt
       0A93  _PWMPiano1_Start
       0A93  PWMPiano1_Start
       0A97  _PWMPiano1_Stop
       0A97  PWMPiano1_Stop
       0A9B  PWMPiano1_WritePeriod
       0A9B  _PWMPiano1_WritePeriod
       0AA1  _PWMPiano1_WritePulseWidth
       0AA1  PWMPiano1_WritePulseWidth
       0AA7  _wPWMPiano1_ReadPulseWidth
       0AA7  wPWMPiano1_ReadPulseWidth
       0AA7  _PWMPiano1_wReadPulseWidth
       0AA7  PWMPiano1_wReadPulseWidth
       0AAD  wPWMPiano1_ReadCounter
       0AAD  PWMPiano1_wReadCounter
       0AAD  _wPWMPiano1_ReadCounter
       0AAD  _PWMPiano1_wReadCounter
       0AE7  _PWM8LED_ISR
       0AE8  _PWM8LED_EnableInt
       0AE8  PWM8LED_EnableInt
       0AEC  PWM8LED_DisableInt
       0AEC  _PWM8LED_DisableInt
       0AF0  _PWM8LED_Start
       0AF0  PWM8LED_Start
       0AF4  PWM8LED_Stop
       0AF4  _PWM8LED_Stop
       0AF8  _PWM8LED_WritePeriod
       0AF8  PWM8LED_WritePeriod
       0AFB  _PWM8LED_WritePulseWidth
       0AFB  PWM8LED_WritePulseWidth
       0AFE  PWM8LED_bReadPulseWidth
       0AFE  bPWM8LED_ReadPulseWidth
       0AFE  _PWM8LED_bReadPulseWidth
       0AFE  _bPWM8LED_ReadPulseWidth
       0B01  _bPWM8LED_ReadCounter
       0B01  bPWM8LED_ReadCounter
       0B01  PWM8LED_bReadCounter
       0B01  _PWM8LED_bReadCounter
       0B2E  _PS2OneShot_Start
       0B2E  PS2OneShot_Start
       0B32  PS2OneShot_Stop
       0B32  _PS2OneShot_Stop
       0B36  _PS2OneShot_EnableInt
       0B36  PS2OneShot_EnableInt
       0B3A  _PS2OneShot_DisableInt
       0B3A  PS2OneShot_DisableInt
       0B3E  PS2OneShot_ClearInt
       0B3E  _PS2OneShot_ClearInt
       0B42  PS2DigBuf_EnableInt
       0B42  _PS2DigBuf_EnableInt
       0B46  PS2DigBuf_DisableInt
       0B46  _PS2DigBuf_DisableInt
       0B4A  PS2DigBuf_Start
       0B4A  _PS2DigBuf_Start
       0B4E  PS2DigBuf_Stop
       0B4E  _PS2DigBuf_Stop
       0B52  LCD_PrCString
       0B52  _LCD_PrCString
       0B64  LCD_HEX_STR
       0B74  LCD_PrHexByte
       0B74  _LCD_PrHexByte
       0B87  _LCD_PrHexInt
       0B87  LCD_PrHexInt
       0B8E  LCD_PrString
       0B8E  _LCD_PrString
       0BA0  LCD_Write_Data
       0BA0  LCD_WriteData
       0BA0  _LCD_Write_Data
       0BA0  _LCD_WriteData
       0BB4  LCD_Control
       0BB4  _LCD_Control
       0C64  _LCD_Start
       0C64  LCD_Init
       0C64  LCD_Start
       0C64  _LCD_Init
       0CD3  LCD_ROW_OFFSET
       0CD7  _LCD_Position
       0CD7  LCD_Position
       0CE7  _LCD_Delay50uTimes
       0CE7  LCD_Delay50uTimes
       0CED  LCD_Delay50u_Table
       0CF5  _LCD_Delay50u
       0CF5  LCD_Delay50u
       0D09  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0D09   20D1 =   8401. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0D09  _KeyboardDecodeData
       0D09  __text_start
       0E61  _KeyboardTotalPressed
       1033  _KeyboardToASCII
       14C3  _KeyboardAction
       1C62  _main
       1F61  _MouseInit
       1F9E  _MousePrintRawData
       204C  _MouseCursor
       2511  _PS2_Write_Byte
       2607  _PS2_Send_Command_Process_Response
       2722  _PS2_Detect_Device
       28A4  _PS2DigBuf_ISR
       2D63  _PS2OneShot_ISR
       2D8C  _TenMicroSecTimer_ISR
       2DDA  __xidata_start
       2DDA  __text_end
       2DF4  __xidata_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   0146 =    326. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0068  __Start
       0143  _bGetPowerSetting
       0143  bGetPowerSetting

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                    InterruptRAM   0000   0004 =      4. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  NO_SHADOW
       0000  Port_1_Data_SHADE
       0000  _NO_SHADOW
       0000  _Port_1_Data_SHADE
       0001  _Port_2_Data_SHADE
       0001  Port_2_Data_SHADE
       0002  Port_2_DriveMode_0_SHADE
       0002  _Port_2_DriveMode_0_SHADE
       0003  Port_2_DriveMode_1_SHADE
       0003  _Port_2_DriveMode_1_SHADE

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   0014   000F =     15. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0014  __rZ
       0015  __rY
       0016  __rX
       0017  __r11
       0018  __r10
       0019  __r9
       001A  __r8
       001B  __r7
       001C  __r6
       001D  __r5
       001E  __r4
       001F  __r3
       0020  __r2
       0021  __r1
       0022  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   006B =    107. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       0004  _PS2RxBuffer
       0062  _PS2FrameStatus
       0064  _PS2RxBufOut
       0065  _TenMicroSecTimerReps
       0066  _NumLock
       0067  _CapsLock
       0068  _ScrollLock
       0069  _ShiftDown
       006A  _CtrlDown
       006B  _AltDown
       006C  _PianoMode
       006D  _IsMouse
       006E  _DeleteDown
       0072  _PS2RxBufIn
       0077  ps2.c:PS2FrameState
       0078  ps2.c:PS2DataIn
       0079  ps2.c:PS2DataOut
       007A  ps2.c:XXXForceBadRxParity
       007B  ps2.c:XXXForceBadTxParity

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/keyboard.o	[ keyboard.c ]
obj/main.o	[ main.c ]
obj/mouse.o	[ mouse.c ]
obj/ps2.o	[ ps2.c ]
<library>	[ uartint.asm, uartclockint.asm, uartclock.asm, uart.asm, tenmicrosectimer.asm, pwmpiano3int.asm ]
[ pwmpiano3.asm, pwmpiano2int.asm, pwmpiano2.asm, pwmpiano1int.asm, pwmpiano1.asm, pwm8ledint.asm ]
[ pwm8led.asm, psocconfigtbl.asm, psocconfig.asm, ps2oneshot.asm, ps2digbuf.asm, lcd.asm, rZ.asm ]
[ rY.asm, rX.asm, r11.asm, r10.asm, r9.asm, r8.asm, r7.asm, r6.asm, r5.asm, r4.asm, r3.asm, r2.asm, r1.asm ]
[ r0.asm, mul16_util.asm ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x14
-Bps2bitbang_RAM	allocated at: 0
-rwh:SSCParmBlk:0xf7.0xff

