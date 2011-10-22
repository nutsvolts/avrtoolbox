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

#ifndef SPI_H
#define SPI_H


#include <avr/io.h>



/*!	
	\note Set up SPI hardware pins. The actual port and pin numbers, shown here with x 
	are selected by device specific definitions.

	\def MOSI_HARDWARE_PIN
	Defines the MOSI port and pin number
	\def MOSI_HARDWARE_DDR
	Defines the MOSI Data Direction Register

	\def MISO_HARDWARE_PIN
	Defines the MISI port and pin number
	\def MISO_HARDWARE_DDR
	Defines the MISI Data Direction Register

	\def SCLK_HARDWARE_PIN
	Defines the SCLK port and pin number
	\def SCLK_HARDWARE_DDR
	Defines the SCLK Data Direction Register

	\def SS_HARDWARE_PORT
	Defines the SCLK port
	\def SS_HARDWARE_PIN
	Defines the SCLK port and pin number
	\def SS_HARDWARE_DDR
	Defines the SS Data Direction Register
*/
/************************************************************/
/*#if defined (DOXYGEN)
#define MOSI_HARDWARE_PIN PORTxx
#define MOSI_HARDWARE_DDR DDBx
#define MISO_HARDWARE_PIN PORTxx
#define MISO_HARDWARE_DDR DDxx
#define SCLK_HARDWARE_PIN PORTxx
#define SCLK_HARDWARE_DDR DDxx
#define SS_HARDWARE_PORT PORTx
#define SS_HARDWARE_PIN PORTxx
#define SS_HARDWARE_DDR DDBx

#else
*/

#if defined(__AVR_ATmega169__) // Assume Butterfly
#define MOSI_HARDWARE_PIN PORTB2
#define MOSI_HARDWARE_DDR DDB2
#define MISO_HARDWARE_PIN PORTB3
#define MISO_HARDWARE_DDR DDB3
#define SCLK_HARDWARE_PIN PORTB1
#define SCLK_HARDWARE_DDR DDB1
#define SS_HARDWARE_PORT PORTB
#define SS_HARDWARE_PIN PORTB0
#define SS_HARDWARE_DDR DDB0
#elif defined(__AVR_ATmega328P__) // Assume Arduino
#define MOSI_HARDWARE_PIN PORTB3
#define MOSI_HARDWARE_DDR DDB3
#define MISO_HARDWARE_PIN PORTB4
#define MISO_HARDWARE_DDR DDB4
#define SCLK_HARDWARE_PIN PORTB5
#define SCLK_HARDWARE_DDR DDB5
#define SS_HARDWARE_PORT PORTB
#define SS_HARDWARE_PIN PORTB2
#define SS_HARDWARE_DDR DDB2
#elif defined(__AVR_ATmega644__) // Assume BeAVR
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
	\def spi0_hard_clear_ss()
	Defines a macro to clear the hardware slave select pin
	\def spi0_hard_set_ss()
	Defines a macro to set the hardware slave select pin
*/
/************************************************************/
#define spi0_clear_ss() (SS_HARDWARE_PORT &= ~(1<<SS_HARDWARE_PIN))
#define spi0_set_ss() (SS_HARDWARE_PORT |= (1<<SS_HARDWARE_PIN)) 


/*!
	\defgroup spi SPI Drivers
	
	\brief DOXYGEN has a problem with the #if defined (etc...) statement so the #defines are not properly documented
	\todo figure out how to get the #if defined stuff to work with DOXYGEN in the spi.h file
*/
/* ********************************************************** */
/*!	
	\ingroup spi

	\brief Deselects then selects the slave for spi0. 

	\author Joe Pardue 
	\date 9/22/10
	\version 1.00
*/
/* ********************************************************** */
void spi0_ss(void);


/* ********************************************************** */
/*!	
	\ingroup spi

	\brief Writes and reads a 16-bit word via hardware SPI
	for spi0.

	\note Blocks waiting for send to complete

	\return 16-bit word from the slave device.

	\param to_slave - 16-bit word to send to the slave device.
	
*/
/* ********************************************************** */
uint16_t spi0_master_rw16(uint16_t to_slave);

