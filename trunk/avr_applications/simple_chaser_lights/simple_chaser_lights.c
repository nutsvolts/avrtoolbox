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
 // please contact me with details so that I may correct the situation. #include "digitalio.h"

//
//
// simple_chaser_lights
// Oct. 17, 2011
//

/* 5 bits for up to 32 patterns
00000	0 	right_sweep1 
00001	1	right_sweep2
00010	2	right_sweep3
00011	3	right_sweep4
00100 	4	left_sweep1
00101	5	left_sweep2
00110	6	left_sweep3
00111	7	left_sweep4
01000	8	right_stack		
01001	9	left_stack
01010	10	right_ant
01011	11	left_ant
01100	12	inout
01101	13	blinkin
01110	14	brownian
01111	15	random
10000	16 	cylon1 
10001	17	cylon2
10010	18	cylon3
10011	19	cylon4
10100	20	cylon_all
10101	21	tick_tock_1
10110	22	tick_tock_2
10111	23	tick_tock_3
11000	24	tick_tock_4		
11001	24	tick_tock_5
11010	26	tick_tock_6
11011	27	tick_tock_all
11100	28	hypno_fade_1
11101	29	hypno_fade_2
11110	30	hypno_fade_4
11111	31	show_all
*/

#include "c:\avrtoolbox\libavr\source\elementary\digitalio\digitalio.h"
#include "c:\avrtoolbox\libavr\source\general\util\bitwise.h"

// debug sends out serial messages - if not needed
// save a couple of kb memory by commenting it out 
// Memory with DEBUG 7336
// Memory without DEBUG 5152 
#define DEBUG

// PORT and PIN alias
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

// DIP switch masks
#define POLARITYMASK 	0x01	// 00000001
#define SPEEDMASK 	0x06	// 00000110
#define PATTERNMASK	0xF8	// 11111000

// multiplier for sweep delay
#define DELAY 50

// sweep function declarations
void chaser_error();
void chaser_right_sweep1();
void chaser_right_sweep2();
void chaser_right_sweep3();
void chaser_right_sweep4();
void chaser_left_sweep1();
void chaser_left_sweep2();
void chaser_left_sweep3();
void chaser_left_sweep4();
void chaser_right_stack();		
void chaser_left_stack();
void chaser_right_ant();
void chaser_left_ant();
void chaser_inout();
void chaser_blinkin();
void chaser_brownian();
void chaser_random();
void chaser_cylon1();
void chaser_cylon2();
void chaser_cylon3();
void chaser_cylon4();
void chaser_cylon_all();
void chaser_tick_tock1();
void chaser_tick_tock2();
void chaser_tick_tock3();
void chaser_tick_tock4();
void chaser_tick_tock5();
void chaser_tick_tock6();
void chaser_tick_tock_all();
void chaser_hypno_fade1();
void chaser_hypno_fade2();
void chaser_hypno_fade3();
void chaser_show_all();

// chaser utilities
uint8_t chaser_read_dip();
void chaser_setup();
void set_pattern(uint8_t pattern);
void rotate_WS41_right(uint8_t pattern, uint8_t n);
void rotate_WS41_left(uint8_t pattern, uint8_t n);
void stack_WS41_left(uint8_t pattern, uint8_t n);
void stack_WS41_right(uint8_t pattern, uint8_t n);
uint8_t bar8_left(uint8_t n);
void roll_right();
void roll_left();
void stack_right();
void stack_left();
void sweep_delay();
void roll_right();
void roll_left();
void tick_tock();
void hypno_fade(uint8_t delay);

// module variables
static uint8_t polarity;
static uint8_t speed;
static uint8_t pattern;

#include <string.h>

