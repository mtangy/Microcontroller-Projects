//----------------------------------------------------------------------------
// SPI SRAM Test Program
//
// PSoC Global Resources:
//   Power Setting     5.0V/24MHz
//   CPU_Clock         SysClk/1
//   32K_Select        Internal
//   PLL_Mode          Off
//   Sleep_Timer       8_Hz
//   VC1=SysClk/N     *4
//   VC2=VC1/N        *2
//                    *VC1 makes 6MHz SPIM Clock; VC2 makes 3MHz DAC Clock
//   VC3_Source        SysClk/1
//   VC3 Divider      *52
//                    *Used to set UART baud rate to 57600
//   SysClk Source     Internal
//   SysClk*2 Disable  { Any }
//   Analog Power      { Any }
//   Ref Mux           { Any }
//   AGndBypass        { Any }
//   Op-Amp Bias       { Any }
//   A_Buff_Power      { Any }
//   SwitchModePump    OFF
//   Trip Voltage      { Any }
//   LVD ThrottleBack *Disable
//                    *When enabled, an LVD event forces the CPU Clock to SysClk/8.
//   Watchdog Enable  *{ Any }
//                    *Incautious use of the Watchdog may adversely affect timing
//
// SPIM Parameters
//   Name              SPIM
//   Clock            *VC1
//                    *6MHz = 3Mbps SPI bit rate.
//   MISO              Row_2_Input_1
//   MOSI              Row_2_Output_0
//   SClk              Row_2_Output_3
//   Interrupt Mode    TXRegEmpty
//   ClockSync         Sync to SysClk
//   InvertMISO        Normal
//
// SPIM Module Notes
//  -The 23K256 SPI SRAM has a maximum clock speed of 20MHz
//   SPIM Clock must be set to two times the desired bit rate.
//  -This uses VC1 = SysClk/4 = 6MHz, yielding a bit rate of 3Mbps.
//  -Per SPIM Module datasheet, for SPI clocks greater than 1MHz,
//   the Row Input synchronization for the MISO signal should be
//   set to Async.
//  -PSoC 5V to 23K256 3.3V translation is accomplished by setting
//   all PSoC SPIM outputs to Open Drain Low drive mode and then
//   using 470ohm pull-up resistors. For 3MHz signals, a smaller
//   value resistor must be used to allow sufficient rise-time.
//  -Pinout:
//   CS   = P12 (StdCPU:    Open Drain Low)
//   SCLK = P13 (GlobalOut: Open Drain Low)
//   MOSI = P14 (GlobalOut: Open Drain Low)
//   MISO = P15 (GlobalIn:  High Z)
//
// DAC Module Notes
//  -To maximize the output sample rate, this example operates the
//   DACs at their maximum practical speed of 3MHz which is provided
//   by VC2. The Analog Column Clock MUXs for both DAC must have
//   VC2 selected manually in the [Chip] view.
//  -DAC8_WriteStall() should be used and not DAC8_WriteBlind in
//   order to prevent output glitches during the DAC update.
//
// bnoble@siue.edu 20140320
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "stdlib.h"
#include "spi_sram.h"
#include "math.h"


#define ARRAY_SIZE 64


/// testing 
/// 
// GPIO Defines
#define TRIGGER_HIGH	{TRIGGER_Data_ADDR |=  TRIGGER_MASK;}
#define TRIGGER_LOW		{TRIGGER_Data_ADDR &= ~TRIGGER_MASK;}

// Define Sampling Rates
#define SAMPLING_RATE_1250 149 // (150-1)
#define SAMPLING_RATE_1500 124 // (125-1)
#define SAMPLING_RATE_1875  99 // (100-1)
#define SAMPLING_RATE_2500  74 //  (75-1)
#define SAMPLING_RATE_3125  59 //  (60-1)
#define SAMPLING_RATE_3750  49 //  (50-1)
#define SAMPLING_RATE_6250  29 //  (30-1)
#define SAMPLING_RATE_7500  24 //  (25-1)
#define SAMPLING_RATE_9375  19 //  (20-1)

int i;

// DACUpdate Period = 4*DelSig_DecimationRate = 128 for DS232
#define DACUPDATE_PERIOD   127 // (128 - 1)