/* ********************************************************** */
/*!	
	\ingroup spi

	\brief Writes and reads an 8-bit byte via hardware SPI
	for spi0.

	\note Blocks waiting for send to complete

	\return 8-bit byte from the slave device.

	\param to_slave - 8-bit byte to send to the slave device.

*/
/* ********************************************************** */
uint8_t spi0_master_rw8(uint8_t to_slave);

/* ********************************************************** */
/*!	
	\ingroup spi

	\brief Initializes the AVR hardware SPI for spi0
*/
/* ********************************************************** */
void spi0_init_master(void);





#endif // SPI_H




//#include <avr/io.h>
//#include "..\device\device.h" // defines device	

/************************************************************/
	
	\def DOXYGEN
	Doxygen has a problem with the #if statements when the
	required define is in another file, so we will add a 
	special section just for Doxygen. Remove the comment '//'
	to define DOXYGEN before running Doxygen. Make sure the
	'//' is back in place before compiling the code.

/************************************************************/
//#define DOXYGEN	
	
/*****************************************************
******************************************************
	TODO: EXPLAIN USING MULTIPLE SPI OF VARYING TYPES
*******************************************************
******************************************************/

/* ********************************************************** */
	
	\mainpage SPI (Serial Peripheral Interface)
	
	\brief This code was designed to allow the user to create
	multiple SPI links using either bit-banged software or regular
	AVR hardware SPI.

	The user first selects a SPI number from a list that can
	be expanded as needed:
	#define SPI0
	//#define SPI1
	//#define SPIx // place holder

	After selecting and SPI number, then the user selects either
	software or hardware for that number:
	//#define SPI0_SOFT
	#define SPI0_HARD

	The user accesses the following functions:
	void spi0_init_master(void);
	uint8_t spi0_master_rw8(uint8_t to_slave);
	uint16_t spi0_master_rw16(uint16_t to_slave);

	Which are alia's for the software or hardware version.

	This code was tested for SPI0 in both software and hardware
	modes on the ATmega169, ATmega328, and ATmega644 (TODO)

	\todo test it for the ATmega644

	\author Joe Pardue 
	\date 9/22/10
	\version 1.00

/* ********************************************************** */


/*****************************************************
	Define number of SPI 
******************************************************/
//#define SPI0
//#define SPI1
//#define SPIx // place holder

//#if defined (SPI0)
/*****************************************************
******************************************************
	SPI0
*******************************************************
******************************************************/

/*****************************************************
	Declare SPI0 function
******************************************************/
//void spi0_init_master(void);
//uint8_t spi0_master_rw8(uint8_t to_slave);
//uint16_t spi0_master_rw16(uint16_t to_slave);

/*****************************************************
	Define SPI0 type
******************************************************/
//#define SPI0_SOFT
//#define SPI0_HARD


//#if defined (SPI0_SOFT)
/*****************************************************
	Software SPI
******************************************************/
/*static void spi0_soft_init_master(void);
static uint8_t spi0_soft_master_rw8(uint8_t to_slave);
static uint16_t spi0_soft_master_rw16(uint16_t to_slave);
*/

