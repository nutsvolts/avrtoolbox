/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2011, Joe Pardue, All rights reserved.
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

// This software was liberally influenced by:
// [TUT][C] LCD Tutorial 1001 by Peter Dannegger
// http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=828978
// And by the LiquidCrystal library for the Arduino
// Many changes were made to fit it into the avrtoolbox format.

// nav.c 
// Oct 23, 2011

//#include "c:\avrtoolbox\libavr\source\general\util\util.h"
//#include "c:\avrtoolbox\libavr\source\driver\external_hardware\lcd_hd44780\lcd.h"

#include <avr\io.h>
#include "c:\avrtoolbox\libavr\source\general\util\bitwise.h"
#include "c:\avrtoolbox\libavr\source\elementary\digitalio\digitalio.h"

#include "nav.h"


void nav_init( void )
{
	nav_state = 0;
	lft_count = 0;
	rgt_count = 0;
	up_count = 0;
	dwn_count = 0;
	ctr_count = 0;
		
	// Clear DDR pin bit for input
	NAV_UP_DDR &= ~(1<<NAV_UP_PIN);
	NAV_CTR_DDR &= ~(1<<NAV_CTR_PIN);
	NAV_DWN_DDR &= ~(1<<NAV_DWN_PIN);
	NAV_RGT_DDR &= ~(1<<NAV_RGT_PIN);	

	nav_timer_init();
}

uint8_t nav_available()
{
	return (nav_state);
}

uint8_t nav_get_key()
{
		if( (nav_state & (1<<CTR)) ) 
		{
			bit_clear(nav_state,CTR); // clear the bit
			nav_state = 0;
			return(CTR);
		}
		else if( (nav_state & (1<<LFT)) )
		{
			bit_clear(nav_state,LFT); // clear the bit
			nav_state = 0;
			return(LFT);
		}
		else if( (nav_state & (1<<RGT)) )
		{
			bit_clear(nav_state,RGT); // clear the bit
			nav_state = 0;
			return(RGT);
		}
		else if( (nav_state & (1<<UP)) )
		{
			bit_clear(nav_state,UP); // clear the bit
			nav_state = 0;
			return(UP);
		}
		else if( (nav_state & (1<<DWN)) )
		{
			bit_clear(nav_state,DWN); // clear the bit
			nav_state = 0;
			return(DWN);
		}
		else return(0);
}

void nav_timer_init() {

	// Set PB5 to output DEBUG ONLY!
  	DDRB |= (1<<PB5);

  	// CTC mode
  	TCCR2A |= (1<<WGM11);
  
  	//Prescaler /1024 - 16MHz so 15625 FCPU ticks per counter tick
  	// 256 counter ticks is 4000000 FCPU ticks 250mS per overflow
  	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);

  	OCR2A = 0x4D;//78;
  
  	//Timer2 Output Compare Match for OCR2A Interrupt Enable  
  	TIMSK2 |= (1<<OCIE2A);

  	TIFR2 |= (1<<OCF2A);

  	sei();

}

//Timer2 Compare A interrupt vector handler
ISR(TIMER2_COMPA_vect) 
{
	if(nav_lft())
	{
	  	if( lft_count < MAX_COUNT ) lft_count++;
		else 
		{
			bit_set(nav_state,LFT);
			lft_count = 0;
		}
	}
	else // not pressed
	{
		if (lft_count > 0) lft_count--;
	}

	if(nav_rgt())
	{
	  	if( rgt_count < MAX_COUNT ) rgt_count++;
		else 
		{
			bit_set(nav_state,RGT);
			rgt_count = 0;
		}
	}
	else // not pressed
	{
		if (rgt_count > 0) rgt_count--;
	}
 
	if(nav_up())
	{
	  	if( up_count < MAX_COUNT ) up_count++;
		else 
		{
			bit_set(nav_state,UP);
			up_count = 0;
		}
	}
	else // not pressed
	{
		if (up_count > 0) up_count--;
	}
   
	if(nav_dwn())
	{
	  	if( dwn_count < MAX_COUNT ) dwn_count++;
		else 
		{
			bit_set(nav_state,DWN);
			dwn_count = 0;
		}
	}
	else // not pressed
	{
		if (dwn_count > 0) dwn_count--;
	} 
 
 	if(nav_ctr())
	{
	  	if( ctr_count < MAX_COUNT ) ctr_count++;
		else 
		{
			bit_set(nav_state,CTR);
			ctr_count = 0;
		}
	}
	else // not pressed
	{
		if (ctr_count > 0) ctr_count--;
	} 
}

