// Prevent duplicate inclusion of this file
#ifndef SERIAL_H
#define SERIAL_H

/* ********************************************************** */
/*!	
	\mainpage Serial Functions Library
	
	\brief The serial library contains elementary functions that
	mimic the Arduino serial functions, but adding a simple wrapper
	function for the standard C printf() function with the output
	sent to the uart for output.
		
	This code was tested on the ATmega169 (AVR Butterfly, ATmega328
	(Arduino)(TODO), and ATmega644 (BeAVR)(TODO)

	Location: avrtoolbox\Libraries\Elementary\serial

	\todo test it for the ATmega328 and ATmega644

	\author Joe Pardue 
	\license New BSD
	\date December 12, 2010
	\version 1.00
*/

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

#include <inttypes.h>
#include <avr\pgmspace.h>

#include "devices.h"
#include "usart.h"
#include "fifo.h"

/*! \def usart buffer size */
#define SIZE 16
uint8_t usart_buffer[SIZE];

/*! \struct Instantiate a fifo buffer */
struct fifo_struct buffer;


/************************************************************/
/*!	
	\brief Sets the baudrate and initializes the fifo, usart,
	receive ISR, and device (if needed).

	\param uint32_t baudrate Select a standard baudrate: 300, 1200,
	 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200. 

	\warning If you don't want to use one of these baudrates then it
	is strongly recommended that you do not use the serial
	function library.


	\author Joe Pardue 
	\date November 8, 2010
	\version 1.00
*/
/************************************************************/
void serial_begin(uint32_t baudrate);

/************************************************************/
/*!	
	\brief Shuts down the usart and ???

	\todo Implement - IS THIS REALLY NEEDED?

	\author Joe Pardue 
	\date November 8, 2010
	\version 1.00
*/
/************************************************************/
void serial_end(void);

/************************************************************/
/*!	
	\brief Returns the buffer length so this can be used as
	a boolean query since a buffer length of 0 is boolean false.

	\return uint8_t the buffer.length. 

	\author Joe Pardue 
	\date November 8, 2010
	\version 1.00
*/
/************************************************************/
uint8_t serial_available(void);

/************************************************************/
/*!	
	\brief Reads a byte from the buffer

	\return uint8_t byte read

	\todo Improve error checking - what happens if you read
	an empty buffer?

	\author Joe Pardue 
	\date November 8, 2010
	\version 1.00
*/
/************************************************************/
uint8_t serial_read(void);

/************************************************************/
/*!	
	\brief Reads a byte from the buffer at the specified index

	\param uint8_t index the index into the buffer

	\return uint8_t byte read

	\todo Improve error checking - what happens if you read
	outside the buffer?

	\author Joe Pardue 
	\date November 8, 2010
	\version 1.00
*/
/************************************************************/
uint8_t serial_read_at_index(uint8_t index);

/************************************************************/
/*!	
	\brief Flushes the buffer by resetting the length and index.
	This is protected from usart ISR put bytes. It does not
	set the bytes to zero.

	\author Joe Pardue 
	\date November 8, 2010
	\version 1.00
*/
/************************************************************/
void serial_flush(void);

/************************************************************/
/*!	
	\brief Sends bytes from a buffer of a given size out the usart.

	\param uint8_t *buff pointer to a buffer
	\param uint9_t size size of the buffer

	\author Joe Pardue 
	\date November 8, 2010
	\version 1.00
*/
/************************************************************/
void serial_write(uint8_t *buff, uint8_t size);

/************************************************************/
/*!	
	\brief This macro provides a wrapper for the standard C printf function
	and sends output to the usart.

	\param val1 is a string formatted for printf
	\param val2 is a variable associated with a format indicator in the string.

	\author Joe Pardue 
	\date November 8, 2010
	\version 1.00
*/
/************************************************************/
#define serial_printf(val1, val2) printf_P(PSTR(val1),val2);


#endif
