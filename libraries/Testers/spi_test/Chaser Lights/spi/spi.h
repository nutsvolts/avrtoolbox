/*****************************************************
	spi.h Joe Pardue December 11, 2010
******************************************************/

/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2010, Joe Pardue, All rights reserved.
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
 *  - Neither the name of the Joe Pardue nor the names of its contributors
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

#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include "..\device\device.h" // defines device		

/* ********************************************************** */
/*!	

	\image html AVR_Toolbox.gif
	<center>Visit us at: http://www.smileymicros.com </center>

	\mainpage SPI (Serial Peripheral Interface) Functions Library
	
	\brief This is for single master only hardware SPI for either
	8 or 16-bit read-write.  

	There are three SPI functions that you will normally use:\n
	void spi_init_master(void);\n
	uint8_t spi_master_rw8(uint8_t to_slave);\n
	uint16_t spi_master_rw16(uint16_t to_slave);\n

	The user is reminded that SPI reads and writes in the same 
	operation, for example 8-bits are clocked out to the slave while
	8-bits are clocked in from the slave. For the spi_master_rw8
	function an 8-bit byte is taken as a parameter to send to the 
	slave and a byte is returned from the slave. The _rw16 function
	sends and receives 16-bits.

	This code was tested on the ATmega169 (AVR Butterfly, ATmega328
	(Arduino), and ATmega644 (BeAVR)(TODO)

	\todo test it for the ATmega644

	\author Joe Pardue 
	\license New BSD
	\date December 11, 2010
	\version 1.00

*/

/* ********************************************************** */
/*!	
	\brief Initializes spi as master.

	\note Remember that AVR SPI does not automatically assign
	or use the SS pin in the master mode. This must be intiailized
	and then set or cleared for each operation
*/
/* ********************************************************** */
void spi_init_master(void);


/* ********************************************************** */
/*!	
	\brief Writes and reads an 8-bit byte via SPI.

	\param to_slave 8-bit byte to send to slave

	\return 8-bit byte from slave
*/
/* ********************************************************** */
uint8_t spi_master_rw8(uint8_t to_slave);


/* ********************************************************** */
/*!	
	\brief Writes and reads a 16-bit word via SPI.

	\param to_slave 16-bit word to send to slave

	\return 16-bit word from slave

*/
/* ********************************************************** */
uint16_t spi_master_rw16(uint16_t to_slave);

/************************************************************/
/*!	
	\note Setup the SPI hardware pins. 

	MOSI_HARDWARE_PIN - Defines the MOSI port and pin number
	MOSI_HARDWARE_DDR - Defines the MOSI Data Direction Register

	MISO_HARDWARE_PIN - Defines the MISI port and pin number
	MISO_HARDWARE_DDR - Defines the MISI Data Direction Register

	SCLK_HARDWARE_PIN - Defines the SCLK port and pin number
	SCLK_HARDWARE_DDR - Defines the SCLK Data Direction Register

	SS_HARDWARE_PORT - Defines the SCLK port
	SS_HARDWARE_PIN - Defines the SCLK port and pin number
	SS_HARDWARE_DDR - Defines the SS Data Direction Register
*/
/************************************************************/

#if defined (Butterfly)
#define MOSI_HARDWARE_PIN PORTB2
#define MOSI_HARDWARE_DDR DDB2
#define MISO_HARDWARE_PIN PORTB3
#define MISO_HARDWARE_DDR DDB3
#define SCLK_HARDWARE_PIN PORTB1
#define SCLK_HARDWARE_DDR DDB1
#define SS_HARDWARE_PORT PORTB
#define SS_HARDWARE_PIN PORTB0
#define SS_HARDWARE_DDR DDB0

#elif defined (Arduino) | (ATmega328)
#define MOSI_HARDWARE_PIN PORTB3
#define MOSI_HARDWARE_DDR DDB3
#define MISO_HARDWARE_PIN PORTB4
#define MISO_HARDWARE_DDR DDB4
#define SCLK_HARDWARE_PIN PORTB5
#define SCLK_HARDWARE_DDR DDB5
#define SS_HARDWARE_PORT PORTB
#define SS_HARDWARE_PIN PORTB2
#define SS_HARDWARE_DDR DDB2

#elif defined (BeAVR40) | (ATmega644)
#define MOSI_HARDWARE_PIN PB5
#define MOSI_HARDWARE_DDR DDB5
#define MISO_HARDWARE_PIN PB4
#define MISO_HARDWARE_DDR DDB4
#define SCLK_HARDWARE_PIN PB7
#define SCLK_HARDWARE_DDR DDB7
#define SS_HARDWARE_PIN PB6
#define SS_HARDWARE_DDR DDB6

#endif

/************************************************************/
/*!	
	\def spi_clear_ss()
	Defines a macro to clear the hardware slave select pin
	\def spi_set_ss()
	Defines a macro to set the hardware slave select pin
*/
/************************************************************/
#define spi_clear_ss() (SS_HARDWARE_PORT &= ~(1<<SS_HARDWARE_PIN))
#define spi_set_ss() (SS_HARDWARE_PORT |= (1<<SS_HARDWARE_PIN)) 


#endif // SPI_H
