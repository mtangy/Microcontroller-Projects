Project:      output/lab3_2
Build Number: 0
Date:         Mon Jun 22 04:35:21 2015
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   01A0   008E =    142. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       01BA  LoadConfigTBL_lab3_2_Bank0
       0209  LoadConfigTBL_lab3_2_Bank1
       022E  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   022E   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       022E  __func_lit_start
       0230  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   0230   0170 =    368. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0230  LoadConfigTBL_lab3_2_Ordered
       0335  _LoadConfigInit
       0335  LoadConfigInit
       0345  _LoadConfig_lab3_2
       0345  LoadConfig_lab3_2
       03A0  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     UserModules   03A0   01B7 =    439. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       03A0  _LCD_PrCString
       03A0  LCD_PrCString
       03B2  LCD_HEX_STR
       03C2  LCD_PrHexByte
       03C2  _LCD_PrHexByte
       03D5  _LCD_PrHexInt
       03D5  LCD_PrHexInt
       03DC  _LCD_PrString
       03DC  LCD_PrString
       03EE  _LCD_Write_Data
       03EE  _LCD_WriteData
       03EE  LCD_WriteData
       03EE  LCD_Write_Data
       0402  LCD_Control
       0402  _LCD_Control
       04B2  _LCD_Start
       04B2  _LCD_Init
       04B2  LCD_Init
       04B2  LCD_Start
       0521  LCD_ROW_OFFSET
       0525  LCD_Position
       0525  _LCD_Position
       0535  LCD_Delay50uTimes
       0535  _LCD_Delay50uTimes
       053B  LCD_Delay50u_Table
       0543  _LCD_Delay50u
       0543  LCD_Delay50u
       0557  __UserModules_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0557   0174 =    372. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0557  __text_start
       0557  _main
       06BA  _PSoC_GPIO_ISR_C
       06CB  __xidata_start
       06CB  __text_end
       06D8  __xidata_end

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
               virtual_registers   0003   0003 =      3. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0003  __rX
       0004  __r1
       0005  __r0

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0000   000B =     11. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __data_start
       0006  _Bp
       0008  _A
       000A  _B
       000C  _count
       000E  _Ap
       0010  _NewData

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
obj/main.o	[ main.c ]
<library>	[ psocconfigtbl.asm, psocconfig.asm, lcd.asm, rX.asm, r1.asm, r0.asm ]

Area Definitions

-blit:0x1a0.0x7fff
-bdata:0.0x6ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0x3
-Blab3_2_RAM
-rwh:SSCParmBlk:0xf7.0xff

