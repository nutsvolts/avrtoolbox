/*! \file usart_init \brief Initializes the usart. */
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

// Keep this in the same file as the usart_put_char function
FILE mystdout = FDEV_SETUP_STREAM(usart_put_char, NULL, _FDEV_SETUP_WRITE);

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
