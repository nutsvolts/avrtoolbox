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
 // please contact me with details so that I may correct the situation. #include "digitalio.h"

//
//
// digitlio_c_tester_328 tester 
// passed 10/3/11 JWP
//
//

#include "C:\avrtoolbox\libavr\source\elementary\digitalio\digitalio.h"

// NOTE: these two functions are specific to the hardware described in Workshop 41
// and thus does not warrent a library function all to itself. 
void rotate_WS41_right(uint8_t pattern, uint16_t delay, uint8_t times);
void rotate_WS41_left(uint8_t pattern, uint16_t delay, uint8_t times);

// It is difficult to keep track of which LED and DIP switch is associated 
// with which port and pin so start off with some descriptive aliaes
#define LED0_1_PORT portc
#define LED0_PIN PC4
#define LED1_PIN PC5


#define LED2_7_PORT portd 
#define LED2_PIN PD2 
#define LED3_PIN PD3
#define LED4_PIN PD4
#define LED5_PIN PD5
#define LED6_PIN PD6
#define LED7_PIN PD7

#define DIP0_4_PORT portb
#define DIP_PIN0 PB0
#define DIP_PIN1 PB1
#define DIP_PIN2 PB2
#define DIP_PIN3 PB3
#define DIP_PIN4 PB4

#define DIP5_7_PORT portc
#define DIP_PIN5 PC0
#define DIP_PIN6 PC1
#define DIP_PIN7 PC2

int main()
{

	serial_begin(57600);
	serial_out("Digitalio tester 077\n");

	uint8_t newvalue = 0;
	uint8_t oldvalue = 1;
	uint8_t temp = 0;

	// Set LED port pins to output
	port_pin_mode(LED0_1_PORT,LED0_PIN,OUTPUT);
	port_pin_mode(LED0_1_PORT,LED1_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED2_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED3_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED4_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED5_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED6_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED7_PIN,OUTPUT);

	// set the pullups for the DIP switch
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN0);
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN1);
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN2);
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN3);
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN4);
	port_pin_activate_pullup(DIP5_7_PORT,DIP_PIN5);
	port_pin_activate_pullup(DIP5_7_PORT,DIP_PIN6);
	port_pin_activate_pullup(DIP5_7_PORT,DIP_PIN7);	

	while(1)
	{
		port_pin_write(LED0_1_PORT,LED0_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN0));
		port_pin_write(LED0_1_PORT,LED1_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN1));
		port_pin_write(LED2_7_PORT,LED2_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN2));
		port_pin_write(LED2_7_PORT,LED3_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN3));
		port_pin_write(LED2_7_PORT,LED4_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN4));
		port_pin_write(LED2_7_PORT,LED5_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN5));
		port_pin_write(LED2_7_PORT,LED6_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN6));
		port_pin_write(LED2_7_PORT,LED7_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN7));

		newvalue = (port_pin_read(DIP0_4_PORT,DIP_PIN0)) \
			     + (port_pin_read(DIP0_4_PORT,DIP_PIN1) << 1) \
				 + (port_pin_read(DIP0_4_PORT,DIP_PIN2) << 2) \
				 + (port_pin_read(DIP0_4_PORT,DIP_PIN3) << 3) \
				 + (port_pin_read(DIP0_4_PORT,DIP_PIN4) << 4) \
				 + (port_pin_read(DIP5_7_PORT,DIP_PIN5) << 5) \
				 + (port_pin_read(DIP5_7_PORT,DIP_PIN6) << 6) \
				 + (port_pin_read(DIP5_7_PORT,DIP_PIN7) << 7);
		
		if(newvalue != oldvalue)
		{
			serial_out("DIP 8-bits: %x\n", newvalue);	
			oldvalue = newvalue;	
		}
		
		// Test the 8-bit rotate functions
		temp = newvalue;	
		rotate_WS41_right(temp, 100, 64);
		delay(2000);
		rotate_WS41_left(temp,100, 64);
		delay(2000);