// Globals
BYTE DACUpdateDone = 0;
// add your globals here

float fScaleFactor;

int trigAdr;

char *pResult;
float voltage; 
char sampleRead;

char Svalue;
int j;
int k;
int blockNum2;
int iStatus;
char rawString[64];  
char charIn;
BOOL finishFlag;
int parseNum;
int blockNum;
BOOL displayOrcapture;
BOOL done = FALSE;
BOOL inA = TRUE;
BOOL error = FALSE;
BOOL validMode = TRUE;
void readFunction (void);
void stringParser(int parseNum);
void instruction1(void);
void instruction2(void);
void instruction3(void);
void instruction4(void);
void instruction5(void);
void instruction6(void);
void instruction7(void);
char toLower(char k);
unsigned int hexToDec(char c1, char c2, char c3, char c4);

unsigned char ascii_to_hex(unsigned char*  addressString);
WORD SPIRAM_ByteModeTest(void);
WORD SPIRAM_SequentialModeTest(void);

int sampleRateS[9]= {
SAMPLING_RATE_1250,
SAMPLING_RATE_1500,
SAMPLING_RATE_1875,
SAMPLING_RATE_2500, 
SAMPLING_RATE_3125, 
SAMPLING_RATE_3750,
SAMPLING_RATE_6250,
SAMPLING_RATE_7500,
SAMPLING_RATE_9375
};

int sampleRate; 



