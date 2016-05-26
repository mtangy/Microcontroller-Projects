//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h" 

void main(void) {	
	 
    
while (1){
	// LED1_Data_ADDR =& 0x00;
	// LED2_Data_ADDR =& 0x00;
	
	if (SW1_Data_ADDR & SW1_MASK){
		 
		LED1_Data_ADDR ^= LED1_MASK;
		while (SW1_Data_ADDR & SW1_MASK);
	}
	if (SW2_Data_ADDR & SW2_MASK){
		
		LED2_Data_ADDR ^= LED2_MASK;
		while (SW2_Data_ADDR & SW2_MASK);
	}
	
//	if (SW2_Data_ADDR & SW2_MASK){
//	LED2_Data_ADDR &=  ~LED2_MASK;
//	
//	}
//	
//	if (SW1_Data_ADDR & SW1_MASK){
//	
//		LED1_Data_ADDR &=  ~LED1_MASK;
//	
//	}
	


}	
}
