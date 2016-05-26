#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include <stdbool.h>  //Boolean data types header
#include <stdlib.h>
#include "PSoCGPIOINT.h"  //GPIO interupt header

#pragma interrupt_handler PSoC_GPIO_ISR_C   // GPIO Interupt directive

int Ap =0; //Ap is the prior Encoder port A input 
int Bp =0;
int A =0;  //A is current Encoder port A input 
int B =0;
BOOL NewData = FALSE;   //Boolean flag for interupt 
int count = 50;  // count variable intialized 


void main(void){
char *countp;    // char pointer to be passed through utoa();

LCD_Start();
LCD_Position(0, 0);
LCD_PrCString("                ");
LCD_Position(1, 0);
LCD_PrCString("                "); 	//should clear junk from LCD
LCD_Position(0, 0);
LCD_PrCString("50");				//Initializes beginning of count to display

M8C_EnableIntMask(INT_MSK0,INT_MSK0_GPIO); // Enable global interupt and Masks
M8C_EnableGInt;

while(1) //infinite loop
{

if(NewData)  //interupt subroutine
{

NewData = FALSE;

A = OpEncA_MASK & OpEncA_Data_ADDR;   // daving current encoder values 
B = OpEncB_MASK & OpEncB_Data_ADDR;

B=B>>2;   // bit shift to line up ports for proper logic

//if (Bp^A)//boolean equation for Clockwise turn 
if (B^Ap)
	{
if (count<100) // count condition 
{
	count++; //Increment if Count is below 100

	utoa(countp,count,10);
	LCD_Position(0, 0);
	LCD_PrCString("                ");//Clears all previous numbers (prevents 0 from 100 staying)
	LCD_Position(0, 0);		
	LCD_PrString(countp);	

/* 	LCD_Position(1, 0);	
	LCD_PrCString("++");//For testing what command(s) have been received 
	LCD_Position(0, 0);
	LCD_PrHexInt(count); */
}
	}

if (!(B^Ap))	
// if(!(Bp^A)) //Counterclockwise Turn
{
if (count >0) 
{
	count--; //Decrements count only if count is above 0
	
    utoa(countp,count,10);	//converts count to char to display 
	LCD_Position(0, 0);
	LCD_PrCString("                ");
	LCD_Position(0, 0);
	LCD_PrString(countp);
	
/* 	LCD_Position(1, 0);	
	LCD_PrCString("--");
	LCD_Position(0, 0);
	LCD_PrHexInt(count);	 */
}
	}
Ap = A;  //Stores previous encoder values for next cycle
Bp = B; 
	}
}
}
void PSoC_GPIO_ISR_C(void){  //GPIO ISR that raises interupt flag to run subroutine 

NewData = TRUE;


}

 
