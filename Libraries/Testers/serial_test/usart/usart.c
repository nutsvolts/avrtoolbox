/*! \file usart.h \brief AVR usart functions using fifo buffer. */
/*****************************************************
	usart.c 11/9/10 Joe Pardue
******************************************************/
/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2010, Smiley Micros, All rights reserved.
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


#include "usart.h"

// Keep this in the same file as the usart_put_char function
FILE mystdout = FDEV_SETUP_STREAM(usart_put_char, NULL, _FDEV_SETUP_WRITE);
 
int usart_put_char(char c, FILE *stream) 
{ 
	if (c == '\n') usart_put_char('\r', stream);
   	loop_until_bit_is_set(UCSRA, UDRE); // wait for UDR to be clear 
   	UDR = c;    //send the character 
   	return 0; 
} 


struct fifo_struct buffer;

uint8_t usart_set_buffer(struct fifo_struct fifo)
{

	buffer = fifo;

	/*if( &fifo != 0) &buffer = &fifo;
	else 
	{
		usart_error(BUFFER_NULL_POINTER);
		return (0);
	}
	if( fifo_size != 0) buffer_size = fifo_size;
	else 
	{
		usart_error(BUFFER_SIZE);
		return (0);
	}*/

	return(1);
}


void usart_error(uint8_t error_num)
{

	switch(error_num)
	{
		case(BUFFER_NULL_POINTER):
			printf_P(PSTR("usart BUFFER_NULL_POINTER ERROR\r"));
			break;
		case(BUFFER_SIZE):
			printf_P(PSTR("usart BUFFER_SIZE ERROR\r"));
			break;
		default: 
			printf_P(PSTR("usart UNKNOWN ERROR\r"));
			break;
	}
}

// Used for intial testing if ISR
//extern volatile uint8_t usart_flag;
ISR(USART0_RX_vect)
{
	uint8_t b = UDR;

	// Used in testing
	//usart_flag = 1;

	// Used in testing
	// First test ping back received byte.
	//usart_send_byte(b);

	// Put char in buffer
	if (!fifo_put_byte(&buffer, b) )printf_P(PSTR("ISR fifo_put_byte Error\r")) ;	
}


void usart_enable_receive_interrupt()
{
	USART_CONTROL_STATUS_REG_B |= (1 << RXEN);
}



void usart_init(uint32_t baudrate)
{
   	stdout = &mystdout;    //set the output stream 
		
	//#if defined(Butterfly) 
	//butterfly_init();
	//#endif

	sei(); // Set the Global Interrupt Enable flag

	// Set Baud registers with values from <util\setbaud.h> in SmileyUSART.h
	USART_BAUD_RATE_HIGH = (F_CPU/(baudrate*16L)-1) >> 8;
	USART_BAUD_RATE_LOW = (uint8_t)(F_CPU/(baudrate*16L)-1);

	// Enable receiver and transmitter
	USART_CONTROL_STATUS_REG_B = (1 << RXCIE) | (1 << USART_ENABLE_RECEIVER) | (1 << USART_ENABLE_TRANSMITTER);
	// Set frame format: n,8,1

#if defined(ATmega644) || defined(Arduino)
	USART_CONTROL_STATUS_REG_C |= (1 << USART_STOP_BIT_SELECT) | (1 << USART_CHARACTER_SIZE);  
#elif defined(ATmega32)
	USART_CONTROL_STATUS_REG_C |= (1 << USART_REGISTER_SELECT) | (1 << USART_CHARACTER_SIZE_0) | (1 << USART_CHARACTER_SIZE_1);

#elif defined(Butterfly)
	// for the Butterfly reuse the Atmel code for the USART in the intialization process
#else
   #error "No USART definition for MCU in USARTInit"
#endif 

}


void usart_send_byte( uint8_t data )
{
	wdt_reset(); /// reset the watchdog timer, if it is set
	/// Wait for empty transmit buffer 
	while ( !( USART_CONTROL_STATUS_REG_A & (1<<USART_READY_TO_TRANSMIT)) );
	/// Put data into buffer, sends the data
	USART_DATA_REG = data;
}



uint8_t usart_receive_byte( void )
{
	wdt_reset(); /// reset the watchdog timer, if it is set
	/// Wait for data to be received 
	while ( !(USART_CONTROL_STATUS_REG_A & (1<<USART_RECEIVE_COMPLETE)) );	
	/// Get and return received data from buffer 
	return USART_DATA_REG;
}




void usart_send_pmstring(const char *FlashString)
{
	int i = 0;

	/// The 'for' logic terminates if the byte is '\0' or if i = 60.
	/// '\0' is 'null' and terminates C strings
	/// The 80 prevents too much overrun if we get a bad pointer
	/// and it limits the string size	
	for( i = 0 ; pgm_read_byte(&FlashString[i]) && i < 80; i++) 
	{
			usart_send_byte(pgm_read_byte(&FlashString[i]));
	}
}



/*****************************************************
///	Initialization
******************************************************/

/*void init()
{
   	stdout = &mystdout;    //set the output stream 

	usart_init(19200);

	#if defined(Butterfly) 
		butterfly_init();
	#endif

}*/



