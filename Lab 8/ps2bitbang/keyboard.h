//// Bit-masks to test for keyboard actions. Set by KeyboardDecodeData()
//// Masks can be OR'd or AND'd to check for specific or combined conditions.
#define KEY_NO_ACTION	0x00
#define KEY_MAKE		0x01
#define KEY_BREAK		0x02
#define KEY_E0			0x04
#define KEY_PAUSE		0x08
#define KEY_FAKE_SHIFT	0x10

BYTE KeyboardDecodeData(BYTE scancode);
BYTE KeyboardTotalPressed(BYTE scancode, BYTE codetype);
char KeyboardToASCII(BYTE scancode, BYTE codetype);
void KeyboardAction(BYTE scancode, BYTE codetype, BYTE keyspressed);