int main()
{

	const char *myString = "Hello, World!";

	#if defined(DEBUG)
	serial_begin(57600);
	serial_out("simple_chaser_lights 009\n");
	#endif

	uint8_t newvalue = 0;
	uint8_t oldvalue = 1;
	uint8_t pattern_num = 0;

	chaser_setup();

	while(1)
	{
		/* First thing to get working - retain in case needed for debugging
		// Show DIP pattern on LEDs
		port_pin_write(LED0_1_PORT,LED0_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN0));
		port_pin_write(LED0_1_PORT,LED1_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN1));
		port_pin_write(LED2_7_PORT,LED2_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN2));
		port_pin_write(LED2_7_PORT,LED3_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN3));
		port_pin_write(LED2_7_PORT,LED4_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN4));
		port_pin_write(LED2_7_PORT,LED5_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN5));
		port_pin_write(LED2_7_PORT,LED6_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN6));
		port_pin_write(LED2_7_PORT,LED7_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN7));
		*/

		// read the DIP switch
		newvalue = chaser_read_dip();
		
		
		if(newvalue != oldvalue) // has the DIP switch changed?
		{
			// extract the speed, polarity, and pattern number from the DIP switch
			speed = 1 + bit_get_mask_field8(newvalue, SPEEDMASK);// add 1 to speed since 0 makes no sense
			polarity = bit_get_mask_field8(newvalue, POLARITYMASK);
			pattern_num = bit_get_mask_field8(newvalue, PATTERNMASK);

			#if defined(DEBUG) // report DIP values
			serial_out("DIP 8-bits: %x\n", newvalue);	
			oldvalue = newvalue;
			serial_out("Speed = %x\n",speed);
			serial_out("Polarity = %x\n",polarity);
			serial_out("Pattern = %x\n",pattern_num);
			#endif
		}

		// run the pattern
		switch(pattern_num)
		{
			case(0): 
			{
				chaser_right_sweep1();
				break;
			}
			case(1):
			{
				chaser_right_sweep2();
				break;
			}
			case(2):
			{
				chaser_right_sweep3();
				break;
			}
			case(3):
			{
				chaser_right_sweep4();
				break;
			}
			case(4):
			{
				chaser_left_sweep1();
				break;
			}
			case(5):
			{
				chaser_left_sweep2();
				break;
			}
			case(6):
			{
				chaser_left_sweep3();
				break;
			}
			case(7):
			{
				chaser_left_sweep4();
				break;
			}
			case(8):
			{
				chaser_right_stack();
				break;
			}
			case(9):
			{
				chaser_left_stack();
				break;
			}
			case(10):
			{
				chaser_right_ant();
				break;
				}			
			case(11):
			{
				chaser_left_ant();
				break;
			}
			case(12):
			{
				chaser_inout();
				break;
			}
			case(13):
			{
				chaser_blinkin();
				break;
			}
			case(14):
			{
				chaser_brownian();
				break;
			}
			case(15):
			{
				chaser_random();
				break;
			}
			case(16): 
			{
				chaser_cylon1();
				break;
			}
			case(17):
			{
				chaser_cylon2();
				break;
			}
			case(18):
			{
				chaser_cylon3();
				break;
			}
			case(19):
			{
				chaser_cylon4();
				break;
			}
			case(20):
			{
				chaser_cylon_all();
				break;
			}
			case(21):
			{
				chaser_tick_tock1();
				break;
			}
			case(22):
			{
				chaser_tick_tock2();
				break;
			}
			case(23):
			{
				chaser_tick_tock3();
				break;
			}
			case(24):
			{
				chaser_tick_tock4();
				break;
			}
			case(25):
			{
				chaser_tick_tock5();
				break;
			}
			case(26):
			{
				chaser_tick_tock6();
				break;
			}
			case(27):
			{
				chaser_tick_tock_all();
				break;
			}
			case(28):
			{
				chaser_hypno_fade1();
				break;
			}
			case(29):
			{
				chaser_hypno_fade2();
				break;
			}
			case(30):
			{
				chaser_hypno_fade3();
				break;
			}
			case(31):
			{
				chaser_show_all();
				break;
			}
			default:
			{
				#if defined(DEBUG)
				serial_out("Invalid case number.\n");
				#endif
				chaser_error(); // get attention to error
				break;
			}
		}
	}
}