void main(void)
{
	int count=0;
	fScaleFactor = (float)5/(float)64;
	// Make sure nCS is high before doing anything
	nCS_HIGH;
	// Make the oscilloscope external trigger signal low. Trigger must be quickly
	// brough high-then-low when you want the oscilloscope to draw the signals
	// on DACA and DACB. Trigger (P1[1]) must be connected to the EXT TRIG input
	// on the back of the oscilloscope and the Trigger Source must be set to
	// External. The oscilloscope should also be set for Normal Mode Triggering.
	TRIGGER_LOW;
	// Enable global interrutps
	M8C_EnableGInt;
	
//	SleepTimer_Start();
//	
//	SleepTimer_EnableInt();
//	SleepTimer_Start();
	LCD_Start();

	// Start the UART
	UART_Start(UART_PARITY_NONE);
	UART_PutCRLF();

	// Start the SPIM Module
	SPIM_Start(SPIM_SPIM_MODE_0 | SPIM_SPIM_MSB_FIRST);

	// Start the DelSig custom clock source at the default sampling rate
	//DelSigClock_WritePeriod(SAMPLING_RATE_1250); //SAMPLING_RATE_1250
	DelSigClock_WritePeriod(SAMPLING_RATE_3125);
	DelSigClock_WriteCompareValue(SAMPLING_RATE_3125>>1);
	//DelSigClock_WriteCompareValue(SAMPLING_RATE_1250>>1); //SAMPLING_RATE_1250>>1
	DelSigClock_Start();

	
	// Start the analog mux and select P0[1] (Channel A) as default
	AMUX4_Start();
	AMUX4_InputSelect(AMUX4_PORT0_1);

	// Start the PGA
	PGA_Start(PGA_HIGHPOWER);

	// Start the DelSig but do not start taking samples yet.
	// Note: The DelSig PWM block output can be monitored on P1[0]. This
	// can be used to verify the sampling rate.
	DelSig_Start(DelSig_HIGHPOWER);
	
	

	// Enable interrupts on the counter that sets the DAC output rate.
	// Start the module only when actually outputting samples and
	// stop it when done. Don't forget to write the period after stoping
	// to reset the count register.
	// NOTE: You can watch this counter on P1[7] to compare desired
	// output rate with your actual output rate.
	DACUpdate_WritePeriod(DACUPDATE_PERIOD);
	DACUpdate_EnableInt();

	
	
	// Start the DACs
	DAC8A_Start(DAC8A_HIGHPOWER);
	DAC8B_Start(DAC8B_HIGHPOWER);
	UART_PutCRLF();
	UART_CPutString("Lab 11 Data Acquisition System\r\n");
	UART_CPutString("This is a project template. You fill in the details.\r\n");
	UART_CPutString("Don't forget to place your lab 10 SPI SRAM code in spi_sram.c!\r\n");
	UART_PutCRLF();
	
	// Enter the main loop

	while(1) {
		
//			instruction5();	
//		    readFunction();
//			UART_PutSHexInt(ascii_to_hex(rawString));
//			UART_PutCRLF();
//			UART_CPutString("HB T: ");
//			UART_PutSHexByte((int)rawString[0]);
//			UART_PutCRLF();
//			UART_CPutString("HB: ");
//			UART_PutSHexByte(rawString[0]);
//			UART_PutCRLF();
//			UART_CPutString("HI T: ");
//			UART_PutSHexInt((int)rawString[0]);
//			UART_PutCRLF();
//			UART_CPutString("HC T: ");
//			UART_PutChar((int)rawString[0]);
//			UART_PutCRLF();
//			UART_CPutString("HC: ");
//			UART_PutChar(rawString[0]);
//			UART_PutCRLF();
//			UART_PutCRLF();
//			UART_PutChar(hexToDec(rawString[3], rawString[2], rawString[1], rawString[0]));
//			UART_PutCRLF();
//        	UART_PutCRLF();
			
		
		validMode = TRUE;
		UART_PutCRLF();
		UART_PutCRLF();
		instruction1();	
		readFunction();
		stringParser(1);
		
		if (validMode){
			
		if(displayOrcapture){
			
			    error = FALSE;
				instruction3();	
			    readFunction();
			    stringParser(2);
			
			if(!error){
		
			instruction7();	//block num 
		    readFunction();
		    stringParser(5);
			}
			
			
		if(!error){
					
		      	 UART_PutCRLF();
			 	 UART_CPutString("Displaying waveform (press any key to exit)");	
			     UART_PutCRLF();
				 UART_PutCRLF();
			
			done = FALSE;
			while (!done){
				j=(8192*(blockNum-1));
				k=(8192*(blockNum2-1));
				while (j<(blockNum*8192) &&  k<(blockNum2*8192)){
					
				k++;
				j++; 

				if (UART_cReadChar()){done = TRUE;}
					
//				if (j = trigAdr){
//					TRIGGER_Data_ADDR |= TRIGGER_MASK;
//					for(i=0 ; i<10000 ; i++);
//					TRIGGER_Data_ADDR &= ~TRIGGER_MASK;	
//				}
     			
			
				    DAC8A_WriteStall(SPIRAM_ReadByte(j));
					DAC8B_WriteStall(SPIRAM_ReadByte(k));
		
			
				if (UART_cReadChar()){done = TRUE;}
				
	            }//end DAC1 while
				
				if (UART_cReadChar()){done = TRUE;}
				
			}//end DAC while
		
		}//end error-if	
		
		}else {
		
			error = FALSE;
			
			if(!error){
			instruction6();	//input
		    readFunction();
		    stringParser(3);
			}
			if(!error){
			instruction2();	//block num 
		    readFunction();
		    stringParser(2);
			}
			
			if(!error){
			instruction4();	//sample rate 
		    readFunction();
		    stringParser(4);
			}
			
			if(!error){
			DelSigClock_WritePeriod(sampleRate);
			DelSigClock_WriteCompareValue(sampleRate>>1);
			}
			
			if(!error){
			instruction5();	
		    readFunction();
		    stringParser(4);
			}
			
			if (!error){
			UART_CPutString("Saving waveform");	
			 UART_PutCRLF();
			 UART_PutCRLF();
				
			DelSig_StartAD();
			for (j=(8192*(blockNum-1)); j<(blockNum*8192); j++){
			
			while (!DelSig_fIsDataAvailable()){}
			
			Svalue = DelSig_bGetData();
			SPIRAM_WriteByte(j,Svalue);
			DelSig_ClearFlag();	
			
			}//end save for
			DelSig_StopAD();
			}//end final if not error
		}//endSaveElse	
			
		///////////////////////////////	
		}//end ifValidMode
	}//end_While1	

} //endmain

/*****************************************************************************/
/********************* Interrupt Service Routines Below **********************/
/*****************************************************************************/
#pragma interrupt_handler DACUpdate_ISR

