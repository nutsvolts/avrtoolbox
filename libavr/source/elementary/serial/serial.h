/*
$Date$
$Revision$
$HeadURL$
$Author$
*/

/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2011, and Joe Pardue, All rights reserved.
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
 *  - Neither the name of Joe Pardue nor the names of 
 *    its contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission. 
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
 
 // Some of this code may have elements taken from other code without attribution.
 // If this is the case it was due to oversight while debugging and I apologize.
 // If anyone has any reason to believe that any of this code violates other licenses
 // please contact me with details so that I may correct the situation. 

#ifndef SERIAL_H
#define SERIAL_H

//#include "..\devices\devices.h"
#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h"
#include "c:\avrtoolbox\libavr\source\general\util\util.h"

#define BUFFER_DELAY 20

/*!
	\defgroup serial Elementary Serial Communications Functions
*/

/*! 
	\ingroup serial

	\brief Gets the number of bytes that have arrived from the serial port and are available for reading from the 128 byte buffer.

	\return uint8_t bytes available in the serial receive buffer up to 128.
	
	Example:
	\code
	void loop()
	{
		if(serial_available() > 16) 
		{
			process_serial_input();
		}
	}
	\endcode
*/
uint8_t serial_available(void);


/*! 
	\ingroup serial

	 Sets up the serial communication with the transmission data rate (baudrate).
	
	\param baudrate: 32-bit integer (uint32_t). Recommended that you only use one of the standard rates of: 300, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200.
	
	Example:
	\code	
	void setup()
	{
		// Set up serial port for 57600 baud
		serial_begin(57600);
	}
	\endcode
*/
void serial_begin(uint32_t baudrate);

/*! 
	\ingroup serial

	\brief Returns the serial communications elements to their default values.
	
	Example:
	\code	
	void shut_down()
	{
		serial_end();
		sleep();
	}
	\endcode
*/
void serial_end(void);

/*! 
	\ingroup serial

	\brief Clear out any data in the serial buffer. Subsequent calls to serial_in() or serial_available() will only return data that has arrived since the call to serial_flush().
	
	Example:
	\code
	// Received unknown command, restart the conversation 
	serial_out("Unknown command: %d, flushing buffer.", last_command);
	// Throw out everything
	serial_flush();
	\endcode

*/
void serial_flush(void);

/*! 
	\ingroup serial

	\brief Inputs incoming serial data one byte at a time, returns -1 if no data is available.
	
	\return 8-bit signed integer (int8_t) - the first byte of incoming data or returns -1 if no data available.

	Example:
	\code	
	// Define and receive a serial byte
	int8_t myByte = serial_in();

	// Is it '!'
	if(myByte == '!')
	{
		process_exclamation();
	}	
	\endcode
	
*/
uint8_t serial_in(void);

/*! 
	\ingroup serial 

	\brief Outputs formatted data based on conversion symbols and escape character sequences contained in a string of text. 
	Syntax: serial_out(string_with_N_data_format_symbols, data1, data2, ... dataN);

	\param buff pointer to a string with format data.
	\param size uint8_t number of characters in the buffer.

	\return The number of characters printed or a negative number if an error occurred.
	
	\note
	Conversion symbols: 
	%c - print an ASCII character
	%s - print a character string
	%d or %i - print a decimal integer
	%x - print a hexadecimal integer. Note that we usually precede this with the characters 0x to output, for instance if the hexadecimal number is 5A, the output will be 0x5A.

	Control characters:
	\n - print a new line
	\" - print a quotation mark
	\\ - print a forward slash	
	
	Examples:
	\code	
	Example 1: 
	uint8_t my_char = '!';
	uint8_t my_string[] = { 'H', 'e', 'l', 'l', 'o', 0};
	my_byte = 42;

	serial_out("Print a character: %c, a string: %c, a decimal integer: %d, a hexadecimal integer: 0x%X, a forward slash: \\, a quote: \", a new line: \n next line.", my_char, my_string, my_byte, my_byte);

	Which shows in the terminal as: 
	Print a character: !, a string: Hello, a decimal integer: 42, a hexadecimal integer: 0x2A, a forward slash \, a quote ", and a new line:
	next line.

	Example 2:
	uint8_t  my_day = 21;
	uint8_t my_month[] = {'J','u','l','y',0};
	uint16_t my_year = 1980;

	serial_out( "Your date of birth is:\n Day %d \nMonth: %s  \nYear %d.", my_day, my_month, my_year); 

	Which shows in the terminal as: 

	Your date of birth is:
	Day 21
	Month July
	Year 1980
	\endcode


	\note More advanced users may note that this is a macro wrapper for the C Standard Library printf() function with the string stored in flash and the output directed to the USART, but the documentation here is kept simple for use by novices. If you want to use floating point conversions - DON'T. That facility is not included since it causes the code size to increase more than is warranted by the convenience. If you really need floating point consider using the special printf() functions as documented in avrlibc.
*/
void serial_out(const char *fmt, ...);

/*! 
	\ingroup serial

	\brief Outputs the indicated number of bytes
	
	\param *buff a pointer to a uint8_t buffer
	\param size uint8_t number of buffer elements to output

	Example:
	\code	
	for(int i = 0 ; i < count; i++)
	{
		buf[i] = serial_in();
	}
			
	serial_write(buf,count);
	
	\endcode
	
*/
void serial_write(uint8_t *buff, uint8_t size);




#endif