/*************************<>*************************/
// Sweep patterns

void chaser_error()
{
	set_pattern(0x0F);
	sweep_delay();
	set_pattern(0xF0);
	sweep_delay();
}

void chaser_right_sweep1()
{
	#if defined(DEBUG)
	serial_out("right_sweep1\n");
	#endif
	pattern = 0x80;
	roll_right();
}

void chaser_right_sweep2()
{
	#if defined(DEBUG)
	serial_out("right_sweep2\n");	
	#endif
	pattern = 0xC0;
	roll_right();
}

void chaser_right_sweep3()
{
	#if defined(DEBUG)
	serial_out("right_sweep3\n");	
	#endif
	pattern = 0xE0;
	roll_right();
}

void chaser_right_sweep4()
{
	#if defined(DEBUG)
	serial_out("right_sweep4\n");
	#endif
	pattern = 0xF0;
	roll_right();		
}
void chaser_left_sweep1()
{
	#if defined(DEBUG)
	serial_out("left_sweep1\n");
	#endif
	pattern = 0x01;
	roll_left();		
}
void chaser_left_sweep2()
{
	#if defined(DEBUG)
	serial_out("left_sweep2\n");	
	#endif
	pattern = 0x03;
	roll_left();		
}
void chaser_left_sweep3()
{
	#if defined(DEBUG)
	serial_out("left_sweep3\n");	
	#endif
	pattern = 0x07;
	roll_left();		
}

void chaser_left_sweep4()
{
	#if defined(DEBUG)
	serial_out("left_sweep4\n");	
	#endif
	pattern = 0x0F;
	roll_left();		
}
 
void chaser_right_stack()		
{
	#if defined(DEBUG)
	serial_out("right_stack\n");
	#endif
	stack_right();	
}

void chaser_left_stack()
{
	#if defined(DEBUG)
	serial_out("left_stack\n");	
	#endif
	stack_left();
}


void chaser_right_ant()
{
	#if defined(DEBUG)
	serial_out("right_ant\n");
	#endif
	pattern = 0b10001000;
	roll_right();	

}
void chaser_left_ant()
{
	#if defined(DEBUG)
	serial_out("left_ant\n");	
	#endif
	pattern = 0b10001000;
	roll_left();	

}

// I bet there is a clever algorithm for this...
void chaser_inout()
{
	#if defined(DEBUG)
	serial_out("inout\n");
	#endif
	if(polarity==0)
	{
		set_pattern(0b00011000);	
		sweep_delay();
		set_pattern(0b00100100);	
		sweep_delay();
		set_pattern(0b01000010);	
		sweep_delay();
		set_pattern(0b10000001);	
		sweep_delay();
		set_pattern(0b01000010);	
		sweep_delay();
		set_pattern(0b00100100);	
		sweep_delay();
	}
	else
	{
		set_pattern(~0b00011000);	
		sweep_delay();
		set_pattern(~0b00100100);	
		sweep_delay();
		set_pattern(~0b01000010);	
		sweep_delay();
		set_pattern((uint8_t)~0b10000001); // needed for signedness warning	
		sweep_delay();
		set_pattern(~0b01000010);	
		sweep_delay();
		set_pattern(~0b00100100);	
		sweep_delay();
	}
}

void chaser_blinkin()
{
	#if defined(DEBUG)
	serial_out("blinkin\n");	
	#endif
	set_pattern(0xFF);	
	sweep_delay();
	set_pattern(0x00);	
	sweep_delay();
}

volatile uint8_t brown = 0x08;

void chaser_brownian()
{
	#if defined(DEBUG)
	serial_out("brownian\n");	
	#endif

	if(rand()>(RAND_MAX/2)) brown = rotate_left8(brown);
	else brown = rotate_right8(brown);
	if(polarity)set_pattern(~brown);
	else set_pattern(brown);
	
	sweep_delay();
}

