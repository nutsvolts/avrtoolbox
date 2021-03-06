
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

#ifndef BITWISE_H
#define BITWISE_H

#include <inttypes.h>
/*!
	\defgroup bitwise Bitwise Macros
*/

/*! 
	\ingroup bitwise  

	\def bit(x)
	Creates a mask with the bit x set to 1

	Example:
	\code
	bit_get(p,m) ((p) & bit(m)) 
	\endcode
*/
#define bit(x)	(1 << (x))

/*! 
	\ingroup bitwise  

	\def bit_get(p,m)
	Gets bit m in p

	Example:
	\code
	if(bit_get(PORTB,pin)) printf("The pin is HIGH.\n");
	else printf("The pin is LOW\n");
	\endcode
*/
#define bit_get(p,m) ((p) & bit(m)) 

/*! 
	\ingroup bitwise  

	\def bit_set(p,m) 
	Sets bit m in p

	Example:
	\code
	// If the button is pressed turn on the LED
	if(bit_get(PORTC,BUTTON1)) bit_set(PORTB,LED1);
	\endcode
*/
#define bit_set(p,m) ((p) |= bit(m)) 

/*! 
	\ingroup bitwise  

	\def bit_clear(p,m)
	Clears bit m in p

	Example:
	\code
	// If the button is not pressed turn off the LED
	if(!bit_get(PORTC,BUTTON1)) bit_clear(PORTB,LED1);
	\endcode
*/
#define bit_clear(p,m) ((p) &= ~bit(m)) 

/*! 
	\ingroup bitwise  

	\def bit_flip(p,m) 
	Flips (inverts) bit m in p
	
	Example:
	\code
	// Flip the even pins on a port
	for(i = 0; i < 8; i += 2)
	{
		bit_flip(PORTB,i);
	}
	\endcode
*/
#define bit_flip(p,m) ((p) ^= bit(m)) 

/*! 
	\ingroup bitwise  

	\def bit_write(c,p,m) 
	Writes c (HIGH or LOW) to pin m of uint8_t p

	Example:
	\code
	// Set PORTB pin# to HIGH
	bit_write(HIGH,PORTB,pin);
	\endcode
*/
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m)) 

/*! 
	\ingroup bitwise  

	\def bit_isset(p, bit) bit_rget(p, bit)
	Returns 1 if the bit # in p is set, 0 otherwise
	
	NOTE: name changed from bit_is_set to bit_isset to prevent conflict with avr sfr_defs.h

	Example:
	\code
	// If PORTB pin# is HIGH, set corresponding bit on PORTC
	if(bit_is_set(PORTB,pin) bit_set(PORTC,pin);
	\endcode
*/
#define bit_isset(p, bit) bit_get(p, bit)

/*! 
	\ingroup bitwise  

	\def bit_isclear(p, bit)
	Returns 1 if the bit # in p is clear, 1 otherwise
	
	NOTE: name changed from bit_is_clear to bit_isclear to prevent conflict with avr sfr_defs.h

	Example:
	\code
	// If PORTB pin# is LOW, clear corresponding bit on PORTC
	if(bit_is_clear(PORTB,pin) bit_clear(PORTC,pin);

	\endcode
*/
#define bit_isclear(p, bit) (!bit_get(p, bit))


/*! 
	\ingroup bitwise 
	
	\def bit_rotate_right(a)
	Rotates each bit 'a' one bit to the right. If the LSB is 1 then the MSB becomes 1
	
	Example:
	\code
	// Show a lit LED moving to the right
	uint16_t x = 0x8000;
	for(int i = 0; i < 16; i++)
	{
		led_out(myLED,x);
		bit_rotate_right(x);
	}
	\endcode
*/
#define bit_rotate_right(a) a = ((a & 0x01)? ((a >> 1)| (1ULL << ((sizeof(a) * 8) - 1))) : (a >> 1)) 

/*! 
	\ingroup bitwise 
	
	\def bit_rotate_left(a)
	Rotates each bit 'a' one bit to the left. If the MSB is 1 then the LSB becomes 1
	
	Example:
	\code
	// Show a lit LED moving to the right
	uint16_t x = 0x0001;
	for(int i = 0; i < 16; i++)
	{
		led_out(myLED,x);
		bit_rotate_left(x);
	}
	\endcode
	
*/
#define bit_rotate_left(a) a = ( (a &  (  1ULL << ((sizeof(a) * 8) -1)))   ? ((a << 1) | 1) : (a << 1)) 


/*! 
	\ingroup bitwise 
	
	\def bit_get_mask_field8(byte, mask)
	This extracts the value of the mask field from the byte
	
	Example:
	\code
	#define PAUSEMASK	0x38	// 00111000
	
	myByte = read_dip(); // read a byte from my DIP switch
	myPause= bit_get_mask_field(myByte,PAUSEMASK); // extract the pause value
	
	pause_seconds(myPause) // pause for myPause (0 to 7) seconds
	
	\endcode
	
*/
/*#define bit_to_shift8(mask) ( \ 
    ((mask) & 0x01) ? 0 : ( \ 
    ((mask) & 0x02) ? 1 : ( \ 
    ((mask) & 0x04) ? 2 : ( \ 
    ((mask) & 0x08) ? 3 : ( \ 
    ((mask) & 0x10) ? 4 : ( \ 
    ((mask) & 0x20) ? 5 : ( \ 
    ((mask) & 0x40) ? 6 : 7 ))))))) 
*/
#define bit_to_shift8(mask) (((mask) & 0x01) ? 0 : (((mask) & 0x02) ? 1 : (((mask) & 0x04) ? 2 : (((mask) & 0x08) ? 3 : (((mask) & 0x10) ? 4 : (((mask) & 0x20) ? 5 : (((mask) & 0x40) ? 6 : 7 ))))))) 
#define bit_get_mask_field8(byte, mask) (((byte) & (mask))>>bit_to_shift8(mask))

/*#define bit_to_shift8(mask) ( \ 
    ((mask) & 0x01) ? 0 : ( \ 
    ((mask) & 0x02) ? 1 : ( \ 
    ((mask) & 0x04) ? 2 : ( \ 
    ((mask) & 0x08) ? 3 : ( \ 
    ((mask) & 0x10) ? 4 : ( \ 
    ((mask) & 0x20) ? 5 : ( \ 
    ((mask) & 0x40) ? 6 : ( \ 
    ((mask) & 0x80) ? 7 : 8 )))))))) 
*/
//#define bit_to_shift8(mask) (((mask) & 0x01) ? 0 : (((mask) & 0x02) ? 1 : (((mask) & 0x04) ? 2 : (((mask) & 0x08) ? 3 : (((mask) & 0x10) ? 4 : (((mask) & 0x20) ? 5 : (((mask) & 0x40) ? 6 : (((mask) & 0x80) ? 7 : 8 )))))))) 
//#define bit_get_mask_field8(byte, mask) (((byte) & (mask))>>bit_to_shift8(mask))




/*! 
	\ingroup bitwise 
	
	\def bit_hi_byte(x)
	This extracts the high byte in the int x
	
	Example:
	\code
	UART_BAUD_RATE_HIGH = bit_hi_byte(setting);
	\endcode
	
*/
#define bit_hi_byte(x)	((uint8_t)(((uint16_t)(x)) >> 8))

/*! 
	\ingroup bitwise 
	
	\def bit_lo_byte(x)
	This extracts the lo byte in the int x
	
	Example:
	\code
	UART_BAUD_RATE_LOW= bit_lo_byte(setting);	
	\endcode
	
*/
#define bit_lo_byte(x)	((uint8_t)((uint16_t)(x)))

#endif
