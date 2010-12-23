/*! \file serial.c \brief Simplified serial communication functions. */
/*****************************************************
	serial.c 10/27/10 Joe Pardue

	The serial library is analogous to the Arduino serial functions
	but expanded to use the regular avrlibc printf and printf_P

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


#include "serial.h"

#include <stdio.h>
#include "..\usart.h"
#include "..\fifo.h"

#if defined(Butterfly) 
#include "..\butterfly.h"
#endif


// Instantiate a fifo buffer
struct fifo_struct buffer;
#define SIZE 16
uint8_t usart_buffer[SIZE];


/************************************************************/
/*!	
	\brief Sets the baudrate and initializes the fifo, usart,
	and device (if needed).

	\param uint32_t baudrate

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
void serial_begin(uint32_t baudrate)
{
	usart_init(baudrate);

	#if defined(Butterfly) 
		butterfly_init();
	#endif

	// Initialize the fifo buffer
	fifo_init(&buffer, usart_buffer, SIZE);

	// Send buffer to the uart library
	usart_set_buffer(buffer);

}

/************************************************************/
/*!	
	\brief Shuts down the usart and ???

	\param uint32_t baudrate

	\todo Implement

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
void serial_end(void)
{
	// TODO - IMPLEMENT
}


/************************************************************/
/*!	
	\brief Returns the buffer length so this can be used as
	a boolean query since a buffer length of 0 is boolean false.

	\return uint8_t the buffer.length. 

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
uint8_t serial_available(void)
{
	return buffer.length;	
}

/************************************************************/
/*!	
	\brief Reads a byte from the buffer

	\return uint8_t byte read

	\todo Improve error checking - what happens if you read
	an empty buffer?

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
uint8_t serial_read(void)
{
	return fifo_get_byte(&buffer);
}


/************************************************************/
/*!	
	\brief Reads a byte from the buffer at the specified index

	\param uint8_t index the index into the buffer

	\return uint8_t byte read

	\todo Improve error checking - what happens if you read
	outside the buffer?

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
uint8_t serial_read_at_index(uint8_t index)
{
	return fifo_get_byte_at_index(&buffer, index);
}

/************************************************************/
/*!	
	\brief Flushes the buffer by reseting the length and index.
	This is protected from usart ISR put bytes. This does not
	set the bytes to zero.

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
void serial_flush(void)
{
	cli();
	buffer.length = 0;
	buffer.index = 0;
	sei();

}

/************************************************************/
/*!	
	\brief Sends bytes from a buffer of a given size out the usart.

	\param uint8_t *buff pointer to a buffer
	\param uint9_t size size of the buffer

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
void serial_write(uint8_t *buff, uint8_t size)
{
	for(int i = 0; i < size; i++)
	{
		usart_send_byte(buff[i]);
	}
}


