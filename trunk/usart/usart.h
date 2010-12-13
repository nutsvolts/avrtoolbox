// Prevent duplicate inclusion of this file
#ifndef USART_H
#define USART_H
/*! \file usart.h \brief AVR usart functions using fifo buffer. */
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
//*****************************************************************************
//
//	usart.h Joe Pardue 11/9/10
//	Revised: 11/9/10
//	Version: 1.00
//	License: new BSD license shown above
//
///	\ingroup avrtoolbox_general
/// \defgroup usart USART Function Library (usart.c)
/// \code #include "usart.h" \endcode
///
/// \par Overview:
///		The usart library provides AVR usart functions for three common ways 
///		of using usarts:
///		1. Blocking transmission and receive functions.
///		2. FIFO buffered reception in the usart receive ISR
///		3. Output streamed with the standard C printf function, with constant
///			data stored in program mememory space (to save SRAM).
///
///	\par Limits:
///		The intitial library is written for a single hardware usart. And was tested
///		along with the fifo and serial libraries as part of a simplified serial
///		communication suite. Several functions that are not used in the suite were 	
///		tested with older programs, but not specifically retested for this release.
/// \par Test Software:
///		This library was tested along with the fifo and serial libraries in the 
///		serial_test.c program.
///
/// \warning You must set F_CPU (CPU frequency) to the correct device in the devices.h file. 
///		Note that some frequencies will not work with some baud rates. If you are unsure
/// 	please consult the datasheet for your device.
//
//*****************************************************************************

//@{

/// \todo make sure all these are needed
#include <avr/io.h>
#include <avr/pgmspace.h> 
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "fifo.h"
#include "..\devices.h"


struct fifo_struct buffer;


/*****************************************************
	Some of this is from Mike Perks, a generous AVRFreak
	- modified quite a bit
//! Defines for the various USART registers
///		These definitions allow us to use the code with 
///		various AVRs and the Butterfly. They also make
///		the cryptic register names a bit more readable
******************************************************/
#if defined(ATmega32) || defined(Butterfly)

   // ATMega with one USART 

   #define USART_BAUD_RATE_HIGH        	UBRRH
   #define USART_BAUD_RATE_LOW        	UBRRL
   #define USART_CONTROL_STATUS_REG_A	UCSRA
   #define USART_CONTROL_STATUS_REG_B	UCSRB
   #define USART_CONTROL_STATUS_REG_C	UCSRC
   #define USART_ENABLE_TRANSMITTER		TXEN
   #define USART_ENABLE_RECEIVER		RXEN
   #define USART_READY_TO_TRANSMIT		UDRE
   #define USART_TRANSMIT_COMPLETE		TXC
   #define USART_RECEIVE_COMPLETE		RXC
   #define USART_DATA_REG				UDR
   #define USART_STOP_BIT_SELECT 		USBS
   #define USART_CHARACTER_SIZE_0 		UCSZ0
   #define USART_CHARACTER_SIZE_1 		UCSZ1
   #define USART_REGISTER_SELECT		URSEL

#elif defined(ATmega168) || defined(ATmega644)

   // ATMega with two USARTs - USART 0
   #define USART_BAUD_RATE_HIGH			UBRR0H
   #define USART_BAUD_RATE_LOW			UBRR0L
   #define USART_CONTROL_STATUS_REG_A	UCSR0A
   #define USART_CONTROL_STATUS_REG_B	UCSR0B
   #define USART_CONTROL_STATUS_REG_C	UCSR0C
   #define USART_ENABLE_TRANSMITTER		TXEN0
   #define USART_ENABLE_RECEIVER		RXEN0
   #define USART_READY_TO_TRANSMIT		UDRE0
   #define USART_TRANSMIT_COMPLETE		TXC0
   #define USART_RECEIVE_COMPLETE		RXC0
   #define USART_DATA_REG				UDR0
   #define USART_STOP_BIT_SELECT		USBS0
   #define USART_CHARACTER_SIZE			UCSZ00

#else
   #error "no USART definition for MCU"
#endif

/*****************************************************
	USART function declarations	 
******************************************************/




/************************************************************/
/*!	
	\brief Intializes the usart using device dependent registers
	defined by defines such as ATmega644 or Butterfly. Sets the baudrate.
	Requres F_CPU be set to correct value.

	\param uint32_t baudrate 

	\todo This function should be made easier to update with additional
	defined devices.
	\todo Make F_CPU device dependent.

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
void usart_init(uint32_t baudrate);


/************************************************************/
/*!	
	\brief Resets watchdog. Blocks until data byte is sent. 

	\param uint8_t data byte to be sent

	\todo Test

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/ 
void usart_send_byte( uint8_t );

/************************************************************/
/*!	
	\brief Resets watchdog. Blocks until data byte is received. 

	\return uint8_t data byte

	\todo Test

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/ 
uint8_t usart_receive_byte( void );

/************************************************************/
/*!	
	\brief Scans and sends chars from a string until either
	a null termination is found or 80 chars are sent.

	\param pointer to a constant character string

	\todo Test

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/ 
void usart_send_pmstring(const char *); 


/************************************************************/
/*!	
	\brief Sets the stdlib printf output stream to the usart

	\param see the discussion in the avrlibc manual.

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
/// FILE mystdout = FDEV_SETUP_STREAM(usart_put_char, NULL, _FDEV_SETUP_WRITE);
// TODO: FIGURE OUT A BETTER WAY TO DOCUMENT THE ABOVE

/************************************************************/
/*!	
	\brief Used by the stdlib function printf to set the character
	output stream. Blocks until UDR is clear, then sends character.
	Converts '\n' to '\r'. For more information, see the discussion
	in the avrlibc manual.

	\param char c the character to be sent.
	\param FILE *stream used by printf to send characters to 
	the standard output.

	\todo Improve documentation.

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
int usart_put_char(char c, FILE *stream);

/************************************************************/
/*!	
	\brief Sets the fifo buffer used by the ISR
	FIFO buffer used: struct fifo_struct buffer;

	\param struct fifo_struct fifo Identified in fifo.h

	\todo Improve error handling

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
uint8_t usart_set_buffer(struct fifo_struct fifo);

//! usart errors
#define BUFFER_NULL_POINTER 0
#define BUFFER_SIZE 1
/************************************************************/
/*!	
	\brief Print the errors.

	\todo This is for the improved error handling which has
	not yet been implemented. 

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/ 
void usart_error(uint8_t error_num);

/************************************************************/
/*!	
	\brief Interrupt Service Routine for the USART0 receive vector.
	Loads a received byte into the fifo buffer.
	NOTE: since this is not a function it must be saved in a .c
	file with a function so that it can be compiled into an object
	module for inclusion in a library. Include this ISR with:
	void usart_init() in 
	TODO NAME THE FILE AND VERIFY HOW THIS WORKS.

	\todo Improve error handling

	\author Joe Pardue 
	\date 11/8/10
	\version 1.00
*/
/************************************************************/
///ISR(USART0_RX_vect)
// NOTE: THIS IS INCLUDE HERE FOR DOCUMENTATION



#endif 
//@}
