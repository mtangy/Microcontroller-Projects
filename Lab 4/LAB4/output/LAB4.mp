Project:      output/LAB4
Build Number: 0
Date:         Mon Feb 02 22:31:17 2015
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   00D7 =    215. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01D3  LoadConfigTBL_lab3_2_Bank0
       023A  LoadConfigTBL_lab3_2_Bank1
       0277  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0277   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       0277  __func_lit_start
       0279  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   0279   0170 =    368. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0279  LoadConfigTBL_lab3_2_Ordered
       037E  _LoadConfigInit
       037E  LoadConfigInit
       038E  _LoadConfig_lab3_2
       038E  LoadConfig_lab3_2
       03E9  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   03E9   0219 =    537. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       03E9  _LCD_PrCString
       03E9  LCD_PrCString
       03FB  LCD_HEX_STR
       040B  _LCD_PrHexByte
       040B  LCD_PrHexByte
       041E  LCD_PrHexInt
       041E  _LCD_PrHexInt
       0425  LCD_PrString
       0425  _LCD_PrString
       0437  _LCD_Write_Data
       0437  _LCD_WriteData
       0437  LCD_Write_Data
       0437  LCD_WriteData
       044B  LCD_Control
       044B  _LCD_Control
       04FB  _LCD_Init
       04FB  _LCD_Start
       04FB  LCD_Start
       04FB  LCD_Init
       056A  LCD_ROW_OFFSET
       056E  LCD_Position
       056E  _LCD_Position
       057E  LCD_Delay50uTimes
       057E  _LCD_Delay50uTimes
       0584  LCD_Delay50u_Table
       058C  _LCD_Delay50u
       058C  LCD_Delay50u
       05A0  _Counter16_ISR
       05A1  _Counter16_1_ISR
       05A2  _Counter16_EnableInt
       05A2  Counter16_EnableInt
       05A6  Counter16_DisableInt
       05A6  _Counter16_DisableInt
       05AA  Counter16_Start
       05AA  _Counter16_Start
       05AE  Counter16_Stop
       05AE  _Counter16_Stop
       05B2  Counter16_WritePeriod
       05B2  _Counter16_WritePeriod
       05B8  Counter16_WriteCompareValue
       05B8  _Counter16_WriteCompareValue
       05BE  wCounter16_ReadCompareValue
       05BE  _Counter16_wReadCompareValue
       05BE  _wCounter16_ReadCompareValue
       05BE  Counter16_wReadCompareValue
       05C4  _wCounter16_ReadCounter
       05C4  wCounter16_ReadCounter
       05C4  Counter16_wReadCounter
       05C4  _Counter16_wReadCounter
       0602  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0602   0FC5 =   4037. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0602  _main
       0602  __text_start
       0A50  _PSoC_GPIO_ISR_C
       0EFF  _ltoa
       1178  _ftoa
       15C7  __xidata_start
       15C7  __text_end
       15D6  __xidata_end

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
                            data   0000   002A =     42. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       001D  _errorOffset
       0021  _OutputF
       0025  _period
       0027  _B
       0029  _A
       002B  _Ap
       002D  _integerFreq
       002F  _compareLog
       0031  _periodLog
       0033  _compare
       0035  _Bp
       0037  _interupt

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ psocconfigtbl.asm, psocconfig.asm, lcd.asm, counter16int.asm, counter16_1int.asm, counter16.asm ]
[ rZ.asm, rY.asm, rX.asm, r7.asm, r6.asm, r5.asm, r4.asm, r3.asm, r2.asm, r1.asm, r0.asm, divmod_16x16_16_util.asm ]
[ divmod_32x32_32_util.asm, divmodu_32x32_32_util.asm, fp_analysiseject_util.asm, fp_clrreg_util.asm ]
[ fp_nan_res_util.asm, fp_saveres_util.asm, fp_sendtoreg_util.asm, fp_sinf_res_util.asm, fp_szero_res_util.asm ]
[ fp_type_oprnd_util.asm, fp_unnormal_util.asm, fpcmp_util.asm, fpmul_util.asm, i_div16_block_util.asm ]
[ i_div32_block_util.asm, i_div32_not_util.asm, i_mulu8_block_util.asm, long2fp_util.asm ]
[ mul32_util.asm, ltoa.s, ftoa.s ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x12
-Blab3_2_RAM
-rwh:SSCParmBlk:0xf7.0xff

