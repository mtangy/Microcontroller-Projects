//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include <string.h>
#include "string.h"
#include "PSoCGPIOINT.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "I2CHWMstr.h"

#pragma interrupt_handler TempReset 
#pragma interrupt_handler T_INT




BYTE currentTempA[2];
BYTE currentTemp;
BYTE currentTemp1;
BYTE currentTemp2;
BYTE POLbitFlip[2];

char string0[17];
char string1[17];
char string2[17];
char string3[17];
char* tempP;

char* configOutP;


char TH;
char TL;

char* THP;
char* TLP;


char messageString[79];
int parseCounter=0;
int stringSize=0;
char temp = 0;
int addressInt=0;
char addressHex;
int i;
int j;
char sizeOfString;
char command;


BOOL Interupt = FALSE;
BOOL hexOrAscii = FALSE;
BOOL finishFlag = FALSE;
BOOL invaildFlag = FALSE;
BOOL readOrWrite = FALSE;
BOOL firstPass = TRUE;
BOOL fanOn;
/* Define slave address */

#define ThermoStat 0x48

BYTE THF = 0x40;
BYTE TLF = 0x20;

/* Define command set */
BYTE tempRead = 0xAA;
BYTE tempStartConvert = 0xEE;
BYTE tempStopConvert = 0x22;
BYTE accessConfigReg = 0xAC;
BYTE accessTL = 0xA2;
BYTE accessTH = 0xA1;

/* Define buffer size */
#define BUFFER_SIZE 0xFF

BYTE txBuffer[BUFFER_SIZE];
BYTE rxBuffer[2];

BYTE THvalue[3];
BYTE TLvalue[3];

BYTE THvalueTest[2];
BYTE TLvalueTest[2];

BYTE status;
BYTE configOut[2];
BYTE configOut2[2];


//int configOutReg;
BYTE* Address_Pointer;

BYTE Read_Address;
BYTE Write_Address;
char temp1;
char temp2;
char temp3;
char charIn = '\0';
char charIn1= '\0';
char charIn2= '\0';
char charIn3= '\0';
char charIn4= '\0';

char instBuffer= '\0';
int placeCounter = 0;
int count;
char tolerence;
BOOL heatOrCool;
char rawString[79];

BOOL update = FALSE;

const char welcome[] = "Welcome to our Programmable Thermostat!";
const char setTempraturePrompt[] = "To set the temprature enter it in the following format: 'S ##' (## is the desired temprature in Celsius)";
const char setTolerancePrompt[] = "To set the tolerance enter it in the following format: 'T #' (# is the width of the temprature tolerance in Celsius)";
const char setThermModePrompt[] = "To set the thermostat mode enter it it in the following format: 'M X' (X should be set to C for cool, H for heat and F for off)";
const char setFanModePrompt[] = "To set the mode of the fan enter it in the following format: 'F X' (X should be set to A for automatic fan and M for manual which keeps the fan on all the time)";

//function prototypes
void startFunction (void);
void readFunction(void);
void stringParser(void);
char asciiToInt(char temp1);
void setTolerenceLevel(char THvalue[], char TLvalue[]);
void compareParameters(void); 
void cleerLCD(void);
void outputConfig(void);
void changePOLbit(void);
void initial(void);

void main(void)
{		
		
	
		M8C_EnableIntMask(INT_MSK0,INT_MSK0_GPIO); 
        I2CHW_Start();
        I2CHW_EnableMstr();
        I2CHW_EnableInt();
        LCD_Start();
        UART_Start(UART_PARITY_NONE);

		M8C_EnableGInt;
		Counter24_Start();
		Counter24_EnableInt();
		
        firstPass = FALSE;
		invaildFlag = FALSE;
		txBuffer[0] = 0xAA;
		startFunction();
		configOut2[2] = 0x00;
		
		initial();

		
        while(!firstPass)
        {
			

		
			while (!invaildFlag){
	

        			readFunction();
	                stringParser();
					


              	if (update){

					I2CHW_bWriteBytes(ThermoStat, &tempStartConvert , 1 , I2CHW_CompleteXfer);
			        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
			        I2CHW_ClrWrStatus();

					I2CHW_bWriteBytes(ThermoStat, &tempRead , 1 , I2CHW_NoStop);
			        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
			        I2CHW_ClrWrStatus();
					
					I2CHW_fReadBytes(ThermoStat, currentTempA , 2, I2CHW_RepStart);
			        while(!(I2CHW_bReadI2CStatus() & I2CHW_RD_COMPLETE));
			        I2CHW_ClrRdStatus();
					
					utoa(tempP, currentTempA[0],10);
					
					
					cleerLCD();
					UART_PutCRLF();
					UART_CPutString("Current Mode:");
					if (heatOrCool){
					LCD_Position(0,0);	
					UART_CPutString("Cool");
					UART_PutCRLF();
					}else {
					LCD_Position(0,0);	
					UART_CPutString("Heat");
					UART_PutCRLF();
					}
					UART_PutCRLF();
					UART_PutCRLF();
					UART_CPutString("Current temperature:");
					utoa(tempP, currentTempA[0],10);
					UART_PutString(tempP);
					
					if(currentTempA[1] == 0x00){
					UART_CPutString(".5 C");
						

					}else {

					UART_CPutString(".0 C");		
					}
					compareParameters();
					update = FALSE;
					
					
					if (fanOn){ LED_Fan_Indicator_Data_ADDR ^= LED_Fan_Indicator_MASK;
					}else {LED_Fan_Indicator_Data_ADDR &= ~LED_Fan_Indicator_MASK;}
					
					
			//	}	
				
				
				//firstPass = TRUE;
				}
	   }//end invalid input loop
        	
  }//End while(1)

} //End Main

