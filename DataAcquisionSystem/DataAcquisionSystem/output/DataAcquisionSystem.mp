Project:      output/DataAcquisionSystem
Build Number: 0
Date:         Mon Apr 20 22:59:22 2015
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   042A =   1066. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       04D6  LoadConfigTBL_DataAcqSystem_Bank0
       0581  LoadConfigTBL_DataAcqSystem_Bank1
       05CA  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   05CA   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       05CA  __func_lit_start
       05CC  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   05CC   0170 =    368. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       05CC  LoadConfigTBL_DataAcqSystem_Ordered
       06D1  LoadConfigInit
       06D1  _LoadConfigInit
       06E1  _LoadConfig_DataAcqSystem
       06E1  LoadConfig_DataAcqSystem
       073C  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   073C   060E =   1550. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       073C  _UART_TX_ISR
       073D  _UART_RX_ISR
       073E  UART_EnableInt
       073E  _UART_EnableInt
       0745  UART_DisableInt
       0745  _UART_DisableInt
       074C  UART_SetTxIntMode
       074C  _UART_SetTxIntMode
       075E  _UART_Start
       075E  UART_Start
       0765  _UART_Stop
       0765  UART_Stop
       076C  _UART_SendData
       076C  UART_SendData
       076F  bUART_ReadTxStatus
       076F  UART_bReadTxStatus
       076F  _UART_bReadTxStatus
       076F  _bUART_ReadTxStatus
       0772  UART_bReadRxData
       0772  _UART_bReadRxData
       0772  _bUART_ReadRxData
       0772  bUART_ReadRxData
       0775  _bUART_ReadRxStatus
       0775  UART_bReadRxStatus
       0775  bUART_ReadRxStatus
       0775  _UART_bReadRxStatus
       0778  _UART_TxIntMode
       0778  UART_TxIntMode
       078B  _UART_IntCntl
       078B  UART_IntCntl
       07B6  UART_PutSHexByte
       07B6  _UART_PutSHexByte
       07C9  _UART_PutSHexInt
       07C9  UART_PutSHexInt
       07D0  _UART_PutChar
       07D0  UART_PutChar
       07D8  UART_cGetChar
       07D8  _UART_cGetChar
       07E0  UART_cReadChar
       07E0  _UART_cReadChar
       07F7  _UART_iReadChar
       07F7  UART_iReadChar
       080D  UART_PutString
       080D  _UART_PutString
       081F  _UART_Write
       081F  UART_Write
       0847  _UART_CWrite
       0847  UART_CWrite
       0873  _UART_CPutString
       0873  UART_CPutString
       0885  _UART_PutCRLF
       0885  UART_PutCRLF
       088E  _SPIM_ISR
       088F  _SPIM_EnableInt
       088F  SPIM_EnableInt
       0893  _SPIM_DisableInt
       0893  SPIM_DisableInt
       0897  _SPIM_Start
       0897  SPIM_Start
       089C  _SPIM_Stop
       089C  SPIM_Stop
       08A0  SPIM_SendTxData
       08A0  _SPIM_SendTxData
       08A3  _bSPIM_ReadRxData
       08A3  SPIM_bReadRxData
       08A3  bSPIM_ReadRxData
       08A3  _SPIM_bReadRxData
       08A6  _SPIM_bReadStatus
       08A6  SPIM_bReadStatus
       08A6  bSPIM_ReadStatus
       08A6  _bSPIM_ReadStatus
       08A9  _SleepTimer_ISR
       08C9  _PGA_Start
       08C9  PGA_Start
       08C9  PGA_SetPower
       08C9  _PGA_SetPower
       08DB  _PGA_SetGain
       08DB  PGA_SetGain
       0905  PGA_Stop
       0905  _PGA_Stop
       0909  _LCD_PrCString
       0909  LCD_PrCString
       091B  LCD_HEX_STR
       092B  _LCD_PrHexByte
       092B  LCD_PrHexByte
       093E  LCD_PrHexInt
       093E  _LCD_PrHexInt
       0945  LCD_PrString
       0945  _LCD_PrString
       0957  LCD_Write_Data
       0957  _LCD_Write_Data
       0957  LCD_WriteData
       0957  _LCD_WriteData
       096B  _LCD_Control
       096B  LCD_Control
       0A1B  LCD_Start
       0A1B  _LCD_Init
       0A1B  LCD_Init
       0A1B  _LCD_Start
       0A8A  LCD_ROW_OFFSET
       0A8E  _LCD_Position
       0A8E  LCD_Position
       0A9E  _LCD_Delay50uTimes
       0A9E  LCD_Delay50uTimes
       0AA4  LCD_Delay50u_Table
       0AAC  LCD_Delay50u
       0AAC  _LCD_Delay50u
       0AC0  _DelSig_ADConversion_ISR
       0AD6  _DelSigClock_ISR
       0AD7  _DelSigClock_EnableInt
       0AD7  DelSigClock_EnableInt
       0ADB  DelSigClock_DisableInt
       0ADB  _DelSigClock_DisableInt
       0ADF  _DelSigClock_Start
       0ADF  DelSigClock_Start
       0AE3  _DelSigClock_Stop
       0AE3  DelSigClock_Stop
       0AE7  DelSigClock_WritePeriod
       0AE7  _DelSigClock_WritePeriod
       0AEA  DelSigClock_WriteCompareValue
       0AEA  _DelSigClock_WriteCompareValue
       0AED  bDelSigClock_ReadCompareValue
       0AED  _DelSigClock_bReadCompareValue
       0AED  _bDelSigClock_ReadCompareValue
       0AED  DelSigClock_bReadCompareValue
       0AF0  DelSigClock_bReadCounter
       0AF0  bDelSigClock_ReadCounter
       0AF0  _bDelSigClock_ReadCounter
       0AF0  _DelSigClock_bReadCounter
       0B21  DelSig_Start
       0B21  _DelSig_Start
       0B21  _DelSig_SetPower
       0B21  DelSig_SetPower
       0B3B  DelSig_Stop
       0B3B  _DelSig_Stop
       0B42  DelSig_StartAD
       0B42  _DelSig_StartAD
       0B49  _DelSig_StopAD
       0B49  DelSig_StopAD
       0B50  _DelSig_fIsDataAvailable
       0B50  DelSig_fIsDataAvailable
       0B56  _DelSig_cGetDataClearFlag
       0B56  _DelSig_bGetDataClearFlag
       0B56  DelSig_bGetDataClearFlag
       0B56  DelSig_cGetDataClearFlag
       0B65  _DelSig_cGetData
       0B65  DelSig_cGetData
       0B65  _DelSig_bGetData
       0B65  DelSig_bGetData
       0B6B  _DelSig_ClearFlag
       0B6B  DelSig_ClearFlag
       0B72  _DelSig_WritePulseWidth
       0B72  DelSig_WritePulseWidth
       0B75  DACUpdate_EnableInt
       0B75  _DACUpdate_EnableInt
       0B79  _DACUpdate_DisableInt
       0B79  DACUpdate_DisableInt
       0B7D  _DACUpdate_Start
       0B7D  DACUpdate_Start
       0B81  DACUpdate_Stop
       0B81  _DACUpdate_Stop
       0B85  DACUpdate_WritePeriod
       0B85  _DACUpdate_WritePeriod
       0B88  _DACUpdate_WriteCompareValue
       0B88  DACUpdate_WriteCompareValue
       0B8B  DACUpdate_bReadCompareValue
       0B8B  _bDACUpdate_ReadCompareValue
       0B8B  _DACUpdate_bReadCompareValue
       0B8B  bDACUpdate_ReadCompareValue
       0B8E  bDACUpdate_ReadCounter
       0B8E  _DACUpdate_bReadCounter
       0B8E  DACUpdate_bReadCounter
       0B8E  _bDACUpdate_ReadCounter
       0BBF  DAC8B_SetPower
       0BBF  _DAC8B_Start
       0BBF  _DAC8B_SetPower
       0BBF  DAC8B_Start
       0BD9  _DAC8B_WriteBlind
       0BD9  DAC8B_WriteBlind
       0C13  _DAC8B_WriteBlind2B
       0C13  DAC8B_WriteBlind2B
       0C1E  DAC8B_WriteStall
       0C1E  _DAC8B_WriteStall
       0C5E  _DAC8B_WriteStall2B
       0C5E  DAC8B_WriteStall2B
       0C6F  DAC8B_Stop
       0C6F  _DAC8B_Stop
       0C76  DAC8A_SetPower
       0C76  _DAC8A_SetPower
       0C76  DAC8A_Start
       0C76  _DAC8A_Start
       0C90  _DAC8A_WriteBlind
       0C90  DAC8A_WriteBlind
       0CCA  DAC8A_WriteBlind2B
       0CCA  _DAC8A_WriteBlind2B
       0CD5  _DAC8A_WriteStall
       0CD5  DAC8A_WriteStall
       0D15  DAC8A_WriteStall2B
       0D15  _DAC8A_WriteStall2B
       0D26  _DAC8A_Stop
       0D26  DAC8A_Stop
       0D2D  AMUX4_InputSelect
       0D2D  _AMUX4_InputSelect
       0D48  AMUX4_Start
       0D48  _AMUX4_Start
       0D49  _AMUX4_Stop
       0D49  AMUX4_Stop
       0D4A  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0D4A   0E29 =   3625. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0D4A  __text_start
       0D4A  _main
       10F3  _DACUpdate_ISR
       1104  _readFunction
       11FE  _stringParser
       1518  _instruction1
       1532  _instruction2
       154C  _instruction3
       1566  _instruction4
       159A  _instruction5
       15B4  _instruction6
       15CE  _instruction7
       15E8  _ascii_to_hex
       164E  _toLower
       166B  _hexToDec
       174C  _SPIRAM_WriteStatusRegister
       17D1  _SPIRAM_ReadStatusRegister
       183D  _SPIRAM_WriteByte
       18E0  _SPIRAM_ReadByte
       1987  _SPIRAM_WriteArray
       1A91  _SPIRAM_ReadArray
       1B73  __xidata_start
       1B73  __text_end
       1B9C  __xidata_end

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
                    InterruptRAM   0000   000C =     12. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  SleepTimer_fTick
       0000  _SleepTimer_fTick
       0001  SleepTimer_bTimerValue
       0001  _SleepTimer_bTimerValue
       0002  SleepTimer_bCountDown
       0002  _SleepTimer_bCountDown
       0003  SleepTimer_TickCount
       0003  _SleepTimer_TickCount
       0007  _NO_SHADOW
       0007  Port_2_Data_SHADE
       0007  NO_SHADOW
       0007  _Port_2_Data_SHADE
       0008  _Port_2_DriveMode_0_SHADE
       0008  Port_2_DriveMode_0_SHADE
       0009  _Port_2_DriveMode_1_SHADE
       0009  Port_2_DriveMode_1_SHADE
       000A  _DelSig_cResult
       000A  DelSig_cResult
       000B  DelSig_bfStatus
       000B  _DelSig_bfStatus

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   005E   0004 =      4. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       005E  __rX
       005F  __r3
       0060  __r1
       0061  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   0078 =    120. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       000C  _rawString
       004C  _sampleRateS
       0062  _fScaleFactor
       0066  _voltage
       006A  _j
       006C  _pResult
       006E  _trigAdr
       0070  _k
       0072  _blockNum
       0074  _parseNum
       0076  _blockNum2
       0078  _i
       007A  _sampleRate
       007C  _iStatus
       007E  _finishFlag
       007F  _displayOrcapture
       0080  _validMode
       0081  _Svalue
       0082  _sampleRead
       0083  _error
       0084  _inA
       0085  _done
       0086  _DACUpdateDone
       0087  _charIn

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
obj/spi_sram.o	[ spi_sram.c ]
<library>	[ uartint.asm, uart.asm, spimint.asm, spim.asm, sleeptimerint.asm, psocconfigtbl.asm, psocconfig.asm ]
[ pga.asm, lcd.asm, delsigint.asm, delsigclockint.asm, delsigclock.asm, delsig.asm, dacupdate.asm ]
[ dac8b.asm, dac8a.asm, amux4.asm, rX.asm, r3.asm, r1.asm, r0.asm ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x5e
-BDataAcqSystem_RAM
-rwh:SSCParmBlk:0xf7.0xff

