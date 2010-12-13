/*****************************************************
	SPI.c Joe Pardue December 11, 2010
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

#include "spi.h"

void spi_init_master(void)
{
	// Set pullups with output high
	PORTB |= (1<< MISO_HARDWARE_PIN) \
 			| (1<< MOSI_HARDWARE_PIN) \
 			| (1<< SCLK_HARDWARE_PIN) \
 			| (1<< SS_HARDWARE_PIN);

	//Set MOSI, SCK AND SS to outputs
	DDRB |= (1<< MOSI_HARDWARE_DDR) \
			| (1<< SCLK_HARDWARE_DDR) \
			| (1<< SS_HARDWARE_DDR);

	// Set Miso to input
	DDRB &= ~(1<< MISO_HARDWARE_DDR);

	// Enable SPI, Set as master, set clock to fosc/16
    SPCR = ( 1 << SPE ) | ( 1 << MSTR ) | ( 1 << SPR0 ); 
}


uint8_t spi_master_rw8(uint8_t to_slave)
{
	uint8_t from_slave;

	// select slave
	spi_set_ss();

	// Put byte in SPI data register
	SPDR = to_slave;	

	// Poll SPIF-flag until transfer complete				
	while(!(SPSR & (1<<SPIF)));					

	// Get the SPI data reg.
	from_slave = SPDR;	

	// deselect slave
	spi_clear_ss();
						
	//return it
	return from_slave;
							
}

uint16_t spi_master_rw16(uint16_t to_slave)
{
	uint8_t to_slave_low = (uint8_t) to_slave;
	uint8_t to_slave_high = (uint8_t) (to_slave >> 8);
	uint8_t from_slave_high = 0;
	uint8_t from_slave_low = 0;

	// select slave
	spi_set_ss();

	// Put byte in SPI data register
	SPDR = to_slave_high;	

	// Poll SPIF-flag until transfer complete				
	while(!(SPSR & (1<<SPIF)));

	// Get the SPI data reg.
	from_slave_low = SPDR;

	// Put byte in SPI data register
	SPDR = to_slave_low;	

	// Poll SPIF-flag until transfer complete				
	while(!(SPSR & (1<<SPIF)));

	// Get the SPI data reg.
	from_slave_high = SPDR;
		
	// deselect slave
	spi_clear_ss();

	return ( (uint16_t)(from_slave_high << 8) + (uint16_t)from_slave_low );						
}