/************************************************************/
/*!	
	\def MOSI_PORT
	Defines the MOSI port
	\def MOSI_PORT_PIN
	Defines the MOSI port and pin number
	\def MOSI_DDR
	Defines the MOSI Data Direction Register
	\def MOSI_PORT_PINS
	Defines the MOSI port pins register

	\def MISO_PORT
	Defines the MiSI port
	\def MISO_PORT_PIN
	Defines the MISI port and pin number
	\def MISO_DDR
	Defines the MISI Data Direction Register
	\def MISO_PORT_PINS
	Defines the MISI port pins register

	\def SCLK_PORT
	Defines the SCLK port
	\def SCLK_PORT_PIN
	Defines the SCLK port and pin number
	\def SCLK_DDR
	Defines the SCLK Data Direction Register

	\def SS_PORT
	Defines the SCLK port
	\def SS_PORT_PIN
	Defines the SCLK port and pin number
	\def SS_DDR
	Defines the SS Data Direction Register
*/
/************************************************************/
// Define ports, pins, and data direction registers for set up
/*#define MOSI_PORT PORTB
#define MOSI_PORT_PIN  PORTB3
#define MOSI_DDR  DDRB
#define MOSI_PORT_PINS PINB

#define MISO_PORT PORTB
#define MISO_PORT_PIN  PORTB4
#define MISO_DDR  DDRB
#define MISO_PORT_PINS PINB

#define SCLK_PORT PORTB
#define SCLK_PORT_PIN PORTB5
#define SCLK_DDR DDRB

#define SS_PORT PORTB
#define SS_PORT_PIN  PORTB2
#define SS_DDR  DDRB

*/
/************************************************************/
/*!	
	\brief Moved bitwise operations to macros to 
	help keep folks heads from exploding.

	\def spi_soft_clear_ss() SS_PORT &= ~(1<<SS_PORT_PIN)
	Defines a macro to clear the slave select pin.
	\def spi_soft_set_ss() SS_PORT |= (1<<SS_PORT_PIN) 
	Defines a macro to set the slave select pin.
	\def spi_soft_set_mosi_bit() MOSI_PORT |= (1<<MOSI_PORT_PIN)
	Defines a macro to set the MOSI bit for output
	\def spi_soft_clear_mosi_bit() MOSI_PORT &= ~(1<<MOSI_PORT_PIN)
	Defines a macro to clear the MOSI bit for output
	\def is_bit_set(myVar, i) (!!(myVar & (1 << i)))
	Defines a macro to return 1 if a bit is set or 0 if not
*/
/************************************************************/
// Move bitwise operations to macros to 
// help keep folks heads from exploding
/*#define spi_soft_clear_ss() SS_PORT &= ~(1<<SS_PORT_PIN)
#define spi_soft_set_ss() SS_PORT |= (1<<SS_PORT_PIN) 
#define spi_soft_set_mosi_bit() MOSI_PORT |= (1<<MOSI_PORT_PIN)
#define spi_soft_clear_mosi_bit() MOSI_PORT &= ~(1<<MOSI_PORT_PIN)
#define is_bit_set(myVar, i) (!!(myVar & (1 << i)))

// Return the data pin state
static uint8_t spi_soft_get_miso_bit(void);

// Return the data pin state
static uint8_t spi_soft_get_miso_pin(void);

// Turn the clock line 0 to 1
static void spi_soft_toggle_sclk(void);

// Initialize the SPI I/O pins
static void spi_soft_setup_pins(void);
*/

//#elif defined (SPI0_HARD)
/************************************************************/
/*!	
	\def spi0_hard_clear_ss()
	Defines a macro to clear the hardware slave select pin
	\def spi0_hard_set_ss()
	Defines a macro to set the hardware slave select pin
*/
/************************************************************/
//#define spi0_clear_ss() (SS_HARDWARE_PORT &= ~(1<<SS_HARDWARE_PIN))
//#define spi0_set_ss() (SS_HARDWARE_PORT |= (1<<SS_HARDWARE_PIN)) 

/*****************************************************
	Hardware SPI
******************************************************/
//void spi0_hard_init_master(void);
//uint8_t spi0_hard_master_rw8(uint8_t to_slave);
//uint16_t spi0_hard_master_rw16(uint16_t to_slave);
//void spi0_SS(void); // Deselects then selects slave





//#elif defined (SPI0_USI)
/*****************************************************
	USI SPI
******************************************************/

//#elif defined (SPI0_USART)
/*****************************************************
	USART SPI
******************************************************/

//#else
//   #error "no SPI0 type declared"
//#endif

//#endif // SPI_H
