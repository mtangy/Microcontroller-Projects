Project:      output/Lab_7
Build Number: 0
Date:         Thu Mar 19 17:26:26 2015
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   03C6 =    966. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01A0  _welcome
       01C8  _setTempraturePrompt
       0231  _setTolerancePrompt
       02A6  _setThermModePrompt
       0326  _setFanModePrompt
       04B6  LoadConfigTBL_lab5_Bank0
       0523  LoadConfigTBL_lab5_Bank1
       0566  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0566   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       0566  __func_lit_start
       0568  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   0568   0170 =    368. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0568  LoadConfigTBL_lab5_Ordered
       066D  LoadConfigInit
       066D  _LoadConfigInit
       067D  LoadConfig_lab5
       067D  _LoadConfig_lab5
       06D8  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   06D8   077C =   1916. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       06D8  _UART_TX_ISR
       06D9  _UART_RX_ISR
       06DA  UART_EnableInt
       06DA  _UART_EnableInt
       06E1  _UART_DisableInt
       06E1  UART_DisableInt
       06E8  _UART_SetTxIntMode
       06E8  UART_SetTxIntMode
       06FA  UART_Start
       06FA  _UART_Start
       0701  UART_Stop
       0701  _UART_Stop
       0708  UART_SendData
       0708  _UART_SendData
       070B  _UART_bReadTxStatus
       070B  bUART_ReadTxStatus
       070B  UART_bReadTxStatus
       070B  _bUART_ReadTxStatus
       070E  UART_bReadRxData
       070E  _bUART_ReadRxData
       070E  bUART_ReadRxData
       070E  _UART_bReadRxData
       0711  _bUART_ReadRxStatus
       0711  _UART_bReadRxStatus
       0711  bUART_ReadRxStatus
       0711  UART_bReadRxStatus
       0714  UART_TxIntMode
       0714  _UART_TxIntMode
       0727  _UART_IntCntl
       0727  UART_IntCntl
       0752  UART_PutSHexByte
       0752  _UART_PutSHexByte
       0765  UART_PutSHexInt
       0765  _UART_PutSHexInt
       076C  UART_PutChar
       076C  _UART_PutChar
       0774  _UART_cGetChar
       0774  UART_cGetChar
       077C  _UART_cReadChar
       077C  UART_cReadChar
       0793  _UART_iReadChar
       0793  UART_iReadChar
       07A9  _UART_PutString
       07A9  UART_PutString
       07BB  UART_Write
       07BB  _UART_Write
       07E3  UART_CWrite
       07E3  _UART_CWrite
       080F  _UART_CPutString
       080F  UART_CPutString
       0821  _UART_PutCRLF
       0821  UART_PutCRLF
       082A  _LCD_PrCString
       082A  LCD_PrCString
       083C  LCD_HEX_STR
       084C  LCD_PrHexByte
       084C  _LCD_PrHexByte
       085F  _LCD_PrHexInt
       085F  LCD_PrHexInt
       0866  _LCD_PrString
       0866  LCD_PrString
       0878  _LCD_WriteData
       0878  _LCD_Write_Data
       0878  LCD_WriteData
       0878  LCD_Write_Data
       088C  _LCD_Control
       088C  LCD_Control
       093C  _LCD_Start
       093C  LCD_Init
       093C  _LCD_Init
       093C  LCD_Start
       09AB  LCD_ROW_OFFSET
       09AF  LCD_Position
       09AF  _LCD_Position
       09BF  LCD_Delay50uTimes
       09BF  _LCD_Delay50uTimes
       09C5  LCD_Delay50u_Table
       09CD  _LCD_Delay50u
       09CD  LCD_Delay50u
       09E1  I2CHW_Start
       09E1  _I2CHW_Start
       09E2  _I2CHW_ResumeInt
       09E2  I2CHW_ResumeInt
       09E4  I2CHW_EnableInt
       09E4  _I2CHW_EnableInt
       09EB  _I2CHW_ClearInt
       09EB  I2CHW_ClearInt
       09EF  _I2CHW_EnableMstr
       09EF  I2CHW_EnableMstr
       09FF  _I2CHW_DisableInt
       09FF  I2CHW_Stop
       09FF  _I2CHW_Stop
       09FF  I2CHW_DisableInt
       0A03  _I2CHW_DisableMstr
       0A03  I2CHW_DisableMstr
       0A07  _I2CHW_fReadBytes
       0A4B  _I2CHW_bWriteBytes
       0A8F  _I2CHW_bWriteCBytes
       0AFB  _I2CHW_fSendRepeatStart
       0AFB  I2CHW_fSendRepeatStart
       0B37  _I2CHW_fSendStart
       0B37  I2CHW_fSendStart
       0B7B  _I2CHW_fWrite
       0B7B  I2CHW_fWrite
       0BBB  _I2CHW_bRead
       0BBB  I2CHW_bRead
       0BF1  _I2CHW_SendStop
       0BF1  I2CHW_SendStop
       0BFA  I2CHW_bReadBusStatus
       0BFA  _I2CHW_bReadBusStatus
       0C00  _I2CHW_ISR
       0D3D  I2CHW_InitWrite
       0D3D  _I2CHW_InitWrite
       0D7B  I2CHW_InitRamRead
       0D7B  _I2CHW_InitRamRead
       0DA8  _I2CHW_InitFlashRead
       0DA8  I2CHW_InitFlashRead
       0DA9  I2CHW_bReadI2CStatus
       0DA9  _I2CHW_bReadI2CStatus
       0DAF  I2CHW_ClrRdStatus
       0DAF  _I2CHW_ClrRdStatus
       0DB6  I2CHW_ClrWrStatus
       0DB6  _I2CHW_ClrWrStatus
       0DBD  Counter24_EnableInt
       0DBD  _Counter24_EnableInt
       0DC1  Counter24_DisableInt
       0DC1  _Counter24_DisableInt
       0DC5  _Counter24_Start
       0DC5  Counter24_Start
       0DC9  Counter24_Stop
       0DC9  _Counter24_Stop
       0DCD  Counter24_WritePeriod
       0DCD  _Counter24_WritePeriod
       0DDF  Counter24_WriteCompareValue
       0DDF  _Counter24_WriteCompareValue
       0DF1  _Counter24_ReadCompareValue
       0DF1  Counter24_ReadCompareValue
       0E09  _Counter24_ReadCounter
       0E09  Counter24_ReadCounter
       0E54  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0E54   0BC1 =   3009. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0E54  _main
       0E54  __text_start
       1015  _startFunction
       1068  _readFunction
       118B  _stringParser
       1370  _TempReset
       1381  _setTolerenceLevel
       14FF  _T_INT
       1505  _asciiToInt
       1557  _compareParameters
       158E  _cleerLCD
       15B3  _outputConfig
       16B5  _changePOLbit
       174C  _initial
       18D2  _utoa
       1A15  __text_end
       1A15  __xidata_start
       1A3E  __xidata_end

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
       0000  _NO_SHADOW
       0000  Port_2_Data_SHADE
       0000  _Port_2_Data_SHADE
       0000  NO_SHADOW
       0001  Port_2_DriveMode_0_SHADE
       0001  _Port_2_DriveMode_0_SHADE
       0002  _Port_2_DriveMode_1_SHADE
       0002  Port_2_DriveMode_1_SHADE
       0003  _I2CHW_bStatus
       0003  I2CHW_bStatus
       0004  I2CHW_SlaveAddr
       0004  _I2CHW_SlaveAddr
       0005  I2CHW_RsrcStatus
       0005  _I2CHW_RsrcStatus
       0006  _I2CHW_Write_Count
       0006  I2CHW_Write_Count
       0007  _pI2CHW_Write_BufHI
       0007  pI2CHW_Write_BufHI
       0008  pI2CHW_Write_Buf
       0008  pI2CHW_Write_BufLO
       0008  _pI2CHW_Write_BufLO
       0008  _pI2CHW_Write_Buf
       0009  _pI2CHW_Read_BufHI
       0009  pI2CHW_Read_BufHI
       000A  pI2CHW_Read_Buf
       000A  pI2CHW_Read_BufLO
       000A  _pI2CHW_Read_BufLO
       000A  _pI2CHW_Read_Buf
       000B  _I2CHW_Read_Count
       000B  I2CHW_Read_Count

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   00EE   0007 =      7. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       00EE  __rZ
       00EF  __rY
       00F0  __rX
       00F1  __r3
       00F2  __r2
       00F3  __r1
       00F4  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   0234 =    564. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       000C  _messageString
       005B  _rawString
       00AA  _string3
       00BB  _string0
       00CC  _string1
       00DD  _string2
       00F5  _configOutP
       0100  _txBuffer
       01FF  _tolerence
       0200  _THvalue
       0203  _TLvalue
       0206  _THP
       0208  _TLP
       020A  _POLbitFlip
       020C  _tempP
       020E  _j
       0210  _parseCounter
       0212  _rxBuffer
       0214  _addressInt
       0216  _stringSize
       0218  _THvalueTest
       021A  _TLvalueTest
       021C  _configOut
       021E  _configOut2
       0220  _Address_Pointer
       0222  _placeCounter
       0224  _currentTempA
       0226  _i
       0228  _count
       022A  _heatOrCool
       022B  _temp3
       022C  _temp2
       022D  _temp1
       022E  _update
       022F  _Read_Address
       0230  _instBuffer
       0231  _charIn4
       0232  _charIn3
       0233  _status
       0234  _charIn2
       0235  _charIn1
       0236  _charIn
       0237  _accessTH
       0238  _accessTL
       0239  _accessConfigReg
       023A  _fanOn
       023B  _command
       023C  _sizeOfString
       023D  _tempStopConvert
       023E  _tempStartConvert
       023F  _addressHex
       0240  _tempRead
       0241  _TLF
       0242  _THF
       0243  _TL
       0244  _TH
       0245  _firstPass
       0246  _readOrWrite
       0247  _invaildFlag
       0248  _finishFlag
       0249  _hexOrAscii
       024A  _Interupt
       024B  _temp
       024C  _currentTemp2
       024D  _currentTemp1
       024E  _currentTemp
       024F  _Write_Address

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ uartint.asm, uart.asm, psocconfigtbl.asm, psocconfig.asm, lcd.asm, i2chwrsrcinits.asm, i2chwmstr.asm ]
[ i2chwint.asm, i2chwcommon.asm, counter24.asm, rZ.asm, rY.asm, rX.asm, r3.asm, r2.asm, r1.asm, r0.asm ]
[ divmodu_16x16_16_util.asm, divmodu_8x8_8_util.asm, i_div16_block_util.asm, i_div8_block_util.asm ]
[ utoa.s ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0xee
-Blab5_RAM
-rwh:SSCParmBlk:0xf7.0xff