void startFunction (void)
{
	UART_CPutString(welcome);
	UART_PutCRLF();
	UART_PutCRLF();
	UART_CPutString(setThermModePrompt);
	UART_PutCRLF();
	UART_PutCRLF();
	UART_CPutString(setFanModePrompt);
	UART_PutCRLF();
	UART_PutCRLF();
	UART_CPutString(setTolerancePrompt);
	UART_PutCRLF();
	UART_PutCRLF();
	UART_CPutString(setTempraturePrompt);
	UART_PutCRLF();
	UART_PutCRLF();

	
}//end startFunction
	
void readFunction (void)
{
	    UART_CPutString("\r\n");
		UART_CPutString(">");
        placeCounter = 0;
		finishFlag= FALSE ;

        while (!finishFlag) { 
              charIn = UART_cReadChar();
              while (charIn == 0x00){charIn = UART_cReadChar();}
	               if (placeCounter<79){
					
                    if (charIn == 0x0d){ 
                                UART_CPutString("\r\n");
                                UART_CPutString("\r\n");
                                finishFlag = TRUE;
                            } //end if CR
                       			 else if ((charIn == 0x08 || charIn ==0x7f) && placeCounter > 0 ){ //if backspace
                                placeCounter--;
                                UART_CPutString("\x8\x20\x8");
                     				   } //end if backspace
                  			  else {
                                    rawString[placeCounter] = charIn;
                                    UART_PutChar(rawString[placeCounter]);
                                    placeCounter++;
                            }// end else write into string
                  }  else { 
							
							UART_PutCRLF();
                            UART_CPutString("String Full");
							UART_PutChar(0x07);
                            finishFlag = TRUE;
							UART_PutCRLF();
							
                    }// end placeCounter if

    }//end while (!finsihFlag)
		
}//end readFunction
void stringParser(void)
{
		if (rawString[2]>= 0x30 && rawString[2]<= 0x39 &&  rawString[3]>= 0x30 && rawString[3]<= 0x39 || rawString[2] == 'h' || rawString[2] == 'c' ){//checks for valid number
			
			if(!(rawString[1] ==' ')){
				
				invaildFlag = TRUE;
				UART_PutCRLF();
				UART_PutCRLF();
				
			}// maybe put else
			
				if(rawString[0]>= 0x41 && rawString[0]<= 0x5a) {rawString[0] = rawString[0]+0x20;} //checks if inputted charter & makes it lower case if it is 
				if(rawString[2]>= 0x41 && rawString[2]<= 0x5a) {rawString[2] = rawString[2]+0x20;}
				
					switch(rawString[0])//Determines if operation is read or write
			        {
			                case  's':
					
							temp2 = asciiToInt(rawString[2]);
							temp3 = asciiToInt(rawString[3]);
							
							temp2 = temp2 * 10;
							temp = temp2 + temp3; 
							
							outputConfig();
			                break; //end case r

			                case 't':
							
							tolerence = asciiToInt(rawString[2]);

							TH = temp + tolerence/2;
							TL = temp - tolerence/2;

							THvalue[0] = accessTH;
							THvalue[1] = TH;
							THvalue[2] = 0x00;
							
							TLvalue[0] = accessTL ;
							TLvalue[1] = TL;
							TLvalue[2] = 0x00;
							
							setTolerenceLevel(THvalue, TLvalue);
							outputConfig();
						
			                break; //end case w
							
							case 'm':
							
							if (rawString[2]=='c'){
								
								heatOrCool=TRUE;
								//changePOLbit();
							}else if(rawString[2]=='h'){
							
							heatOrCool = FALSE;
							//changePOLbit();		
								
							}else{ fanOn = FALSE;}
							
							break;
							
							case 'f':

							break;
							
							default:
							
							UART_PutCRLF();
			                UART_CPutString("invalid input charecter");
			                UART_PutCRLF();
							invaildFlag = TRUE;	 
							
					}//end command switch
 
		}else{
			
		UART_PutCRLF();
		UART_CPutString("Invalid input number");
		UART_PutCRLF();
		invaildFlag = TRUE;	
			
		}//end of invalid input if-else 
	
}//parse string

void TempReset(void){
	
		update = TRUE;
	
}

