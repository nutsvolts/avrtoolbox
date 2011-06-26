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

#include "c:\avrtoolbox\libavr\source\driver\spi\spi.h"

uint16_t spi0_master_rw16(uint16_t to_slave)
{
	uint8_t to_slave_low = (uint8_t) to_slave;
	uint8_t to_slave_high = (uint8_t) (to_slave >> 8);
	uint8_t from_slave_high = 0;
	uint8_t from_slave_low = 0;

	// select slave
//	spi_hard_set_ss();

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
//	spi_hard_clear_ss();

	return ( (uint16_t)(from_slave_high << 8) + (uint16_t)from_slave_low );						
}

