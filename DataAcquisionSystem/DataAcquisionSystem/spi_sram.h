//*****************************************************************************
//* Read/Write/Control Functions for the Microchip 23K256 32kB SPI RAM
//*
//* bnoble@siue.edu 20140320
//*****************************************************************************

#include <m8c.h>

// Chip Select Macros
#define nCS_LOW  {nCS_Data_ADDR &= ~nCS_MASK;}
#define nCS_HIGH {nCS_Data_ADDR |=  nCS_MASK;}

// 23K256 I/O defines
#define SPIRAM_READ				0x03
#define SPIRAM_WRITE			0x02
#define SPIRAM_READ_STATUS_REG	0x05
#define SPIRAM_WRITE_STATUS_REG	0x01

// 23K256 Status Register defines
#define SPIRAM_DISABLE_HOLD		0x01
#define SPIRAM_BYTE_MODE		0x00
#define SPIRAM_SEQUENTIAL_MODE	0x40
#define SPIRAM_PAGE_MODE		0x80

// SPI Dummy Byte define
#define SPIRAM_DUMMY_BYTE		0x00

// Function Prototypes
BYTE SPIRAM_WriteStatusRegister(BYTE value);
BYTE SPIRAM_ReadStatusRegister(void);
void SPIRAM_WriteByte(WORD addr, BYTE out);
BYTE SPIRAM_ReadByte(WORD addr);
void SPIRAM_WriteArray(WORD addr, BYTE *out, BYTE count);
void SPIRAM_ReadArray(WORD addr, BYTE *in, BYTE count);


