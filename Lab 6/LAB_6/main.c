//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "string.h"
//#include "stdbool.h"
//#include <stdbool.h>
#include "I2CHWMstr.h"

//char register [7];
char string0[17];
char string1[17];
char string2[17];
char string3[17];

char address[2]; 
char messageString[79]; 
int parseCounter=0; 

BYTE ramSelect;

BOOL finishFlag = FALSE; 
BOOL invaildFlag = FALSE; 

/* Define slave address */
#define Ram1 0x50
#define Ram2 0x51  //NOTE:1 may need to be changed to a 2 to make room for the R/W bit  

/* Define buffer size */
#define BUFFER_SIZE 0x08

BYTE txBuffer[BUFFER_SIZE];
BYTE rxBuffer[BUFFER_SIZE];
BYTE status;

BYTE *Read_Address;

char charIn = '\0';
char charIn1= '\0';
char charIn2= '\0';
char charIn3= '\0';
char charIn4= '\0';

char instBuffer= '\0';
int placeCounter = 0;
int count;


char rawString[79]; 

const char welcomeMsg[] = "Welcome.";
const char instructMsg[] = "Type in the form we like (I swear I'll fix this)";
//"W # XX A Mary had a little lamb"

//function prototypes
void startFunction(void);
void readFunction(void);
void stringParser(void);
void instructions(void);



void main(void)
{
	
	I2CHW_Start(); 
	I2CHW_EnableMstr();
	M8C_EnableGInt;
	I2CHW_EnableInt();
	LCD_Start();
	
	
	UART_Start(UART_PARITY_NONE);
		
	//I2CHW_InitRamRead(txBuffer, BUFFER_SIZE);

	Read_Address = 0x00;
	
	txBuffer[0] = 0x00;
	txBuffer[1] = 0x55;
	txBuffer[2] = 0x55;
	txBuffer[3] = 0x55;
	txBuffer[4] = 0x55;
	txBuffer[5] = 0x55;
	txBuffer[6] = 0x55;
	txBuffer[7] = 0x55;
	
	//txBuffer[8] = 0x55;
	
	while(1) 
	{
		
		startFunction();
		readFunction();
		
		if (finishFlag){
		LCD_Position(0,0);
		LCD_PrString(rawString); 
		}
		stringParser(); 
		if (invaildFlag)
		{
			UART_CPutString("This string was invalid");
			UART_CPutString(instructMsg);
		}//end invalid flag if
		else 
		{	
			//This is where the good I2c stuff goes
		
		}
	}//End while(1)

} //End Main

void startFunction (void)
{
	
	UART_CPutString(welcomeMsg);
	UART_PutCRLF();
	UART_CPutString(instructMsg);
	UART_PutCRLF();
	UART_CPutString(">");
	
}//end startFunction
void readFunction (void)
{
	placeCounter = 0; 
	finishFlag= FALSE; 
	
	while (!finishFlag) {
				
				charIn = UART_cReadChar();	
					while (charIn == 0x00){charIn = UART_cReadChar();}
						if (placeCounter<78){
							
					    if (charIn == 0x0d){ //if carriage return 
								UART_CPutString("\r\n");
								UART_CPutString("\r\n");
							    finishFlag = TRUE; 
								//Call the parser function here
						    } //end if CR
						
						else if (charIn == 0x08 || charIn ==0x7f){ //if backspace
							placeCounter--;
							string0[placeCounter] = ' ';
							
						} //end if backspace 
						else {
								rawString[placeCounter] = charIn;
					    		UART_PutChar(rawString[placeCounter]);
								placeCounter++;
							}// end else write into string 
					
						} // end placeCounter if
					else 
						{
							
							UART_CPutString("String Full"); 
							finishFlag = TRUE;
						}
				
	}//end while (~finsihFlag) 
	
	finishFlag= FALSE ;
	
}//end readFunction

void stringParser(void)
{
	switch (rawString[0])
	{
		case  'r'|'R': 
			
		UART_PutCRLF();
		UART_CPutString("read");
		UART_PutCRLF();
			
		break; //end case r 
		
		case 'w'|'W':
		
		UART_PutCRLF();
		UART_CPutString("write");
		UART_PutCRLF();	
		
		break; //end case w 
		
		default: 
		invaildFlag = TRUE; 
			
		UART_PutCRLF();
		UART_CPutString("r/w fail");
		UART_PutCRLF();		
			
			
	}//end read/write switch
	
	switch (rawString[2])
	{
		case  '0': 
		
		ramSelect = Ram1;
			
		UART_PutCRLF();
		UART_CPutString("ram 1");
		UART_PutCRLF();	
		
		break; //end case 0 
		
		case '1':
		
		ramSelect = Ram2;
		UART_PutCRLF();
		UART_CPutString("ram 2");
		UART_PutCRLF();	
		
		break; //end case 1 
		
		default: 
			
		UART_PutCRLF();
		UART_CPutString("ram fail");
		UART_PutCRLF();		
		invaildFlag = TRUE; 
			
	}//end address switch
	
	address[0] = rawString[4];
	address[1] = rawString[5];
	
	UART_PutCRLF();
	UART_CPutString("address: ");
	UART_PutString(address);
	UART_PutCRLF();
	
	switch (rawString[7])
	{
		case  'a'|'A': 
		UART_PutCRLF();
		UART_CPutString("ascii");
		UART_PutCRLF();
		break; //end case 0 
		
		case 'h'|'H':
		UART_PutCRLF();
		UART_CPutString("hex");
		UART_PutCRLF();
		break; //end case 1 
		
		default: 
			
		UART_PutCRLF();
		UART_CPutString("ascii/hex fail");
		UART_PutCRLF();	
			
		invaildFlag = TRUE; 
			
	}//end ascii/hex switch
	
	while((parseCounter+9)<placeCounter)
	{
		messageString[parseCounter] = rawString[(parseCounter+9)];
		parseCounter++;
		
	}//end parseCounter while 
	
	UART_PutCRLF();
	UART_PutString(messageString);
	UART_PutCRLF();
	
	placeCounter=0;
	parseCounter=0;
	
}//end stringParser

void instructions(void)
{
	//const char instructMsg[] = "Type in the form we like (I swear I'll fix this)";
	//"W # XX A Mary had a little lamb"
	UART_CPutString("Please format your request in the following format: ");
	UART_PutCRLF();
	
	UART_CPutString("R # XX A Mary had a little lamb...");
	UART_PutCRLF();
	
	UART_CPutString("R reads from a memory location");
	UART_PutCRLF();
	
	
}//end instructions



