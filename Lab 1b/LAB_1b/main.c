//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"

int i;

void main() {
char count = 0;
while(1) {
	count++;
	LED0_Data_ADDR = count;
	for ( i = 0; i < 10000; i ++);
}



