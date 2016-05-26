//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------
#include "M8C.h"
#include <m8c.h> // part specific constants and macros
#include "PSoCAPI.h" // PSoC API definitions for all User Modules
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DigBuf.h"
#include <float.h>
#include "PSoCGPIOINT.h"
#pragma interrupt_handler PSoC_GPIO_ISR_C
#pragma interrupt_handler DigBuf_ISR
#pragma interrupt_handler SW2Buf_ISR	
int Ap =0; //Ap is the prior Encoder port A input
int Bp =0;
int A =0; //A is current Encoder port A input
int B =0;
BOOL interupt = FALSE; //global declerations of all variables
int period;
int compare;
int periodLog;
int compareLog;
int integerFreq = 8;
int frequencyDivider = 1;
float OutputF;
float errorOffset = 1.0;
BOOL BP_Interupt = FALSE;
BOOL freqFlag = FALSE;

void main(void){
	char *freq;
	period = 1999; //initializing period and compare register vaiables to set initial
	frequency of 1KHz
	compare = 1000;
	Counter16_Start(); //start counter and write initial period and start register
	Counter16_1_Start();
	Counter16_WritePeriod(period);
	Counter16_WriteCompareValue(compare);
	LCD_Start();
	LCD_Position(0, 0);
	LCD_PrCString("Main ");
	LCD_Position(1, 0);
	LCD_PrCString(" "); //should clear junk from LCD
	LCD_Position(0, 0);
	LCD_PrCString("Frequency(Hz): "); //Initalizes frequency display
	OutputF = ((100240/(1+period))*20)*errorOffset/frequencyDivider;
	freq = ftoa(OutputF,&integerFreq);
	LCD_Position(1, 0);
	LCD_PrString(freq); //clears previous frequency
	M8C_EnableIntMask(INT_MSK0,INT_MSK0_GPIO); //enables bit for GPIO interupt
	M8C_EnableGInt;
	DigBuf_EnableInt(); //start digitel buffer and enable interupts
	DigBuf_Start();
	while(1)
	{
	if(interupt)
	{
		interupt = FALSE;
		A = OpEncA_MASK & OpEncA_Data_ADDR; // assigning current state of encoder
		B = OpEncB_MASK & OpEncB_Data_ADDR;
		B=B>>2; //bit shift to allighn ports to allow for correct lgic
		if (Bp^A)//Clockwise turn
		{
		if( OutputF >= (100/frequencyDivider)){
			period += 200; //Increment period and compare when turned clockwise
			compare = (period+1)/2;
			Counter16_WritePeriod(period); //write period and compare
			Counter16_WriteCompareValue(compare);
			OutputF = ((100240/(1+period))*20)*errorOffset/frequencyDivider; //compute frequency and
			convert to char to print
			freq = ftoa(OutputF,&integerFreq);
			LCD_Position(0, 0);
			LCD_PrCString("Frequency(Hz): "); //Initalizes frequency display
			LCD_Position(1, 0);
			LCD_PrCString(" "); //clears previous frequency
			LCD_Position(1, 0);
			LCD_PrString(freq); //displays new frequency
		}
		}
		if(!(Bp^A)) //Counterclockwise Turn
		{
			if(OutputF <= (10000/frequencyDivider) ){
				period -= 200; //decrement period and compare when turned counter-clockwise
				compare = (period+1)/2;
				Counter16_WritePeriod(period); //write period and compare
				Counter16_WriteCompareValue(compare);
				OutputF = ((100240/(1+period))*20)*errorOffset/frequencyDivider; //compute frequency
				and convert to char to print
				freq = ftoa(OutputF,&integerFreq);
				LCD_Position(0, 0);
				LCD_PrCString("Frequency(Hz): "); //Initalizes frequency display
				LCD_Position(1, 0);
				LCD_PrCString(" "); //clears previous frequency
				LCD_Position(1, 0);
				LCD_PrString(freq); //displays new frequency
			}
		}
		Ap = A; //Stores current data to Ap and Bp for next cycle
		Bp = B;
	}
		if (BP_Interupt){
		BP_Interupt = FALSE;
		LCD_Position(1, 0);
		LCD_PrCString(" ");
			if (!freqFlag)
			{
				frequencyDivider = 10; //changing frequency Divider to allow for lower frequencies
				OSC_CR3 = 0x1d;
				LCD_Position(0, 0);
				LCD_PrCString(" "); //printing to LCD
				LCD_Position(0, 0);
				LCD_PrCString("1kHz to 10Hz");
				freqFlag = TRUE;
			}
			else {
				frequencyDivider = 1; //changing frequency Divider to allow for normal frequencies
				OSC_CR3 = 0x02;
				LCD_Position(0, 0);
				LCD_PrCString(" "); //printing to LCD
				LCD_Position(0, 0);
				LCD_PrCString("10kHz to 100Hz");
				freqFlag = FALSE;
			}
		}
	}
}
void PSoC_GPIO_ISR_C(void){
	interupt = TRUE;
}
void DigBuf_ISR(void){
	BP_Interupt = TRUE;
}