void setTolerenceLevel(char THvalue[], char TLvalue[]){

		I2CHW_bWriteBytes(ThermoStat, THvalue , 3 ,I2CHW_CompleteXfer);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();
		
		I2CHW_bWriteBytes(ThermoStat, TLvalue , 3 ,I2CHW_CompleteXfer);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();
		
		I2CHW_bWriteBytes(ThermoStat, &accessTH , 1 ,I2CHW_NoStop);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();
		
		I2CHW_fReadBytes(ThermoStat, THvalueTest , 2, I2CHW_RepStart);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_RD_COMPLETE));
        I2CHW_ClrRdStatus();
		
		I2CHW_bWriteBytes(ThermoStat, &accessTL , 1 ,I2CHW_NoStop);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();
		
		I2CHW_fReadBytes(ThermoStat, TLvalueTest , 2, I2CHW_RepStart);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_RD_COMPLETE));
        I2CHW_ClrRdStatus();
		
		UART_PutCRLF();
		UART_PutCRLF();
		UART_CPutString("TL value:");
		

		utoa(TLP, TLvalueTest[0],10);
		UART_PutString(TLP);
		
		UART_PutCRLF();
		UART_PutCRLF();
		UART_CPutString("TH value:");
		
		
		utoa(THP, THvalueTest[0],10);
		UART_PutString(THP);
		
}

void T_INT(void)
{
	
LED_Data_ADDR &= LED_MASK;
	
//Interupt = TRUE;
	
}
char asciiToInt(char temp1){
	
	if(temp1>= 0x61 && temp1<= 0x66){
		temp1= temp1-0x20;
	}else 
	
	if (temp1  >= 0x30 && temp1 <= 0x39){
		
		temp1 = temp1 - 0x30;
	
	} else if(temp1  >= 0x41 && temp1 <= 0x46){
		temp1 = temp1 - 0x31;
		
	}
	else{
		return '0';
	}

	return temp1;
	
}

void compareParameters(void){
	
	if(heatOrCool && currentTemp >= TH){
		
		fanOn = TRUE;
	
	}else if(!heatOrCool && currentTemp <= TL){
		
		fanOn = TRUE;	
	}	
}
void cleerLCD(void){

LCD_Position(0,0);
LCD_PrCString("                 ");	
LCD_Position(1,0); 
LCD_PrCString("                 ");	
		
}	
void outputConfig(void){
	
	
		I2CHW_bWriteBytes(ThermoStat, &accessConfigReg , 1 ,I2CHW_NoStop);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();
		
		I2CHW_fReadBytes(ThermoStat, configOut , 1, I2CHW_RepStart);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_RD_COMPLETE));
        I2CHW_ClrRdStatus();
		
		UART_PutCRLF();
		UART_PutCRLF();
		UART_CPutString("Configuration Register:");
		UART_PutCRLF();
		UART_PutCRLF();

		utoa(configOutP, configOut[0], 2);
		UART_PutString(configOutP);
		UART_PutCRLF();
		UART_PutCRLF();
		
		if (configOut[0] & THF){
		UART_PutCRLF();
		UART_PutCRLF();
		UART_CPutString("Temp High Flag On!");	
		UART_PutCRLF();
		UART_PutCRLF();
			
		}else if (configOut[0] & TLF){
		UART_PutCRLF();
		UART_PutCRLF();
		UART_CPutString("Temp Low Flag On!");
		UART_PutCRLF();
		UART_PutCRLF();
		
		}else{UART_CPutString("High Low flag fail");}	

}	
void changePOLbit(void){
	
		I2CHW_bWriteBytes(ThermoStat, &accessConfigReg , 1 ,I2CHW_NoStop);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();
		
		I2CHW_fReadBytes(ThermoStat, configOut2 , 1, I2CHW_RepStart);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_RD_COMPLETE));
        I2CHW_ClrRdStatus();
		
		UART_PutCRLF();
		UART_PutCRLF();
//		UART_PutSHexByte(configOut2[0]);
//		UART_PutCRLF();
//		UART_PutCRLF();
		
		
		
		POLbitFlip[0] = accessConfigReg;
		POLbitFlip[1] = configOut2[0] ^ 0x02;
	
	    I2CHW_bWriteBytes(ThermoStat, POLbitFlip , 2 ,I2CHW_CompleteXfer);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();

	
}	
void initial(void){

		I2CHW_bWriteBytes(ThermoStat, &tempStartConvert , 1 , I2CHW_CompleteXfer);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();

		I2CHW_bWriteBytes(ThermoStat, &tempRead , 1 , I2CHW_NoStop);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();
		
		j = 0;
		for(j = 0; j < 5000; j++); 
		
		I2CHW_fReadBytes(ThermoStat, currentTempA , 2, I2CHW_RepStart);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_RD_COMPLETE));
        I2CHW_ClrRdStatus();
		
		
		I2CHW_bWriteBytes(ThermoStat, &accessConfigReg , 1 ,I2CHW_NoStop);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_WR_COMPLETE));
        I2CHW_ClrWrStatus();
		
		I2CHW_fReadBytes(ThermoStat, configOut , 1, I2CHW_RepStart);
        while(!(I2CHW_bReadI2CStatus() & I2CHW_RD_COMPLETE));
        I2CHW_ClrRdStatus();
		
		j = 0;
		for(j = 0; j < 5000; j++); 

}	