void chaser_random()
{
	#if defined(DEBUG)
	serial_out("random\n");
	#endif
	set_pattern((uint8_t)(rand()>>4));
	sweep_delay();
}

void chaser_cylon1()
{
	#if defined(DEBUG)
	serial_out("cylon1\n");
	#endif
	pattern = 0x01;
	roll_right();
	pattern = 0x80;
	roll_left();
}

void chaser_cylon2()
{
	#if defined(DEBUG)
	serial_out("cylon2\n");	
	#endif

	pattern = 0x81;
	if(polarity) pattern = ~pattern;
		
	rotate_WS41_right(pattern, 7);
	rotate_WS41_left(pattern, 7);
}

void chaser_cylon3()
{
	#if defined(DEBUG)
	serial_out("cylon3\n");	
	#endif

	pattern = 0xE0;
	if(polarity) pattern = ~pattern;
	rotate_WS41_right(pattern, 5);
	pattern = 0x07;
	if(polarity) pattern = ~pattern;
	rotate_WS41_left(pattern, 5);
}

void chaser_cylon4()
{
	#if defined(DEBUG)
	serial_out("cylon4\n");
	#endif
	pattern = 0xF0;
	if(polarity) pattern = ~pattern;
	rotate_WS41_right(pattern, 4);
	pattern = 0x0F;
	if(polarity) pattern = ~pattern;
	rotate_WS41_left(pattern, 4);
}

void chaser_cylon_all()
{
	chaser_cylon1();
	chaser_cylon2();
	chaser_cylon3();
	chaser_cylon4();
}

void chaser_tick_tock1()
{
	pattern = 0x10;	;
	if(polarity) pattern = ~pattern;
	rotate_WS41_right(pattern, 1);
	sweep_delay();
	pattern = 0x08;	;
	if(polarity) pattern = ~pattern;
	rotate_WS41_left(pattern, 1);
	sweep_delay();

}
void chaser_tick_tock2()
{
	pattern = 0x18;	
	tick_tock();
}
void chaser_tick_tock3()
{
	pattern = 0x38;	
	tick_tock();
}
void chaser_tick_tock4()
{
	pattern = 0x3C;	
	tick_tock();
}
void chaser_tick_tock5()
{
	pattern = 0x7C;	
	tick_tock();
}
void chaser_tick_tock6()
{
	pattern = 0x7E;	
	tick_tock();
}

void chaser_tick_tock_all()
{
	chaser_tick_tock1();
	chaser_tick_tock2();
	chaser_tick_tock3();
	chaser_tick_tock4();
	chaser_tick_tock5();
	chaser_tick_tock6();

}

void chaser_hypno_fade1()
{
	hypno_fade(100);
}
void chaser_hypno_fade2()
{
	hypno_fade(50);
}
void chaser_hypno_fade3()
{
	hypno_fade(10);
}


void chaser_show_all()
{
	chaser_error();
	chaser_right_sweep1();
	chaser_right_sweep2();
	chaser_right_sweep3();
	chaser_right_sweep4();
	chaser_left_sweep1();
	chaser_left_sweep2();
	chaser_left_sweep3();
	chaser_left_sweep4();
	chaser_right_stack();		
	chaser_left_stack();
	chaser_right_ant();
	chaser_left_ant();
	chaser_inout();
	chaser_blinkin();
	chaser_brownian();
	chaser_random();
	chaser_cylon1();
	chaser_cylon2();
	chaser_cylon3();
	chaser_cylon4();
	chaser_tick_tock1();
	chaser_tick_tock2();
	chaser_tick_tock3();
	chaser_tick_tock4();
	chaser_tick_tock5();
	chaser_tick_tock6();
	chaser_hypno_fade1();
	chaser_hypno_fade2();
	chaser_hypno_fade3();
	chaser_tick_tock_all();
}



/*************************<>*************************/
// Pattern utilities

