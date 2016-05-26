//*****************************************************************************
//* Read/Write/Control Functions for the Microchip 23K256 32kB SPI RAM
//*
//* bnoble@siue.edu 20140320
//*****************************************************************************

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "spi_sram.h"

// Write byte "value" to SRAM Status Register
BYTE SPIRAM_WriteStatusRegister(BYTE value)
{
	BYTE b;

	// If bits 5 through 1 aren't zero, return an error as per
	// Section 2.5 in the 23K256 datasheet
	if (value & 0b00111110)
		return(1);
	// Mode SPIRAM_SEQUENTIAL_MODE|SPIRAM_PAGE_MODE are invalid.
	if ((value & 0b11000000) == 0b11000000)
		return(1);
	// Make sure the TX buffer is empty (it should be but let's be proper)
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	// SPI transfers begin by bringing CS LOW
	nCS_LOW;
	// Send the Status Register Write command
	SPIM_SendTxData(SPIRAM_WRITE_STATUS_REG);
	// It will be almost immediately loaded into the TX shift register, freeing
	// up the TX buffer, and the SPIM module will start transmission.
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	// Prime the TX buffer for the next byte by loading it with the new status
	// register byte while the first byte is still transmitting.
	SPIM_SendTxData(value);
	// Wait for the first TX/RX cycle to finish. We don't care what we read.
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	// Reading the data clears the RX_BUFFER_FULL flag, even if we don't want it.
	SPIM_bReadRxData(); // ignore byte from SPIRAM_WRITE_STATUS_REG TX
	// Wait for the second TX/RX cycle to finish so that we know that the entire
	// two byte transaction is finished.
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData(); // We don't care about this read either
	// SPI transfers end by bringing CS LOW
	nCS_HIGH;
	return(0);
}

// Read SRAM Status Register and return the result.
BYTE SPIRAM_ReadStatusRegister(void)
{
	BYTE statReg;
	BYTE b;

	// Make sure the TX buffer is empty before starting
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	nCS_LOW;
	// Send the Read Status Register command
	SPIM_SendTxData(SPIRAM_READ_STATUS_REG);
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	// Send a dummy byte in order to initiate a TX/RX transfer
	SPIM_SendTxData(SPIRAM_DUMMY_BYTE);
	// Wait for the first RX byte to arrive and ignore it; it is meaningless.
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();
	// Wait for the second RX byte to arrive; it contains the status reg value.
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	statReg = SPIM_bReadRxData();
	nCS_HIGH;
	return(statReg);
	
}

// Write byte "out" to SRAM address "addr"
// NOTE: This function assumes the SRAM has already been put in Byte Mode.
void SPIRAM_WriteByte(WORD addr, BYTE out)
{
	BYTE hiAddr;
	BYTE loAddr;
	
	// Break the SRAM word address into two bytes
	hiAddr = (BYTE)((addr >> 8) & 0x00ff);
	loAddr = (BYTE)(addr & 0x00ff);
	M8C_DisableGInt;
	// Place your SPI code here
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	
	nCS_LOW;
	SPIM_SendTxData(SPIRAM_WRITE);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(hiAddr);

	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(loAddr);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(out);
		
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();
	
	nCS_HIGH;
	
	M8C_EnableGInt;
}

// Read and return byte at SRAM address "addr"
// NOTE: This function assumes the SRAM has already been put in Byte Mode.
BYTE SPIRAM_ReadByte(WORD addr)
{
	BYTE hiAddr;
	BYTE loAddr;
	BYTE in;

	// Break the SRAM word address into two bytes
	hiAddr = (BYTE)((addr >> 8) & 0x00ff);
	loAddr = (BYTE)(addr & 0x00ff);
	M8C_DisableGInt;
	// Place your SPI code here
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
		
	nCS_LOW;
	SPIM_SendTxData(SPIRAM_READ);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(hiAddr);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(loAddr);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(SPIRAM_DUMMY_BYTE);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	in = SPIM_bReadRxData();
	
	nCS_HIGH;

	M8C_EnableGInt;
	return(in);
}

// Write "count" bytes starting at address "addr" from array "out".
// The M8C is limited to 256 byte pages. This limits the maximum
// array size to 256 bytes, which means that "count" is only useful
// as a BYTE.
// NOTE: This function assumes the SRAM has already been put in Sequential Mode
void SPIRAM_WriteArray(WORD addr, BYTE *out, BYTE count)
{
	BYTE hiAddr;
	BYTE loAddr;
	BYTE b;
	int i;
	
	// If some clown tries to write 0 bytes, just return.
	// XXX - Always beware of clowns!
	if (!count)
		return;
	// Break the SRAM word address into two bytes
	hiAddr = (BYTE)((addr >> 8) & 0x00ff);
	loAddr = (BYTE)(addr & 0x00ff);
	M8C_DisableGInt;
	// Place your SPI code here
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	nCS_LOW;
	SPIM_SendTxData(SPIRAM_WRITE);

	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(hiAddr);

	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();
	
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(loAddr);

	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();

	for (i = 0; i < count; i++ ){
			
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(out[i]);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();
	}

	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();
		
	nCS_HIGH;

	M8C_EnableGInt;
}

// Read "count" bytes starting at address "addr" into array "in"
// The M8C is limited to 256 byte pages. This limits the maximum
// array size to 256 bytes, which means that "count" is only useful
// as a BYTE.
// NOTE: This function assumes the SRAM has already been put in Sequential Mode
void SPIRAM_ReadArray(WORD addr, BYTE *in, BYTE count)
{
	BYTE hiAddr;
	BYTE loAddr;
	BYTE b;
	int i;
	// If some clown tries to write 0 bytes, just return.
	// XXX - Always beware of clowns!
	if (!count)
		return;
	// Break the SRAM word address into two bytes
	hiAddr = (BYTE)((addr >> 8) & 0x00ff);
	loAddr = (BYTE)(addr & 0x00ff);
	M8C_DisableGInt;
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));	
	nCS_LOW;
	SPIM_SendTxData(SPIRAM_READ);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(hiAddr);

	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));
	SPIM_SendTxData(loAddr);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_TX_BUFFER_EMPTY));	
    SPIM_SendTxData(SPIRAM_DUMMY_BYTE);
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	SPIM_bReadRxData();		
	
	while(!(SPIM_bReadStatus() & SPIM_SPIM_SPI_COMPLETE));
	
	for (i = 0; i < count; i++ ){
	in[i] = SPIM_bReadRxData();
	}

	nCS_HIGH;
	
	M8C_EnableGInt;
}
