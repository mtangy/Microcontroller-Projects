//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------
#include    "M8C.h"

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include  "DigBuf.h"

//#include "SW2Buf.h"

#include <float.h>
#include "PSoCGPIOINT.h" 
#pragma interrupt_handler PSoC_GPIO_ISR_C
#pragma interrupt_handler DigBuf_ISR

#pragma interrupt_handler SW2Buf_ISR

int Ap =0; //Ap is the prior Encoder port A input 
int Bp =0;
int A =0;  //A is current Encoder port A input 
int B =0;
//int T_OUT;

BOOL interupt = FALSE;
int period;
int compare;

int periodLog;
int compareLog;

int integerFreq = 8; 
BOOL freqFlag = FALSE;
int frequencyDivider = 1; 

float OutputF;
float errorOffset = 1.0;
//float comparef = 2.5;  

BOOL BP_Interupt = FALSE;


void main(void){
	
char *freq;	
period = 1999;
compare = 1000;

DigBuf_EnableInt();	
DigBuf_Start();	

	
Counter16_Start();
//Counter16_1_Start();	
Counter16_WritePeriod(period);
Counter16_WriteCompareValue(compare); 

  
     //T_OUT = (Counter16_PERIOD + 1)* T_CLK;
	 //Counter16_WritePeriod(T_OUT);

     
	//Counter16_Start();
	//comparef = 2.5;

	LCD_Start();
	LCD_Position(0, 0);
	LCD_PrCString("Main            ");
	LCD_Position(1, 0);
	LCD_PrCString("                "); 	//should clear junk from LCD
	
	
	
	LCD_Position(1, 0);		
	LCD_PrString(freq); //clears previous frequency
	
	M8C_EnableIntMask(INT_MSK0,INT_MSK0_GPIO);
	//M8C_EnableIntMask(INT_MSK0,INT_MSK0_DBB10);
	//DigBuf_EnableInt();

    M8C_EnableGInt;
	DigBuf_EnableInt();
    DigBuf_Start();

	while(1)
	{
	    
		if(interupt)
		{
		    
			interupt = FALSE;
			
			A = OpEncA_MASK & OpEncA_Data_ADDR;
			B = OpEncB_MASK & OpEncB_Data_ADDR;
			
			B=B>>2;
			
		    if (Bp^A)//Clockwise turn 
			{
				if( OutputF >= (100/frequencyDivider)){
				
				period += 200;
                compare = (period+1)/2;
				
				//periodLog = log(period);
				//compareLog =(periodLog+1)/2;
				
				Counter16_WritePeriod(period);
                Counter16_WriteCompareValue(compare); 
				
				
				OutputF = ((100240/(1+period))*20)*errorOffset/frequencyDivider;
				freq = ftoa(OutputF,&integerFreq);
			
				
				    LCD_Position(0, 0);	
				    LCD_PrCString("Frequency(Hz):  "); //Initalizes frequency display 
	
					LCD_Position(1, 0);		
					LCD_PrCString("                "); //clears previous frequency
					
				    LCD_Position(1, 0);		
					LCD_PrString(freq); //displays new frequency 
					
				
				
				//itoa(freq, integerFreq, 10);
				}
					
			}
			
			 if(!(Bp^A)) //Counterclockwise Turn
			{
				if(OutputF <= (10000/frequencyDivider) ){
				
				
				period -= 200;
                compare = (period+1)/2;
				
				//periodLog = log(period);
				//compareLog = log(compare);
                Counter16_WritePeriod(period);
                Counter16_WriteCompareValue(compare); 
				
				    OutputF = ((100240/(1+period))*20)*errorOffset/frequencyDivider;
					freq = ftoa(OutputF,&integerFreq);
				
				
					//itoa(freq, integerFreq, 10);
					LCD_Position(0, 0);	
					LCD_PrCString("Frequency(Hz):  "); //Initalizes frequency display 
	
				
				    LCD_Position(1, 0);		
					LCD_PrCString("                "); //clears previous frequency 
				    LCD_Position(1, 0);		
					LCD_PrString(freq); //displays new frequency 
				}
			}
			Ap = A;  //Stores current data to Ap and Bp for next cycle
			Bp = B; 
				
		}
		
		if (BP_Interupt){
			
		BP_Interupt = FALSE;	
		LCD_Position(1, 0);		
		LCD_PrCString("                "); 
		//LCD_Position(1, 0);		
		//LCD_PrCString("BP Int active");
		
		if (!freqFlag){
			
			frequencyDivider = 10;
			OSC_CR3 = 0x1d;
			LCD_Position(1, 0);		
		    LCD_PrCString("10"); 
			freqFlag = TRUE;
		}
		else {
				
			frequencyDivider = 1;
			OSC_CR3 = 0x02;
			LCD_Position(1, 0);		
		    LCD_PrCString("11"); 
		    freqFlag = FALSE;
		}
			
//		if (OSC_CR3 = 0x02)
//		{
//		OSC_CR3 = 0x1d;	
//		}
//		else if (OSC_CR3 = 0x1d)
//		{OSC_CR3 = 0x02;}	
			
			
		}
		
		
		
	}

}
void PSoC_GPIO_ISR_C(void){
	
	interupt = TRUE;
	
	
	}



void DigBuf_ISR(void){
	
	BP_Interupt = TRUE;
	
}
 