// DACUpdate_ISR is called at the terminal count of the DACUpdate user module.
// Since it's clock source is the same as DelSig, setting its period to
// match the DelSig PWM (4*DecimationRate) will cause it to interrupt at the
// same rate as the DelSig's sampling rate. If the samples are only sent to
// the DACs when the variable DACUpdateDone is one, the output sampling rate
// can be controlled.
void DACUpdate_ISR(void)
{
	
	// Updating the DACs inside the ISR takes more clock cycles
	// than simply setting a flag and exiting. This is because
	// the C-compiler does a full preserve and restore of the
	// CPU context which takes 190+185 CPU cycles.
	
	DACUpdateDone = 1;
}


void readFunction (void)
{
        int placeCounter = 0;
        finishFlag= FALSE;
		
		UART_CPutString(">");
	
        while (!finishFlag) {

                		charIn = UART_cReadChar();
                        while (charIn == 0x00){charIn = UART_cReadChar();}
                                if (placeCounter<7){

                            if (charIn == 0x0d){ //if carriage return
                                                UART_CPutString("\r\n");
                                                UART_CPutString("\r\n");
                                            finishFlag = TRUE;
                                    } //end if CR
									//backspace
                                else if ((charIn == 0x08 || charIn ==0x7f) && placeCounter > 0 ){ //if backspace
                                        placeCounter--;
                                        UART_CPutString("\x8\x20\x8");
                                } //end if backspace
                                else {
                                                rawString[placeCounter] = charIn;
                                                UART_PutChar(rawString[placeCounter]);
                                                placeCounter++;
                                        }// end else write into string

                                } // end placeCounter if
                        else
                                {

                                       	 UART_CPutString("Too many characters.");
									   	 UART_PutChar(0x07);
                                         finishFlag = TRUE;
									   //addbell
                                }

        }//end while (~finsihFlag)

        finishFlag= FALSE ;

}//end readFunction
void stringParser(int parseNum){

	switch (parseNum) {
			
	case 1:  
				switch (rawString[0]){
						case 'd':  displayOrcapture = TRUE; 
						break;
						case 'c':  displayOrcapture = FALSE;
						break;				
						default: 
							UART_CPutString("Invalid Mode");
							UART_PutChar(0x07);
							validMode = FALSE;
							UART_PutCRLF();
							UART_PutCRLF();
						break;
					}
	break;
				
	case 2: 
		switch (rawString[0]){
					case '1': blockNum = 1;
					break;
					case '2': blockNum = 2;
					break;
					case '3': blockNum = 3;
					break;
					case '4': blockNum = 4;
					break;
					default: 
						UART_CPutString("Invalid block #");
						UART_PutChar(0x07);
						error = TRUE;
				        UART_PutCRLF();
						UART_PutCRLF();
						//M8C_Reset;
					break;
				}					
	break;
			
	case 3:  
				switch (rawString[0]){
					case 'a':  
						       AMUX4_InputSelect(AMUX4_PORT0_1);
								inA = TRUE;
					break;
					case 'b':  AMUX4_InputSelect(AMUX4_PORT0_7);
								inA = FALSE;
					break;
					default: 
						UART_CPutString("Invalid input");
						UART_PutChar(0x07);
						error = TRUE;
						UART_PutCRLF();	
						UART_PutCRLF();
						//M8C_Reset;
					break;
				}									
	break;
		
	case 4:  
		
			switch (rawString[0]){
				    case '1': sampleRate = sampleRateS[0];
					break;
					case '2':sampleRate = sampleRateS[1];
					break;
					case '3': sampleRate = sampleRateS[2];
					break;
					case '4': sampleRate = sampleRateS[3];
					break;
					case '5': sampleRate = sampleRateS[4];
					break;
					case '6': sampleRate = sampleRateS[5];
					break;
					case '7': sampleRate = sampleRateS[6];
					break;
					case '8': sampleRate = sampleRateS[7];
					break;
					case '9': sampleRate = sampleRateS[8];
					break;
					default: 
						UART_CPutString("Invalid sample rate #");
						UART_PutChar(0x07);
						error = TRUE;
						UART_PutCRLF();
						UART_PutCRLF();
						//M8C_Reset;
					break;
				}				
	break;	
			
	case 5:  		
		switch (rawString[0]){
					case '1': blockNum2 = 1;
					break;
					case '2': blockNum2 = 2;
					break;
					case '3': blockNum2 = 3;
					break;
					case '4': blockNum2 = 4;
					break;
					default: 
						UART_CPutString("Invalid block #");
						UART_PutChar(0x07);
						error = TRUE;
				        UART_PutCRLF();
						UART_PutCRLF();
						//M8C_Reset;
					break;
				}								
	break;
					
	default: 	
			M8C_Reset;
			break;
	}

} 
void instruction1(void)
{
		UART_CPutString("Would you like to (d)isplay waveform or (c)apture waveform?  ");
		UART_PutCRLF();
		UART_CPutString(">");
	
}

