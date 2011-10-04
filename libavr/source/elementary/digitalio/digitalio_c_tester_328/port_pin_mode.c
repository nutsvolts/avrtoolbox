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

#include "C:\avrtoolbox\libavr\source\elementary\digitalio\digitalio.h"

int8_t port_pin_mode(uint8_t portx, uint8_t pin, uint8_t mode)
{
#if defined (__AVR_ATmega169__) || defined (__AVR_ATmega169P__)
	if (portx == porb) // it is PORTB
	{
		if ( mode == INPUT ) // set DDRB bit to 0
		{
			bit_clear(DDRB,pin);
		}
		else // ( mode == OUTPUT ) // set DDRB bit to 1
		{
			bit_set(DDRB,pin);
		}
	}
	else if (portx == portd) // it is PORTD
	{
		if ( mode == INPUT ) // set DDRD bit to 0
		{
			bit_clear(DDRD,pin);
		}
		else // ( mode == OUTPUT ) // set DDRD bit to 1
		{
			bit_set(DDRD,pin);
		}
	}
	else // out of range 
	{
		return(-1); // return ERROR
	}
	// TODO: remaining accessible Butterfly ports
#elif defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__) 
	if( portx == portd ) // matches bit for PORTD 
	{
		if ( mode == INPUT ) // set DDRD bit to 0
		{
			DDRD &= ~(1<<pin);
		}
		else // ( mode == OUTPUT ) // set DDRB bit to 1
		{
			DDRD |= (1<<pin);
		}
	}
	else if (portx == portb) // matches bit# for PORTB 0 thru 5
	{
		if ( mode == INPUT ) // set DDRD bit to 0
		{
			DDRB &= ~(1<<pin);
		}
		else // ( mode == OUTPUT ) // set DDRB bit to 1
		{
			DDRB |= (1<<pin);
		}
	}
	else if (portx == portc) // matches bit# for PORTC 0 thru 5
	{ // on the Arduino these are labeled analog 0 thru 5, but also work for digitalio
		if ( mode == INPUT ) // set DDRD bit to 0
		{
			DDRC &= ~(1<<pin);
		}
		else // ( mode == OUTPUT ) // set DDRB bit to 1
		{
			DDRC |= (1<<pin);
		}
	}
	else // out of range 
	{
		return(-1); // return ERROR
	}	
#else 
#    warning "device type not defined"
#endif
	return(1); // return OKAY

}
