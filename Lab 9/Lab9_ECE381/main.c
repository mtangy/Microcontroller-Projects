//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include <stdbool.h>
#include <stdlib.h>

#include "stdlib.h"
#include "math.h"

void clearScreen(void);

int sampleIn;

char *Degree;

float voltageIn;
 
int*  tempValue = 0x00;
char *voltageValuep = 0x00;
BYTE *tempValuep = 0x00;
int *status;
int i;
int j;
int count=0;
int iStatus;
float scaleFactor;

void main(void)
{
	M8C_EnableGInt;
	PGA_Start(PGA_HIGHPOWER);
	ADCINC_Start (ADCINC_HIGHPOWER);
	LCD_Start(); 
	SleepTimer_Start();
	SleepTimer_EnableInt();
	SleepTimer_SetInterval(SleepTimer_1_HZ);
	
	scaleFactor = ((float)1.3)/((float)16384);
	//Degree = 0xDF;
	
	ADCINC_GetSamples(0);	
	
	while (1){
	
	count++;
//	i = 0;
//	j = 0;
//		
	
	SleepTimer_SyncWait(0x01,SleepTimer_WAIT_RELOAD);

	//	for (j = 0; j < 1000; j++);
		
		while(ADCINC_fIsDataAvailable() == 0);  
	
     	sampleIn = ADCINC_iClearFlagGetData();
		voltageIn = ((scaleFactor*(float)sampleIn)*100)+.05;
		
		voltageValuep = ftoa(voltageIn, &iStatus);
		
		clearScreen();
		LCD_Position(0,0);					// Set LCD position to row 1 column 0
		
		LCD_PrString(voltageValuep);				// Print voltage value on LCD
		//LCD_PrString(Degree);
		if ((voltageIn<100)&&(voltageIn>10))
		{
			
			LCD_Position(0,4);
			LCD_WriteData(0xDF);
			LCD_PrCString("F            ");
			
		}
		else if(voltageIn>100)  
		{
			LCD_Position(0,5);
			LCD_WriteData(0xDF);
			LCD_PrCString("F            ");
		}else {
			LCD_Position(0,3);
			LCD_WriteData(0xDF);
			LCD_PrCString("F            ");
		}
		
		
//		LCD_Position(0,0);             
//		LCD_PrHexInt(tempValue);
//		LCD_Position(1,0);  
//		LCD_PrString(tempValuep);
		LCD_Position(1,11);  
		LCD_PrHexInt(count);
//		LCD_Position(0,5); 
//		LCD_PrString(ftoa(tempValue,status));
	
	
	}	
}

void clearScreen(void){
	
	LCD_Position(0,0);  
	LCD_PrCString("                "); 
	LCD_Position(1,0);  
	LCD_PrCString("                ");
		
}