void instruction2(void)
{
		UART_CPutString("Which block to save to? (Choose 1, 2, 3, or 4) ");
		UART_PutCRLF();
		UART_CPutString(">");
	
}

void instruction3(void)
{
		UART_CPutString("Which block to read from DAC A? (Choose 1, 2, 3, or 4) ");
		UART_PutCRLF();
		UART_CPutString(">");	
}

void instruction4(void)
{
		UART_CPutString("Choose sample rate");
		UART_PutCRLF();
		UART_CPutString("1 for 1.25ksps, 2 for 1.5ksps, 3 for 1.87ksps, 4 for 2.5ksps");
		UART_PutCRLF();
		UART_CPutString("5 for 3.125ksps, 6 for 3.75ksps, 7 for 6.25ksps, 8 for 7.5ksps, 9 for 9.375ksps");
		UART_PutCRLF();
		UART_CPutString(">");
}

void instruction5(void)
{
		UART_CPutString("Enter address to set trigger on within block in decimal or hex (Perferably decimal)");
		UART_PutCRLF();
		UART_CPutString(">");
	
}
void instruction6(void)
{
		UART_CPutString("Which Input would you like to save 'a' or 'b' ?");
		UART_PutCRLF();
		UART_CPutString(">");
	
}
void instruction7(void)
{
		UART_CPutString("Which block to read from DAC B? (Choose 1, 2, 3, or 4) ");
		UART_PutCRLF();
		UART_CPutString(">");	
}
//char asciiToHex(char addressByte)
//{
//        char output;
//        BOOL lowerCase = FALSE;

//		if(addressByte>= 0x41 && addressByte<= 0x5a)
//		{
//			addressByte -= 0x37;
//			
//		}  
//
//        if (addressByte >= 0x30  && addressByte <= 0x39){	
//						
//						UART_CPutString("integer");
//						UART_PutCRLF();
//                      output = addressByte - 0x30;
//		}
//		 if (addressByte >= 0x61  && addressByte <= 0x66){	
//						
//						/// Add conditional if 
//						UART_CPutString("Upper case");
//						UART_PutCRLF();
//                        output = addressByte - 0x51;
//		} 
//
//		if (!(addressByte >= 0x30  && addressByte <= 0x39)&& !(addressByte >= 0x61  && addressByte <= 0x7a))
////		{
////				
//////			   	invaildFlag=TRUE;
//////               	UART_CPutString("Not valid Hex address");
//////				UART_PutChar(0x07);
////		}
//        return output;
//
//}//end asciiToHex

unsigned char ascii_to_hex(unsigned char*  addressString)
{
   unsigned char hundred, ten, unit, value;

   hundred = (*addressString-0x30)*100;
   ten = (*(addressString + 1)-0x30)*10;
   unit = *(addressString+2)-0x30;     

   value = (hundred + ten + unit);
   //printf("\nValue: %#04x \n", value);

   return value; 
}

char toLower(char k) {
	if (k >= 'A' && k <= 'Z') {
		return k + 0x20;	
	} else {	
		return k;
	}
}

unsigned int hexToDec(char c1, char c2, char c3, char c4) {
	int total = 0;
	
	if (c1 >= 'a' && c1 <= 'z') c1 -= 0x57;
	else c1 -= 0x30;
	if (c2 >= 'a' && c2 <= 'z') c2 -= 0x57;
	else c2 -= 0x30;
	if (c3 >= 'a' && c3 <= 'z') c3 -= 0x57;
	else c3 -= 0x30;
	if (c4 >= 'a' && c4 <= 'z') c4 -= 0x57;
	else c4 -= 0x30;
	
	total += c1*4096;
	total += c2*256;
	total += c3*16;
	total += c4;
	
	return total;
 }