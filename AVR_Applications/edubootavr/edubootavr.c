/*****************************************************
	edubootavr Joe Pardue 7/24/10
******************************************************/

// I HATE LICENSES LIKE THIS >>BUT<< I've been told that without
// the license then the work is automatically copyrighted in my name
// since my purpose is to educate, I want the code to be used by whoever
// wants to use it to learn something. If you like it, then visit
// my website www.smileymicros.com and buy something.

/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2008, Smiley Micros, All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 *   
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *   
 *  - Neither the name of the Smiley Micros nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission. 
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

// And to further cover my ass, let me add that if you use this software
// it will destroy whatever machine you use it on and kill anyone in a one 
// kilometer radius. So don't even consider using it for any reason whatsoever!

#include "edubootavr.h"  



// From Peter Fluery AVRFreaks Aug 10 2005 - to remove interrupt Vector table
// put -nostartfiles in LDFlags, add the following function saves wasted space
void __jumpMain (void) __attribute__ ((naked)) __attribute__ ((section (".init9")));

void __jumpMain(void)
{   
    asm volatile ( ".set __stack, %0" :: "i" (RAMEND) );
    asm volatile ( "clr __zero_reg__" );        // r1 set to 0
    asm volatile ( "rjmp main");                   // jump to main()
} 


int main(void) 
{ 
	// Set up the USART
	Initialization();
	
	// Run the boot load stuff
	AVR109CommandParser();

	// Jump to the application section
	application_ptr();
}



/*****************************************************
	Bootloader Functions
******************************************************/

// Note that the function name is the command
// except where otherwise commented. 
void AVR109CommandParser()
{
	uint8_t cmd;

	while(1)// Loop forever
	{
		cmd = receiveByte();

		switch (cmd)
		{
			case 'P':// Enter program mode
			case 'L':// Leave program mode
				sendByte('\r');
				break;
			case 'a':
				autoIncrementAddress();
				break;
			case 'A':
				setAddress();
				break;
			case 'e':
				chipErase();	
				break;
			case 'T':
				selectDeviceType();
				break;				
			case 's':
				readSignatureBytes();	
				break;			
			case 't':
				returnSupportedDeviceCodes();	
				break;
			case 'S':
				returnSoftwareIdentifier();	
				break;			
			case 'p':
				returnProgrammerType();	
				break;			
			case 'b':
				checkBlockSupport();	
				break;
			case 'B': // Start Block Flash Load
			case 'g': // Start Block Flash Read
				startBlockAction(cmd);
				break;
			case 'E':
				exitBootloader();
				break;									
			default:
				if(cmd != 0x1B) sendByte('?');
				break;
		}
	}
}	

/*****************************************************
	AVR109 Self Programming Commands
******************************************************/

void autoIncrementAddress(void) // 'a'
{ 
	// Yes, this code autoincrements
	sendByte('Y');
}

void setAddress(void) // 'A'
{ 
	// Note that flash addresses are in words, not bytes               
    address = receiveByte();   
	address = (address << 8) | receiveByte();
	address = address << 1; // convert word address to byte address

 	sendByte('\r');  // respond okay
}

void chipErase(void) // 'e'
{ 
 	int i;
 	for(i = 0 ; i < (FLASHEND - (BOOTSIZE * 2)); i += SPM_PAGESIZE)
	{
    	boot_page_erase(i);//_safe(i);	// Erase the page
    	boot_spm_busy_wait();		// Wait until finished.
	}
   
	sendByte('\r');  // respond okay
}

void selectDeviceType() // 'T'
{
	//dummy read since we only have one device type
	uint8_t dummy;
	dummy = receiveByte();
	sendByte('\r');
}

void readSignatureBytes(void) // 'S'
{ 
    sendByte( SIGNATURE_BYTE_3 );
    sendByte( SIGNATURE_BYTE_2 );
    sendByte( SIGNATURE_BYTE_1 );
}

void returnSupportedDeviceCodes(void) // 't'
{
	//sendByte((char)0); // list terminator
	sendByte(SUPPORTED_DEVICE_CODE); // Support only this device
	sendByte((char)0); // list terminator
	// Wait for empty transmit buffer 
	//while ( !( USART_CONTROL_STATUS_REG_A & (1<<USART_READY_TO_TRANSMIT)) );
	// Put data into buffer, sends the data
	//USART_DATA_REG = 0;

}

void returnSoftwareIdentifier(void) // 'S'
{ 
    // Software identifier is 'AVRBOOT'
	sendByte('A');
    sendByte('V'); 
    sendByte('R');
    sendByte('B');
    sendByte('O');
    sendByte('O');
    sendByte('T');
}

