//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "string.h"

char string0[17];
char string1[17];
char string2[17];
char string3[17];
//void Start(void);

char buffer= '\0';
char buffer2= '\0';
char buffer3= '\0';
char buffer4= '\0';
char buffer5= '\0';
int placeCounter = 0;
int count;

const char promptMessage1[67]= "Would you like to read or write a string? R for read & W for write";
const char promptMessage2[28]= "Not a valid input. Goodbye";
const char promptMessage3[55]= "Which string? Type a for 1, b for 2, c for 3, d for 4";
const char promptMessage4[65]= "Do you want to print to Port or LCD? p for port & l for LCD";
const char* promptMessage1P = promptMessage1;
const char* promptMessage2P = promptMessage2;
const char* promptMessage3P = promptMessage3;
const char* promptMessage4P = promptMessage4;

void main(void)
{
	
	//UART_CPutString("\r\n1\r\n");
	string0[0] = '\0';
	string1[0] = '\0';
	string2[0] = '\0';
	string3[0] = '\0';
	
	LCD_Start();
	LCD_Position(0,0);
	LCD_PrCString("                ");	
	LCD_Position(1,0);
	LCD_PrCString("                ");	

	//LCD_PrCString(promptMessage1P);

		
	UART_Start(UART_PARITY_NONE); 
	
	UART_CPutString(promptMessage1P);
	//UART_CPutString("\r\n");
	UART_CPutString("\r\n");
	UART_PutCRLF();
	while(1) 
	{
Start:	
		buffer= '\0';
		buffer2= '\0';
		buffer3= '\0';
		buffer4= '\0';
		buffer5= '\0';
		placeCounter = 0;
		
		buffer = UART_cReadChar();
			
		//while ((buffer != 0x00)) {buffer = UART_cReadChar();}		

		if(buffer != 0x00)
		{
				
			    
				UART_CPutString(promptMessage3P);//"Which String?"	
				UART_CPutString("\r\n");
				UART_CPutString("\r\n");
				buffer2 = UART_cReadChar();
				while (buffer2 == 0x00){buffer2 = UART_cReadChar();}
			    if(buffer2 != 0x00)
				{
	
					if(buffer == 'r')
					{
						
						UART_CPutString(promptMessage4P);	
						UART_CPutString("\r\n");
						buffer4 = UART_cReadChar();
						while (buffer4 == 0x00){buffer4 = UART_cReadChar();}
							
								if (buffer4 == 'l'){
									switch(buffer2)
									{
								        case 'a':
								        	LCD_Position(0,0);
										    LCD_PrCString("                ");	
										    LCD_Position(1,0); 
										    LCD_PrCString("                ");	
											LCD_Position(0,0);
											LCD_PrString(string0);
											buffer3 = UART_cReadChar();
											while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													goto Start; 
											    }
											
								        break; 
								    	
										case 'b':
											LCD_Position(0,0);
										    LCD_PrCString("                ");	
										    LCD_Position(1,0); 
										    LCD_PrCString("                ");	
											LCD_Position(0,0);
											LCD_PrString(string1);
											buffer3 = UART_cReadChar();
											while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
												    UART_CPutString("\r\n");
													goto Start; 
											    }
										break;
										
										case 'c':	
											LCD_Position(0,0);
										    LCD_PrCString("                ");	
										    LCD_Position(1,0); 
										    LCD_PrCString("                ");	
											LCD_Position(0,0);
											LCD_PrString(string2);
											buffer3 = UART_cReadChar();
											while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
												    UART_CPutString("\r\n");
													goto Start; 
											    }
										break;
											
										case 'd':
											LCD_Position(0,0);
										    LCD_PrCString("                ");	
										    LCD_Position(1,0); 
										    LCD_PrCString("                ");	
											LCD_Position(0,0);
											LCD_PrString(string3);
											buffer3 = UART_cReadChar();
											while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													goto Start; 
											    }
											
										default: 
										UART_CPutString(promptMessage2P);		
										}
									}
									
							if (buffer4 == 'p'){
									switch(buffer2)
									{
								        case 'a':
								        	UART_CPutString("\r\n");
											UART_PutString(string0);
											buffer3 = UART_cReadChar();
											while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													goto Start; 
											    }
											
								        break; 
								    	
										case 'b':
											
											UART_CPutString("\r\n");
											UART_PutString(string1);
											buffer3 = UART_cReadChar();
											while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
												    UART_CPutString("\r\n");
													goto Start; 
											    }
												
										break;
										
										case 'c':	
											
											UART_CPutString("\r\n");
											UART_PutString(string2);
											buffer3 = UART_cReadChar();
											while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													goto Start; 
											    }
											
										break;
											
										case 'd':
											
											UART_CPutString("\r\n");
											UART_PutString(string3);
											buffer3 = UART_cReadChar();
											while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													goto Start; 
											    }
												
										break;
											
										default: 
										UART_CPutString(promptMessage2P);		
										}
									}
					
					}  
					
				
				if(buffer == 'w')
				{
				buffer2 = UART_cReadChar();	
				while (buffer2 == 0x00){buffer2 = UART_cReadChar();}	
					switch(buffer2)
					{
			        	case 'a':
							UART_PutChar(0x3e);
							while(1){
									buffer3 = UART_cReadChar();	
										while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											if (placeCounter<16){
									          while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
											
										    if (buffer3 == 0x0d){
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													UART_CPutString(promptMessage1P);
													UART_CPutString("\r\n");
													UART_CPutString("\r\n");
													goto Start; 
											    }
											if (buffer3 == 0x08 || buffer3 ==0x7f){
												placeCounter--;
												string0[placeCounter] = ' ';
												
											}
											string0[placeCounter] = buffer3;
										    UART_PutChar(string0[placeCounter]);
											placeCounter++;
											
										} // end if
										
							} // end outer while
				
		        		break; 
							
				    	case 'b':
				        	UART_PutChar(0x3e);
							while(1){
								
							buffer3 = UART_cReadChar();	
								while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
									if (placeCounter<16){
							          while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
									
								    if (buffer3 == 0x0d){
											UART_CPutString("\r\n");
											UART_CPutString("\r\n");
											UART_CPutString(promptMessage1P);
											UART_CPutString("\r\n");
											UART_CPutString("\r\n");
											goto Start; 
									    }
									
									if (buffer3 ==0x08){
										placeCounter--;
										string1[placeCounter] = ' ';
										
									}
						            
									string1[placeCounter] = buffer3;
								    UART_PutChar(string1[placeCounter]);
									placeCounter++;
									
									}else{UART_PutChar(0x07);}	
							}		
		      
						break;
							
						case 'c':	
							UART_PutChar(0x3e);
							while(1){
								
							buffer3 = UART_cReadChar();	
								while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
									if (placeCounter<16){
							          while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
									
								    if (buffer3 == 0x0d){
											UART_CPutString("\r\n");
											UART_CPutString("\r\n");
										    UART_CPutString(promptMessage1P);
											UART_CPutString("\r\n");
											UART_CPutString("\r\n");
											goto Start; 
									    }
									
									if (buffer3 == 0x08 || buffer3 ==0x7f){
										placeCounter--;
										string2[placeCounter] = ' ';
										
									}
									
									string2[placeCounter] = buffer3;
								    UART_PutChar(string2[placeCounter]);
									placeCounter++;
									
							}else{UART_PutChar(0x07);}		
							}	
						break;
				
						case 'd':
							UART_PutChar(0x3e);
							while(1){
							buffer3 = UART_cReadChar();	
								while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
									if (placeCounter<16){
							          while (buffer3 == 0x00){buffer3 = UART_cReadChar();}
									
								    if (buffer3 == 0x0d){
											UART_CPutString("\r\n");
											UART_CPutString("\r\n");
											UART_CPutString(promptMessage1P);
											UART_CPutString("\r\n");
											UART_CPutString("\r\n");
											goto Start; 
									}
									
									if (buffer3 == 0x08 || buffer3 ==0x7f){
										placeCounter--;
										string3[placeCounter] = ' ';
										
									}
									
									string3[placeCounter] = buffer3;
								    UART_PutChar(string3[placeCounter]);
									placeCounter++;
									
									}else{UART_PutChar(0x07);}	
							}		
		    			break;
							
						default: 
						UART_CPutString(promptMessage2P);		

					}
				}

		}
			
		}
			
	}
}


