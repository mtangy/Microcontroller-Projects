Project:      output/lab2_2
Build Number: 0
Date:         Mon Feb 09 20:09:36 2015
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   0084 =    132. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01A0  _clear
       01B0  LoadConfigTBL_lab2_2_Bank0
       01FF  LoadConfigTBL_lab2_2_Bank1
       0224  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0224   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       0224  __func_lit_start
       0226  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   0226   0170 =    368. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0226  LoadConfigTBL_lab2_2_Ordered
       032B  _LoadConfigInit
       032B  LoadConfigInit
       033B  _LoadConfig_lab2_2
       033B  LoadConfig_lab2_2
       0396  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   0396   01B7 =    439. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0396  _LCD_PrCString
       0396  LCD_PrCString
       03A8  LCD_HEX_STR
       03B8  LCD_PrHexByte
       03B8  _LCD_PrHexByte
       03CB  _LCD_PrHexInt
       03CB  LCD_PrHexInt
       03D2  _LCD_PrString
       03D2  LCD_PrString
       03E4  _LCD_Write_Data
       03E4  _LCD_WriteData
       03E4  LCD_WriteData
       03E4  LCD_Write_Data
       03F8  LCD_Control
       03F8  _LCD_Control
       04A8  _LCD_Start
       04A8  _LCD_Init
       04A8  LCD_Init
       04A8  LCD_Start
       0517  LCD_ROW_OFFSET
       051B  LCD_Position
       051B  _LCD_Position
       052B  LCD_Delay50uTimes
       052B  _LCD_Delay50uTimes
       0531  LCD_Delay50u_Table
       0539  _LCD_Delay50u
       0539  LCD_Delay50u
       054D  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   054D   032F =    815. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       054D  _main
       054D  __text_start
       0739  _utoa
       087C  __text_end
       087C  __xidata_start
       0899  __xidata_end

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
               virtual_registers   0017   0007 =      7. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0017  __rZ
       0018  __rY
       0019  __rX
       001A  __r3
       001B  __r2
       001C  __r1
       001D  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   001A =     26. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       0003  _dec
       000D  _inc
       001E  _countd
       0020  _action
       0022  _count

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ psocconfigtbl.asm, psocconfig.asm, lcd.asm, rZ.asm, rY.asm, rX.asm, r3.asm, r2.asm, r1.asm, r0.asm ]
[ divmodu_16x16_16_util.asm, i_div16_block_util.asm, utoa.s ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x17
-Blab2_2_RAM
-rwh:SSCParmBlk:0xf7.0xff

