Project:      output/LAB4_Part2
Build Number: 0
Date:         Tue Feb 03 18:10:45 2015
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   00E9 =    233. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01D9  LoadConfigTBL_lab3_2_Bank0
       0246  LoadConfigTBL_lab3_2_Bank1
       0289  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0289   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       0289  __func_lit_start
       028B  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   028B   0170 =    368. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       028B  LoadConfigTBL_lab3_2_Ordered
       0390  _LoadConfigInit
       0390  LoadConfigInit
       03A0  _LoadConfig_lab3_2
       03A0  LoadConfig_lab3_2
       03FB  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   03FB   0229 =    553. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       03FB  LCD_PrCString
       03FB  _LCD_PrCString
       040D  LCD_HEX_STR
       041D  _LCD_PrHexByte
       041D  LCD_PrHexByte
       0430  LCD_PrHexInt
       0430  _LCD_PrHexInt
       0437  LCD_PrString
       0437  _LCD_PrString
       0449  _LCD_WriteData
       0449  _LCD_Write_Data
       0449  LCD_WriteData
       0449  LCD_Write_Data
       045D  LCD_Control
       045D  _LCD_Control
       050D  LCD_Start
       050D  _LCD_Start
       050D  _LCD_Init
       050D  LCD_Init
       057C  LCD_ROW_OFFSET
       0580  LCD_Position
       0580  _LCD_Position
       0590  LCD_Delay50uTimes
       0590  _LCD_Delay50uTimes
       0596  LCD_Delay50u_Table
       059E  LCD_Delay50u
       059E  _LCD_Delay50u
       05B2  _DigBuf_EnableInt
       05B2  DigBuf_EnableInt
       05B6  DigBuf_DisableInt
       05B6  _DigBuf_DisableInt
       05BA  _DigBuf_Start
       05BA  DigBuf_Start
       05BE  _DigBuf_Stop
       05BE  DigBuf_Stop
       05C2  _Counter16_ISR
       05C3  _Counter16_1_ISR
       05C4  _Counter16_EnableInt
       05C4  Counter16_EnableInt
       05C8  _Counter16_DisableInt
       05C8  Counter16_DisableInt
       05CC  _Counter16_Start
       05CC  Counter16_Start
       05D0  _Counter16_Stop
       05D0  Counter16_Stop
       05D4  Counter16_WritePeriod
       05D4  _Counter16_WritePeriod
       05DA  _Counter16_WriteCompareValue
       05DA  Counter16_WriteCompareValue
       05E0  wCounter16_ReadCompareValue
       05E0  _Counter16_wReadCompareValue
       05E0  Counter16_wReadCompareValue
       05E0  _wCounter16_ReadCompareValue
       05E6  _Counter16_wReadCounter
       05E6  wCounter16_ReadCounter
       05E6  Counter16_wReadCounter
       05E6  _wCounter16_ReadCounter
       0624  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0624   12CF =   4815. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0624  _main
       0624  __text_start
       0C88  _PSoC_GPIO_ISR_C
       0C99  _DigBuf_ISR
       122B  _ltoa
       14A4  _ftoa
       18F3  __xidata_start
       18F3  __text_end
       1911  __xidata_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   0143 =    323. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0068  __Start
       0140  _bGetPowerSetting
       0140  bGetPowerSetting

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                    InterruptRAM   0000   0003 =      3. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  _NO_SHADOW
       0000  Port_2_Data_SHADE
       0000  NO_SHADOW
       0000  _Port_2_Data_SHADE
       0001  _Port_2_DriveMode_0_SHADE
       0001  Port_2_DriveMode_0_SHADE
       0002  _Port_2_DriveMode_1_SHADE
       0002  Port_2_DriveMode_1_SHADE

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   0012   000B =     11. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0012  __rZ
       0013  __rY
       0014  __rX
       0015  __r7
       0016  __r6
       0017  __r5
       0018  __r4
       0019  __r3
       001A  __r2
       001B  __r1
       001C  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   002E =     46. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       001D  _errorOffset
       0021  _OutputF
       0025  _period
       0027  _integerFreq
       0029  _A
       002B  _Ap
       002D  _Bp
       002F  _periodLog
       0031  _compare
       0033  _B
       0035  _compareLog
       0037  _frequencyDivider
       0039  _interupt
       003A  _freqFlag
       003B  _BP_Interupt

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ psocconfigtbl.asm, psocconfig.asm, lcd.asm, digbuf.asm, counter16int.asm, counter16_1int.asm ]
[ counter16.asm, rZ.asm, rY.asm, rX.asm, r7.asm, r6.asm, r5.asm, r4.asm, r3.asm, r2.asm, r1.asm, r0.asm, divmod_16x16_16_util.asm ]
[ divmod_32x32_32_util.asm, divmodu_32x32_32_util.asm, fp_analysiseject_util.asm, fp_clrreg_util.asm ]
[ fp_nan_res_util.asm, fp_saveres_util.asm, fp_sendtoreg_util.asm, fp_sinf_res_util.asm, fp_szero_res_util.asm ]
[ fp_type_oprnd_util.asm, fp_unnormal_util.asm, fpcmp_util.asm, fpdiv_util.asm, fpmul_util.asm ]
[ i_div16_block_util.asm, i_div32_block_util.asm, i_div32_not_util.asm, i_mulu8_block_util.asm ]
[ long2fp_util.asm, mul32_util.asm, ltoa.s, ftoa.s ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x12
-Blab3_2_RAM
-rwh:SSCParmBlk:0xf7.0xff

