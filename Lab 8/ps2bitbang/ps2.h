//// Port/Shadow Register Control Macros
#define PS2CLOCK_HIGH	{PS2CLOCK_DataShadow |=  PS2CLOCK_MASK; PS2CLOCK_Data_ADDR = PS2CLOCK_DataShadow;}
#define PS2CLOCK_LOW	{PS2CLOCK_DataShadow &= ~PS2CLOCK_MASK; PS2CLOCK_Data_ADDR = PS2CLOCK_DataShadow;}
#define PS2DATA_HIGH	{PS2DATA_DataShadow |=  PS2DATA_MASK; PS2DATA_Data_ADDR = PS2DATA_DataShadow;}
#define PS2DATA_LOW		{PS2DATA_DataShadow &= ~PS2DATA_MASK; PS2DATA_Data_ADDR = PS2DATA_DataShadow;}

//// PS/2 Frame I/O status codes
#define FRAME_DATA_AVAILABLE	0x01
#define FRAME_BYTE_TRANSMITTED	0x02
#define FRAME_RX_PARITY_ERROR	0x04
#define FRAME_RX_FRAME_ERROR	0x08 // Only set by having an invalid Stop bit
#define FRAME_TX_FRAME_ERROR	0x10 // Only set by having an invalid ACK bit
#define FRAME_INCOMPLETE		0x20 // Only set by PS2OneShot ISR

//// PS/2 Device status codes
#define DEVICE_TX_TIMEOUT		0x01
#define DEVICE_RX_TIMEOUT		0x02
#define DEVICE_TX_FRAME_ERROR	0x04
#define DEVICE_RX_FRAME_ERROR	0x08
#define DEVICE_BAD_BAT			0x10
#define DEVICE_INVALID_RESPONSE	0x20
#define DEVICE_ERROR			0x40
#define DEVICE_IS_MOUSE			0x80

//// Function prototypes
BYTE PS2_Write_Byte(BYTE ps2data);
BYTE PS2_Send_Command_Process_Response(BYTE ps2data);
BYTE PS2_Detect_Device(void);