/*		// test port_pin_toggle
		delay(1000);
		port_pin_toggle(LED0_1_PORT,LED0_PIN);
		port_pin_toggle(LED0_1_PORT,LED1_PIN);
		port_pin_toggle(LED2_7_PORT,LED2_PIN);
		port_pin_toggle(LED2_7_PORT,LED3_PIN);
		port_pin_toggle(LED2_7_PORT,LED4_PIN);
		port_pin_toggle(LED2_7_PORT,LED5_PIN);
		port_pin_toggle(LED2_7_PORT,LED6_PIN);
		port_pin_toggle(LED2_7_PORT,LED7_PIN);
		delay(1000);

		// test port_pin_set
		port_pin_set(LED0_1_PORT,LED0_PIN);
		port_pin_set(LED0_1_PORT,LED1_PIN);
		port_pin_set(LED2_7_PORT,LED2_PIN);
		port_pin_set(LED2_7_PORT,LED3_PIN);
		port_pin_set(LED2_7_PORT,LED4_PIN);
		port_pin_set(LED2_7_PORT,LED5_PIN);
		port_pin_set(LED2_7_PORT,LED6_PIN);
		port_pin_set(LED2_7_PORT,LED7_PIN);
		delay(1000);

		// test port_pin_clear
		port_pin_clear(LED0_1_PORT,LED0_PIN);
		port_pin_clear(LED0_1_PORT,LED1_PIN);
		port_pin_clear(LED2_7_PORT,LED2_PIN);
		port_pin_clear(LED2_7_PORT,LED3_PIN);
		port_pin_clear(LED2_7_PORT,LED4_PIN);
		port_pin_clear(LED2_7_PORT,LED5_PIN);
		port_pin_clear(LED2_7_PORT,LED6_PIN);
		port_pin_clear(LED2_7_PORT,LED7_PIN);
		delay(1000);
*/
	}
}

void rotate_WS41_right(uint8_t pattern, uint16_t del, uint8_t times)
{
		for(int i = 0 ; i < times ; i++)
		{		   
			pattern = rotate_right8(pattern);

			if(bit_is_set(pattern,0)) port_pin_write(LED0_1_PORT,LED0_PIN,1);
			else port_pin_write(LED0_1_PORT,LED0_PIN,0);
			if(bit_is_set(pattern,1)) port_pin_write(LED0_1_PORT,LED1_PIN,1);
			else port_pin_write(LED0_1_PORT,LED1_PIN,0);
			if(bit_is_set(pattern,2)) port_pin_write(LED2_7_PORT,LED2_PIN,1);
			else port_pin_write(LED2_7_PORT,LED2_PIN,0);
			if(bit_is_set(pattern,3)) port_pin_write(LED2_7_PORT,LED3_PIN,1);
			else port_pin_write(LED2_7_PORT,LED3_PIN,0);
			if(bit_is_set(pattern,4)) port_pin_write(LED2_7_PORT,LED4_PIN,1);
			else port_pin_write(LED2_7_PORT,LED4_PIN,0);
			if(bit_is_set(pattern,5)) port_pin_write(LED2_7_PORT,LED5_PIN,1);
			else port_pin_write(LED2_7_PORT,LED5_PIN,0);
			if(bit_is_set(pattern,6)) port_pin_write(LED2_7_PORT,LED6_PIN,1);
			else port_pin_write(LED2_7_PORT,LED6_PIN,0);
			if(bit_is_set(pattern,7)) port_pin_write(LED2_7_PORT,LED7_PIN,1);
			else port_pin_write(LED2_7_PORT,LED7_PIN,0);
			delay(del);
		}
}

void rotate_WS41_left(uint8_t pattern, uint16_t del, uint8_t times)
{

		for(int i = 0 ; i < times ; i++)
		{		   
			pattern = rotate_left8(pattern);

			if(bit_is_set(pattern,0)) port_pin_write(LED0_1_PORT,LED0_PIN,1);
			else port_pin_write(LED0_1_PORT,LED0_PIN,0);
			if(bit_is_set(pattern,1)) port_pin_write(LED0_1_PORT,LED1_PIN,1);
			else port_pin_write(LED0_1_PORT,LED1_PIN,0);
			if(bit_is_set(pattern,2)) port_pin_write(LED2_7_PORT,LED2_PIN,1);
			else port_pin_write(LED2_7_PORT,LED2_PIN,0);
			if(bit_is_set(pattern,3)) port_pin_write(LED2_7_PORT,LED3_PIN,1);
			else port_pin_write(LED2_7_PORT,LED3_PIN,0);
			if(bit_is_set(pattern,4)) port_pin_write(LED2_7_PORT,LED4_PIN,1);
			else port_pin_write(LED2_7_PORT,LED4_PIN,0);
			if(bit_is_set(pattern,5)) port_pin_write(LED2_7_PORT,LED5_PIN,1);
			else port_pin_write(LED2_7_PORT,LED5_PIN,0);
			if(bit_is_set(pattern,6)) port_pin_write(LED2_7_PORT,LED6_PIN,1);
			else port_pin_write(LED2_7_PORT,LED6_PIN,0);
			if(bit_is_set(pattern,7)) port_pin_write(LED2_7_PORT,LED7_PIN,1);
			else port_pin_write(LED2_7_PORT,LED7_PIN,0);
			delay(del);

		}
}