void returnProgrammerType(void) // 'p'
{      
	// Get programmer type - serial.
    sendByte('S');
}

void checkBlockSupport(void) // 'b'
{ 
    sendByte('Y'); // yes, block load is supported.
    sendByte((SPM_PAGESIZE>>8) & 0xFF); // send MSB first.
    sendByte(SPM_PAGESIZE & 0xFF); // send LSB second.
}

void startBlockAction(uint8_t cmd)
{
	uint8_t tempRec;
	uint16_t tempSize;

	tempSize = (receiveByte() << 8) | receiveByte();
	// dummy read for type - we only do flash NOT EEPROM
	tempRec = receiveByte(); 
	if(cmd == 'B') blockFlashLoad( tempSize );
	else blockFlashRead( tempSize  );
}

void blockFlashLoad(uint16_t size)
{ 
	uint16_t tempAddress = address;

	uint16_t i,tempWord;

	// store values to be programmed in temporary buffer
	for (i=0; i<USART_RX_BUFFER_SIZE; i++) {
		if (i<size) pageBuffer[i]=receiveByte();
		else pageBuffer[i]=0xFF;
	}
	i=0;
 
    boot_page_erase(address);//_safe(address);	// Perform page erase
    boot_spm_busy_wait();		// Wait until the memory is erased.

    for(i = 0; i < size; i+=2)
	{
		tempWord = pageBuffer[i]; // load the little end then increment i
		tempWord += (pageBuffer[i+1] << 8); // load the big end
        boot_page_fill(address,tempWord);;//_safe(address,tempWord);
    							
        address = address + 2;  	// word increment
    } 
    
    boot_page_write(tempAddress);//_safe(tempAddress);
    boot_spm_busy_wait();	
    boot_rww_enable();				// Re-enable the RWW section   

	sendByte('\r');
}

void blockFlashRead(uint16_t size)
{ 
	uint8_t data;
	do {
		// read_program_memory(address,0x00);
		data = pgm_read_byte_near(address++);
		// send byte
		sendByte(data);
		// reduce number of bytes to read by one
		size--;	
								
	} while (size);	// loop through size
}


void exitBootloader()
{
	sendByte('\r');
}


/*****************************************************
	USART Functions
******************************************************/
void USARTInit()
{
	// Set baud rate hard coded to 19200 for 12MHz
	//USART_BAUD_RATE_LOW = 38;

	USART_BAUD_RATE_LOW =(uint8_t)(F_CPU/(BAUD*16L)-1);
	// Enable receiver and transmitter
	USART_CONTROL_STATUS_REG_B = (1 << USART_ENABLE_RECEIVER) | (1 << USART_ENABLE_TRANSMITTER);
	// Set frame format: n,8,1
#if defined(ATmega644)
	USART_CONTROL_STATUS_REG_C |= (1 << USART_STOP_BIT_SELECT) | (1 << USART_CHARACTER_SIZE);  
#elif defined(ATmega32)
	USART_CONTROL_STATUS_REG_C |= (1 << USART_REGISTER_SELECT) | (1 << USART_CHARACTER_SIZE_0) | (1 << USART_CHARACTER_SIZE_1);

#elif defined(Butterfly)
	// for the Butterfly reuse the Atmel code for the USART in the intialization process
#else
   #error "No USART definition for MCU in USARTInit"
#endif 
}

void sendByte( uint8_t data )
{
	wdt_reset(); // reset the watchdog timer, if it is set
	// Wait for empty transmit buffer 
	while ( !( USART_CONTROL_STATUS_REG_A & (1<<USART_READY_TO_TRANSMIT)) );
	// Put data into buffer, sends the data
	USART_DATA_REG = data;
}

uint8_t receiveByte( void )
{
	uint32_t count = 0;

	wdt_reset(); // reset the watchdog timer, if it is set
	// Wait for data to be received 
	while ( !(USART_CONTROL_STATUS_REG_A & (1<<USART_RECEIVE_COMPLETE)) )
	{
		if(count++ >= (F_CPU >> 4)) application_ptr();
	}
	
	count = 0;	
		
	// Get and return received data from buffer 
	return USART_DATA_REG;
}

/*****************************************************
	Initialization
******************************************************/

