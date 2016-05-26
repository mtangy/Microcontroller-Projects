//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int count=0;
char *action;
char *countd;
char inc[10] = "Increment"; 	
char dec[10] = "Decrement";	
const char clear[16] = "                ";


void main(void)
{
char *action;
char *countd;

 
//void  LCD_Position(BYTE bRow, BYTE bCol);
//void  LCD_PrString(CHAR * sRamString);
//void  LCD_PrHexInt(INT iValue);
	
	
LCD_Start(); 
LCD_Position(0,0);
LCD_PrCString(clear);	
LCD_Position(1,0);
LCD_PrCString(clear);	
utoa(countd,count,10);
LCD_Position(1,6);
LCD_PrString(countd);
	
	
while(1){
	
	if (SW1_Data_ADDR & SW1_MASK){	 
		count++;
		action = inc;
		LCD_Position(0,0);
		LCD_PrCString(clear);	
		LCD_Position(1,0);
		LCD_PrCString(clear);	
		LCD_Position(0,0);          
		LCD_PrString(action);
		LCD_Position(1,0);
		LCD_PrHexInt(count);
		LCD_Position(1,5);
		utoa(countd,count,10);
		LCD_Position(1,6);
		LCD_PrString(countd);
		while(SW1_Data_ADDR & SW1_MASK);
	
	}
		
	if (SW2_Data_ADDR & SW2_MASK){	
		count--;
		action = dec;
		LCD_Position(0,0);
		LCD_PrCString(clear);	
		LCD_Position(1,0);
		LCD_PrCString(clear);	
		LCD_Position(0,3);          
    	LCD_PrString(action);
		LCD_Position(1,0);
		LCD_PrHexInt(count);
		utoa(countd,count,10);
		LCD_Position(1,6);
		LCD_PrString(countd);
		while(SW2_Data_ADDR & SW2_MASK);
	}


	
	
	
}

}
