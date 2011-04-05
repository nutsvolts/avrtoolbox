/*****************************************************
	SmileyUSART.c Joe Pardue September 10, 2010

	NOTE THAT THIS IS A PILE OF JUNK AND WILL BE REPLACED
	BY A BETTER LIBRARY SHORTLY

******************************************************/

// I HATE LICENSES LIKE THIS >>BUT<< I've been told that without
// the license then the work is automatically copyrighted in my name
// since my purpose is to educate (and learn), I want the code to be 
// used by whoever wants to use it to learn something. If you like it, 
// then visit my website www.smileymicros.com and buy something.

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

// And to further cover my butt, let me add that if you use this software
// it will destroy whatever machine you use it on and kill anyone in a one 
// kilometer radius. So don't even consider using it for any reason whatsoever!

#include "usart.h"


/*****************************************************
	USART Functions
******************************************************/
void uart_init()
{
	// Set Baud registers with values from <util\setbaud.h> in SmileyUSART.h
	USART_BAUD_RATE_HIGH = (F_CPU/(BAUD*16L)-1) >> 8;
	USART_BAUD_RATE_LOW = (uint8_t)(F_CPU/(BAUD*16L)-1);

	// Enable receiver and transmitter
	USART_CONTROL_STATUS_REG_B = (1 << USART_ENABLE_RECEIVER) | (1 << USART_ENABLE_TRANSMITTER);
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

/*uint8_t receiveByte( void )
{
	wdt_reset(); // reset the watchdog timer, if it is set
	// Wait for data to be received 
	while ( !(USART_CONTROL_STATUS_REG_A & (1<<USART_RECEIVE_COMPLETE)) );	
	// Get and return received data from buffer 
	return USART_DATA_REG;
}*/

void uart_send_byte( uint8_t data )
{
	wdt_reset(); // reset the watchdog timer, if it is set
	// Wait for empty transmit buffer 
	while ( !( USART_CONTROL_STATUS_REG_A & (1<<USART_READY_TO_TRANSMIT)) );
	// Put data into buffer, sends the data
	USART_DATA_REG = data;
}

void uart_send_bit( uint8_t data )
{
	wdt_reset(); // reset the watchdog timer, if it is set
	// Wait for empty transmit buffer 
	while ( !( USART_CONTROL_STATUS_REG_A & (1<<USART_READY_TO_TRANSMIT)) );
	
	if(data == 1)
	{
		USART_DATA_REG = '1';
	}
	else 
	{
		USART_DATA_REG = '0';
	}
}

void uart_send_stringP(const char *FlashString)
{
	int i = 0;

	// The 'for' logic terminates if the byte is '\0' or if i = 80.
	// '\0' is 'null' and terminates C strings
	// The 80 prevents too much overrun if we get a bad pointer
	// and it limits the string size	
	for( i = 0 ; pgm_read_byte(&FlashString[i]) && i < 80; i++) 
	{
			uart_send_byte(pgm_read_byte(&FlashString[i]));
	}
}

void uart_send_string(const char *String)
{
	int i = 0;

	for( i = 0 ; String[i] && i < 80; i++) 
	{
			uart_send_byte(String[i]);
	}
}
