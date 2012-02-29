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
// Many changes were made to fit it into the avrtoolbox format.

#ifndef NAV_H
#define NAV_H

// Define the specific ports and pins used for the 5-button navigator keypad
#define NAV_LFT_PORTX PORTD
#define NAV_LFT_DDR DDRD
#define NAV_LFT_PINX PIND
#define NAV_LFT_PIN PD6

#define NAV_UP_PORT PORTD
#define NAV_UP_DDR DDRD
#define NAV_UP_PINX PIND
#define NAV_UP_PIN PD7

#define NAV_CTR_PORT PORTB
#define NAV_CTR_DDR DDRB
#define NAV_CTR_PINX PINB
#define NAV_CTR_PIN PB0

#define NAV_DWN_PORT PORTB
#define NAV_DWN_DDR DDRB
#define NAV_DWN_PINX PINB
#define NAV_DWN_PIN PB1

#define NAV_RGT_PORT PORTB
#define NAV_RGT_DDR DDRB
#define NAV_RGT_PINX PINB
#define NAV_RGT_PIN PB2


// This gives us xxmS debounce
#define MAX_COUNT 20

// Define bit positions for each of the buttons
#define LFT 0
#define RGT 1
#define UP 2
#define DWN 3
#define CTR 4

/*
#define LFT_PORT
#define LFT_PIN
#define RGT_PORT
#define RGT_PIN
#define UP_PORT
#define UP_PIN
#define DWN_PORT
#define DWN_PIN 
#define CTR_PORT
#define CTR_PIN 
*/

volatile uint8_t nav_state;
volatile uint8_t lft_count;
volatile uint8_t rgt_count;
volatile uint8_t up_count;
volatile uint8_t dwn_count;
volatile uint8_t ctr_count;


void nav_timer_init(void);

/*!
	\defgroup nav Drivers for a 5-button navigator keypad

	This code uses #defines for I/O pins specific to the LCDNAV PCB 
·	\li LFT	Arduino Pin 6 (ATmega328 Pin PD6)
·	\li UP	Arduino Pin 7 (ATmega328 Pin PD7)
·	\li CTR	Arduino Pin 8 (ATmega328 Pin PB0)
·	\li DWN	Arduino Pin 9 (ATmega328 Pin PB1)
·	\li RGT Arduino Pin 10 (ATmega328 Pin PB2)

	

	If you want to use another I/O pin configuration you need to redo the #defines for the pins.

*/
/** 
	\ingroup nav

	\brief Initialize the nav button keypad
  
	\return nothing
	
*/
void nav_init(void);

/** 
	\ingroup nav

	\brief True if a nav button is available
  
	\return state of nav buttons, 0 if non available
	
*/
uint8_t nav_available();

/** 
	\ingroup nav

	\brief Gets the keys from nav_state in order of LSB to MSB until all keys are read. 
	This could be used to prioritize key presses since the LSB keys will be returned first
  
	\return LFT, RGT, UP, DWN, CTR, or 0 is no key is available
	
*/
uint8_t nav_get_key();

/* 
	\ingroup nav

	\brief Test for left key
  
	\return 1 if the button is pressed 0 otherwise
	
*/
#define nav_lft() !bit_get(NAV_LFT_PINX,NAV_LFT_PIN)

/* 
	\ingroup nav

	\brief Test for up key
  
	\return 1 if the button is pressed 0 otherwise
	
*/
#define nav_up() !bit_get(NAV_UP_PINX,NAV_UP_PIN)

/* 
	\ingroup nav

	\brief Test for center key
  
	\return 1 if the button is pressed 0 otherwise
	
*/
#define nav_ctr() !bit_get(NAV_CTR_PINX,NAV_CTR_PIN)

/* 
	\ingroup nav

	\brief Test for down key
  
	\return 1 if the button is pressed 0 otherwise
	
*/
#define nav_dwn() !bit_get(NAV_DWN_PINX,NAV_DWN_PIN)

/* 
	\ingroup nav

	\brief Test for right key
  
	\return 1 if the button is pressed 0 otherwise
	
*/
#define nav_rgt() !bit_get(NAV_RGT_PINX,NAV_RGT_PIN)

#endif