void Initialization()
{
	USARTInit();

#if defined(Butterfly)


    OSCCAL_calibration();   // Calibrate the OSCCAL byte

    ACSR = (1<<ACD);

    // Disable Digital input on PF0-2 (power save)
    DIDR1 = (7<<ADC0D);

    PORTB = 0xFF;       // Enable pullups on Ports B and E
    PORTE = 0xFF;
    
    // boost IntRC to 2Mhz to achieve 19200 baudrate
    CLKPR = (1<<CLKPCE);        // set Clock Prescaler Change Enable
    // set prescaler = 4, Inter RC 8Mhz / 4 = 2Mhz
    CLKPR = (1<<CLKPS1);    

    UBRRH = 0;//(unsigned char)(baudrate>>8);
    UBRRL = 12;//(unsigned char)baudrate;

    // Enable 2x speed
    UCSRA = (1<<U2X);

    // Enable receiver and transmitter
    UCSRB = (1<<RXEN)|(1<<TXEN)|(0<<RXCIE)|(0<<UDRIE);

    // Async. mode, 8N1
    UCSRC = (0<<UMSEL)|(0<<UPM0)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
        
    MCUCR = (1<<IVCE);       
    MCUCR = (1<<IVSEL);             //move interruptvectors to the Boot sector    

    sei(); // mt __enable_interrupt();
    
    // mt PCMSK1 = (1<<PORTB6) | (1<<PORTB4);
	PCMSK1 = (1<<PINB6) | (1<<PINB4);       // set pin-change interrupt mask
  	EIFR   = (1<<PCIF1);                    // clear external intterupt flag 1
	EIMSK  = (1<<PCIE1);   

#endif
}


// Only compile if Butterfly is defined in SmileyBootloader.h
#if defined(Butterfly)
/*****************************************************
	Oscillator Calibration
	The following code is taken directly from Martin Thoma's
	port of Atmel's IAR Butterfly software to GCC
******************************************************/
/*****************************************************************************
*
*   Function name : OSCCAL_calibration
*
*   Returns :       None
*
*   Parameters :    None
*
*   Purpose :       Calibrate the internal OSCCAL byte, using the external 
*                   32,768 kHz crystal as reference
*
*****************************************************************************/
void OSCCAL_calibration(void)
{
    unsigned char calibrate = 0;//FALSE;
    int temp;
    unsigned char tempL;

    CLKPR = (1<<CLKPCE);        // set Clock Prescaler Change Enable
    // set prescaler = 8, Inter RC 8Mhz / 8 = 1Mhz
    CLKPR = (1<<CLKPS1) | (1<<CLKPS0);
    
    TIMSK2 = 0;             //disable OCIE2A and TOIE2

    ASSR = (1<<AS2);        //select asynchronous operation of timer2 (32,768kHz)
    
    OCR2A = 200;            // set timer2 compare value 

    TIMSK0 = 0;             // delete any interrupt sources
        
    TCCR1B = (1<<CS10);     // start timer1 with no prescaling
    TCCR2A = (1<<CS20);     // start timer2 with no prescaling

    while((ASSR & 0x01) | (ASSR & 0x04));       //wait for TCN2UB and TCR2UB to be cleared

    Delay(1000);    // wait for external crystal to stabilise
    
    while(!calibrate)
    {
        cli(); // mt __disable_interrupt();  // disable global interrupt
        
        TIFR1 = 0xFF;   // delete TIFR1 flags
        TIFR2 = 0xFF;   // delete TIFR2 flags
        
        TCNT1H = 0;     // clear timer1 counter
        TCNT1L = 0;
        TCNT2 = 0;      // clear timer2 counter
           
	while ( !(TIFR2 & (1<<OCF2A)) ); // while ( !(TIFR2 && (1<<OCF2A)) );   // wait for timer2 compareflag
    
        TCCR1B = 0; // stop timer1

        sei(); // __enable_interrupt();  // enable global interrupt
    
        if ( (TIFR1 & (1<<TOV1)) ) // if ( (TIFR1 && (1<<TOV1)) )
        {
            temp = 0xFFFF;      // if timer1 overflows, set the temp to 0xFFFF
        }
        else
        {   // read out the timer1 counter value
            tempL = TCNT1L;
            temp = TCNT1H;
            temp = (temp << 8);
            temp += tempL;
        }
    
        if (temp > 6250)
        {
            OSCCAL--;   // the internRC oscillator runs to fast, decrease the OSCCAL
        }
        else if (temp < 6120)
        {
            OSCCAL++;   // the internRC oscillator runs to slow, increase the OSCCAL
        }
        else
            calibrate = 1;//TRUE;   // the interRC is correct
    
        TCCR1B = (1<<CS10); // start timer1
    }
}


/*****************************************************************************
*
*   Function name : Delay
*
*   Returns :       None
*
*   Parameters :    unsigned int millisec
*
*   Purpose :       Delay-loop
*
*****************************************************************************/
void Delay(unsigned int millisec)
{
    unsigned char i; // mt int i;
    
    while (millisec--)
        for (i=0; i<125; i++);
}

#endif