void hypno_fade(uint8_t del)
{
	for(int i = 0; i < del; i++)
	{
		set_pattern(0xff);
		delay(i);
		set_pattern(0);
		delay(del-i);
	}

	for(int i = 0; i < del; i++)
	{
		set_pattern(0x00);
		delay(i);
		set_pattern(0xff);
		delay(del-i);
	}
}


void tick_tock()
{
	if(polarity) pattern = ~pattern;
	rotate_WS41_right(pattern, 1);
	sweep_delay();
	rotate_WS41_left(pattern, 1);
	sweep_delay();
}

void roll_right()
{
	if(polarity) pattern = ~pattern;
	rotate_WS41_right(pattern, 8);
}

void roll_left()
{
	if(polarity) pattern = ~pattern;		
	rotate_WS41_left(pattern, 8);
}

void stack_left()
{
	if(polarity) pattern = ~pattern;		
	stack_WS41_left(pattern, 8);
}

void stack_right()
{
	if(polarity) pattern = ~pattern;		
	stack_WS41_right(pattern, 8);
}


void sweep_delay()
{
	delay(speed*DELAY);
}


uint8_t chaser_read_dip()
{
	return((port_pin_read(DIP0_4_PORT,DIP_PIN0)) \
	+ (port_pin_read(DIP0_4_PORT,DIP_PIN1) << 1) \
	+ (port_pin_read(DIP0_4_PORT,DIP_PIN2) << 2) \
	+ (port_pin_read(DIP0_4_PORT,DIP_PIN3) << 3) \
	+ (port_pin_read(DIP0_4_PORT,DIP_PIN4) << 4) \
	+ (port_pin_read(DIP5_7_PORT,DIP_PIN5) << 5) \
	+ (port_pin_read(DIP5_7_PORT,DIP_PIN6) << 6) \
	+ (port_pin_read(DIP5_7_PORT,DIP_PIN7) << 7));
}

void chaser_setup()
{

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
}

void set_pattern(uint8_t pattern)
{
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
}

void rotate_WS41_right(uint8_t pattern,  uint8_t times)
{
	for(int i = 0 ; i < times ; i++)
	{	
		pattern = rotate_right8(pattern);	   
		set_pattern(pattern);
		sweep_delay();
	}
}

void rotate_WS41_left(uint8_t pattern, uint8_t times)
{

	for(int i = 0 ; i < times ; i++)
	{		   
		pattern = rotate_left8(pattern);
		set_pattern(pattern);
		sweep_delay();
	}
}

uint8_t bar8_left(uint8_t n)
{
	uint8_t pat = 0x80;

	if(n==0)return(0);

	for(int i = 1 ; i < n ; i++)
	{
		pat |= (pat >> 1);
	}
	return(pat);	
}

uint8_t bar8_right(uint8_t n)
{
	uint8_t pat = 0x01;

	if(n==0)return(0);

	for(int i = 1 ; i < n ; i++)
	{
		pat |= (pat << 1);
	}
	return(pat);	
}

void stack_WS41_left(uint8_t pattern, uint8_t n)
{
	for(int i = 8 ; i > 0 ; i--)
	{
		pattern = 0x01;
		for(int j = i ; j > 0 ; j--)
		{
			if(polarity==0) set_pattern(pattern | bar8_left((8-i)));
			else set_pattern( ~(pattern | bar8_left((8-i))));
			pattern = rotate_left8(pattern);
			sweep_delay();
		}
	}
}

void stack_WS41_right(uint8_t pattern, uint8_t n)
{
	for(int i = 8 ; i > 0 ; i--)
	{
		pattern = 0x80;
		for(int j = i ; j > 0 ; j--)
		{
			if(polarity==0) set_pattern(pattern | bar8_right((8-i)));
			else set_pattern(~(pattern | bar8_right((8-i))));
			pattern = rotate_right8(pattern);
			sweep_delay();
		}
	}
}
