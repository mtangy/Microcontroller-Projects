Project:      output/LAB_6
Build Number: 0
Date:         Fri Feb 20 21:52:02 2015
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   01B2 =    434. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01A0  _welcomeMsg
       01A9  _instructMsg
       02C6  LoadConfigTBL_lab5_Bank0
       0321  LoadConfigTBL_lab5_Bank1
       0352  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0352   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       0352  __func_lit_start
       0354  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   0354   0170 =    368. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0354  LoadConfigTBL_lab5_Ordered
       0459  LoadConfigInit
       0459  _LoadConfigInit
       0469  LoadConfig_lab5
       0469  _LoadConfig_lab5
       04C4  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   04C4   06E5 =   1765. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       04C4  _UART_TX_ISR
       04C5  _UART_RX_ISR
       04C6  _UART_EnableInt
       04C6  UART_EnableInt
       04CD  UART_DisableInt
       04CD  _UART_DisableInt
       04D4  _UART_SetTxIntMode
       04D4  UART_SetTxIntMode
       04E6  UART_Start
       04E6  _UART_Start
       04ED  _UART_Stop
       04ED  UART_Stop
       04F4  _UART_SendData
       04F4  UART_SendData
       04F7  bUART_ReadTxStatus
       04F7  UART_bReadTxStatus
       04F7  _UART_bReadTxStatus
       04F7  _bUART_ReadTxStatus
       04FA  UART_bReadRxData
       04FA  bUART_ReadRxData
       04FA  _bUART_ReadRxData
       04FA  _UART_bReadRxData
       04FD  UART_bReadRxStatus
       04FD  _UART_bReadRxStatus
       04FD  _bUART_ReadRxStatus
       04FD  bUART_ReadRxStatus
       0500  UART_TxIntMode
       0500  _UART_TxIntMode
       0513  _UART_IntCntl
       0513  UART_IntCntl
       053E  UART_PutSHexByte
       053E  _UART_PutSHexByte
       0551  _UART_PutSHexInt
       0551  UART_PutSHexInt
       0558  _UART_PutChar
       0558  UART_PutChar
       0560  _UART_cGetChar
       0560  UART_cGetChar
       0568  _UART_cReadChar
       0568  UART_cReadChar
       057F  _UART_iReadChar
       057F  UART_iReadChar
       0595  _UART_PutString
       0595  UART_PutString
       05A7  _UART_Write
       05A7  UART_Write
       05CF  UART_CWrite
       05CF  _UART_CWrite
       05FB  _UART_CPutString
       05FB  UART_CPutString
       060D  UART_PutCRLF
       060D  _UART_PutCRLF
       0616  LCD_PrCString
       0616  _LCD_PrCString
       0628  LCD_HEX_STR
       0638  LCD_PrHexByte
       0638  _LCD_PrHexByte
       064B  _LCD_PrHexInt
       064B  LCD_PrHexInt
       0652  _LCD_PrString
       0652  LCD_PrString
       0664  _LCD_WriteData
       0664  LCD_Write_Data
       0664  _LCD_Write_Data
       0664  LCD_WriteData
       0678  LCD_Control
       0678  _LCD_Control
       0728  LCD_Init
       0728  _LCD_Init
       0728  _LCD_Start
       0728  LCD_Start
       0797  LCD_ROW_OFFSET
       079B  LCD_Position
       079B  _LCD_Position
       07AB  LCD_Delay50uTimes
       07AB  _LCD_Delay50uTimes
       07B1  LCD_Delay50u_Table
       07B9  LCD_Delay50u
       07B9  _LCD_Delay50u
       07CD  _I2CHW_Start
       07CD  I2CHW_Start
       07CE  _I2CHW_ResumeInt
       07CE  I2CHW_ResumeInt
       07D0  _I2CHW_EnableInt
       07D0  I2CHW_EnableInt
       07D7  _I2CHW_ClearInt
       07D7  I2CHW_ClearInt
       07DB  _I2CHW_EnableMstr
       07DB  I2CHW_EnableMstr
       07EB  I2CHW_Stop
       07EB  _I2CHW_DisableInt
       07EB  I2CHW_DisableInt
       07EB  _I2CHW_Stop
       07EF  I2CHW_DisableMstr
       07EF  _I2CHW_DisableMstr
       07F3  _I2CHW_fReadBytes
       0837  _I2CHW_bWriteBytes
       087B  _I2CHW_bWriteCBytes
       08E7  I2CHW_fSendRepeatStart
       08E7  _I2CHW_fSendRepeatStart
       0923  _I2CHW_fSendStart
       0923  I2CHW_fSendStart
       0967  I2CHW_fWrite
       0967  _I2CHW_fWrite
       09A7  I2CHW_bRead
       09A7  _I2CHW_bRead
       09DD  _I2CHW_SendStop
       09DD  I2CHW_SendStop
       09E6  _I2CHW_bReadBusStatus
       09E6  I2CHW_bReadBusStatus
       09EC  _I2CHW_ISR
       0B29  _I2CHW_InitWrite
       0B29  I2CHW_InitWrite
       0B67  _I2CHW_InitRamRead
       0B67  I2CHW_InitRamRead
       0B94  I2CHW_InitFlashRead
       0B94  _I2CHW_InitFlashRead
       0B95  I2CHW_bReadI2CStatus
       0B95  _I2CHW_bReadI2CStatus
       0B9B  _I2CHW_ClrRdStatus
       0B9B  I2CHW_ClrRdStatus
       0BA2  _I2CHW_ClrWrStatus
       0BA2  I2CHW_ClrWrStatus
       0BA9  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0BA9   03D5 =    981. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0BA9  __text_start
       0BA9  _main
       0C29  _startFunction
       0C50  _readFunction
       0D4A  _stringParser
       0F54  _instructions
       0F7E  __xidata_start
       0F7E  __text_end
       0F8C  __xidata_end

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
               virtual_registers   0108   0005 =      5. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0108  __rY
       0109  __rX
       010A  __r3
       010B  __r1
       010C  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   0106 =    262. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       000C  _messageString
       005B  _rawString
       00AA  _string3
       00BB  _string1
       00CC  _string0
       00DD  _string2
       00EE  _rxBuffer
       00F6  _status
       0100  _txBuffer
       010D  _count
       010F  _placeCounter
       0111  _address
       0113  _parseCounter
       0115  _Read_Address
       0117  _charIn2
       0118  _charIn3
       0119  _ramSelect
       011A  _charIn
       011B  _charIn4
       011C  _invaildFlag
       011D  _finishFlag
       011E  _charIn1
       011F  _instBuffer

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ uartint.asm, uart.asm, psocconfigtbl.asm, psocconfig.asm, lcd.asm, i2chwrsrcinits.asm, i2chwmstr.asm ]
[ i2chwint.asm, i2chwcommon.asm, rY.asm, rX.asm, r3.asm, r1.asm, r0.asm ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x108
-Blab5_RAM
-rwh:SSCParmBlk:0xf7.0xff

