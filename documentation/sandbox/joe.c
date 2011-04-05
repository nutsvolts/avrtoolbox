joe.c

<!---
/* ********************************************************** */
	
Repository path:    $HeadURL$
Last committed:     $Revision$
Last changed by:    $Author$
Last changed date:    $Date$
ID:            $Id$

/* ********************************************************** */
--->

/* ********************************************************** */
/*!	
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

Location: avrtoolbox\Libraries\Peripheral\spi

	\todo test it for the ATmega644

	\author Joe Pardue 
	\license New BSD
	\date December 1, 2010
	\version <!--- $ID$ --->
*/
/* ********************************************************** */


