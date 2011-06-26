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
 

#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 
#include "c:\avrtoolbox\libavr\source\driver\spi\spi.h" 


//include to use delay function
#include "c:\avrtoolbox\libavr\source\general\util\util.h"



/*
int main(void)
{
	// Say hello
	usart0_init_baud(57600);

	printf("spi_c_328.c 001\n");
}
*/

/*****************************************************
	Defines
******************************************************/
// LED pattern function selection numbers
#define CYLONEYES1	0x00 // 0000 
#define CYLONEYES2	0x01 // 0001 
#define CYLONEYES3	0x02 // 0010 
#define CYLONEYES4	0x03 // 0011 
#define CYLONEYES5	0x04 // 0100
#define WALLEYES1	0x05 // 0101 
#define WALLEYES2	0x06 // 0110
#define SAWEYES1	0x07 // 0111
#define SAWEYES2	0x08 // 1000
#define ANTEYES1 	0x09 // 1001 
#define ANTEYES2	0x0A // 1010
#define VIBROEYES1 	0x0B // 1011 
#define VIBROEYES2 	0x0C // 1100
#define BLINKEYES   0x0D // 1101
#define RANDOMEYES 	0x0E // 1110
#define FULLMONTY	0x0F // 1111

// DIP switch masks
#define POLARITYMASK 	0x80	// 1000 0000
#define SELECTMASK 		0x0F	// 0000 1111
#define SPEEDMASK 		0x78	// 0111 0000

// macro to clear all bits except those 
// set to 1 in the mask
#define mask_bits(p,m) (p & m)

/*****************************************************
	Global variables
******************************************************/
uint8_t volatile polarity = 1;
uint8_t volatile sweep_speed = 0;   
uint8_t volatile sweep_pattern = 0;
uint16_t volatile dip_switch = 0;
/*****************************************************
	Constants in PROGMEM
******************************************************/
// identify() loads this and from device.h
// the device name and outputs to the UART
const char PROGRAM[] PROGMEM = "ChaserLights - ";
const char VERSION[] PROGMEM = "1.30 \r";

// ?TODO: WHY WON'T THIS GO IN DEVICES.H?
// Used by the main module to identify the device
#if defined(Arduino)
const char DEVICE_NAME[] PROGMEM = "Arduino ";
#elif defined (Butterfly)
const char DEVICE_NAME[] PROGMEM = "Butterfly ";
#elif defined (BeAVR40)
const char DEVICE_NAME[] PROGMEM = "BeAVR40 ";
#else
const char DEVICE_NAME[] PROGMEM = "DEVICE_NAME UNDEFINED";
#endif

/*****************************************************
	Function declarations
******************************************************/
void cylon_eyes1(void);
void cylon_eyes2(void);
void cylon_eyes3(void);
void cylon_eyes4(void);
void cylon_eyes5(void);
void wall_eyes1(void);
void wall_eyes2(void);
void saw_eyes1(void);
void saw_eyes2(void);
void ant_eyes1(void);
void ant_eyes2(void);
void vibro_eyes1(void);
void vibro_eyes2(void);
void blinkin_eyes(void);
void random_eyes(void);
void full_monty(void);
void error_eyes(void);

void cylon_eyes_init(void);

// Send out identifying info on UART
void identify(void);

// Control the LED pattern action
void sweep(uint16_t *, uint8_t);
void sweep_right(uint16_t *, uint8_t);
void sweep_left(uint16_t *, uint8_t);


void parse_dip_switch(void);


int main(void)
{	

	// Say hello
	usart0_init_baud(57600);

	printf("spi_c_328.c 001\n");

	spi0_init_master();

	dip_switch = 0xC0;// Set to medium speed cylon_eye1

	while(1)
	{
		// Set pattern, polarity, and speed		
		parse_dip_switch();
		
		// Pick an LED pattern to run once
		switch (sweep_pattern)
		{
			case CYLONEYES1:
				cylon_eyes1();
				break;
			case CYLONEYES2:
				cylon_eyes2();
				break;
			case CYLONEYES3:
				cylon_eyes3();
				break;
			case CYLONEYES4:
				cylon_eyes4();
				break;
			case CYLONEYES5:
				cylon_eyes5();
				break;
			case WALLEYES1:
				wall_eyes1();
				break;
			case WALLEYES2:
				wall_eyes2();
				break;
			case SAWEYES1:
				saw_eyes1();				
				break;
			case SAWEYES2:
				saw_eyes2();				
				break;
			case ANTEYES1:
				ant_eyes1();				
				break;
			case ANTEYES2:
				ant_eyes2();				
				break;
			case VIBROEYES1:
				vibro_eyes1();
				break;
			case VIBROEYES2:
				vibro_eyes2();
				break;
			case BLINKEYES:
				blinkin_eyes();
				break;			
			case RANDOMEYES:
				random_eyes();
				break;				
			case FULLMONTY:
				full_monty();
				break;			
			default:
				error_eyes();
				break;
		}// switch
	}// while(1)
}

/*****************************************************
	Get the DIP-switch settings for determining the
	LED pattern, polarity, and sweep speed. The following
	bit masks are used:

	// DIP switch masks
	POLARITYMASK 	0x80	// 1000 0000
	SPEEDMASK 		0x78	// 0111 0000
	SELECTMASK 		0x0F	// 0000 1111

	You can invert the LED patterns with the left most switch
	You select one of 8 speeds with the next three switchs.
	You select one of 16 sweep patterns with the right most
	4 switches.
******************************************************/
// We have a single '597 attached to an 8-bit DIP-switch
// the sweep runs the 16-bit SPI, so we have to extract
// the 8-bits belonging to the DIP-switch, but since the
// valid data is in the low 8-bits we get it with a
// simple cast.

void parse_dip_switch()
{
	uint8_t temp0, temp1, temp2;

	temp0 = temp1 = temp2 = (uint8_t) dip_switch;

	sweep_pattern = mask_bits(temp0,SELECTMASK);
	polarity = mask_bits(temp1,POLARITYMASK);
	sweep_speed = 10 + ((mask_bits(temp2,SPEEDMASK)>>4)*25);	
}

/*****************************************************
	Output the LED pattern to the two '595 ICs 
******************************************************/
void sweep(uint16_t ce[], uint8_t num)
{	
	sweep_right(ce, num);
	sweep_left(ce, num);
}

void sweep_right(uint16_t ce[], uint8_t num)
{
  	for (int j=0; j<=num-1; j++)
  	{	
		if(polarity) dip_switch = spi0_master_rw16(ce[j]);
		else dip_switch = spi0_master_rw16(~ce[j]);

  		// Wait a while
  		//_delay_ms(sweep_speed);	
  		delay(sweep_speed);	

  	}
}

// The back swing eliminates the two ends
void sweep_left(uint16_t ce[], uint8_t num)
{
  	for (int j=num-1; j>=0; j--)
  	{
		if(polarity) dip_switch = spi0_master_rw16(ce[j]);
		else dip_switch = spi0_master_rw16(~ce[j]);

  		// Wait a while
  		//_delay_ms(sweep_speed);
  		delay(sweep_speed);

  	}
}


/*****************************************************
	The LED sweep patterns

	Yes, I am fully aware that several of these patterns
	could be run more efficiently with for loops and 
	bit shift operators, but tables are used for all
	to keep things consistent.
******************************************************/

/*
To create a 16 LED Cylon Eye effect
output this array 0 to 15 then 15 to 0
0000 0000 0000 0001 == 0x0001
0000 0000 0000 0010 == 0x0002
0000 0000 0000 0100 == 0x0004
0000 0000 0000 1000 == 0x0008
0000 0000 0001 0000 == 0x0010
0000 0000 0010 0000 == 0x0020
0000 0000 0100 0000 == 0x0040
0000 0000 1000 0000 == 0x0080
0000 0001 0000 0000 == 0x0100
0000 0010 0000 0000 == 0x0200
0000 0100 0000 0000 == 0x0400
0000 1000 0000 0000 == 0x0800
0001 0000 0000 0000 == 0x1000
0010 0000 0000 0000 == 0x2000
0100 0000 0000 0000 == 0x4000
1000 0000 0000 0000 == 0x8000
*/
// ce1 has 16 elements
void cylon_eyes1()
{
	printf_P(PSTR("cylon_eyes.\r"));

	uint16_t ce1[] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };

	sweep(ce1, 16);	
}

/*
CylonEyes2
0000 0000 0000 0011 == 0x0003
0000 0000 0000 0110 == 0x0006
0000 0000 0000 1100 == 0x000C
0000 0000 0001 1000 == 0x0018
0000 0000 0011 0000 == 0x0030
0000 0000 0110 0000 == 0x0060
0000 0000 1100 0000 == 0x00C0
0000 0001 1000 0000 == 0x0180
0000 0011 0000 0000 == 0x0300
0000 0110 0000 0000 == 0x0600
0000 1100 0000 0000 == 0x0C00
0001 1000 0000 0000 == 0x1800
0011 0000 0000 0000 == 0x3000
0110 0000 0000 0000 == 0x6000
1100 0000 0000 0000 == 0xC000
*/
// ce2 has 15 elements

void cylon_eyes2()
{
	printf_P(PSTR("cylon_eyes2.\r"));
	//_delay_ms(1000);
	
	uint16_t ce2[] = { 0x0003, 0x0006, 0x000C, 0x0018, 0x0030, 0x0060, 0x00C0, 0x0180, 0x0300, 0x0600, 0x0C00, 0x1800, 0x3000, 0x6000, 0xC000 };
	sweep(ce2, 15);
}

/*
CylonEyes3
0000 0000 0000 0111 == 0x0007
0000 0000 0000 1110 == 0x000E
0000 0000 0001 1100 == 0x001C
0000 0000 0011 1000 == 0x0038
0000 0000 0111 0000 == 0x0700
0000 0000 1110 0000 == 0x0E00
0000 0001 1100 0000 == 0x01C0
0000 0011 1000 0000 == 0x0380
0000 0111 0000 0000 == 0x0700
0000 1110 0000 0000 == 0x0E00
0001 1100 0000 0000 == 0x1C00
0011 1000 0000 0000 == 0x3800
0111 0000 0000 0000 == 0x7000
1110 0000 0000 0000 == 0xE000
*/
// ce3 has 14 elements

void cylon_eyes3()
{
	printf_P(PSTR("cylon_eyes3.\r"));
	//_delay_ms(1000);
	
	uint16_t ce3[] = { 0x0007, 0x000E, 0x001C, 0x0038, 0x0070, 0x00E0, 0x01C0, 0x0380, 0x0700, 0x0E00, 0x1C00, 0x3800, 0x7000, 0xE000 };
	sweep(ce3, 13);
}

/*
CylonEyes4
0000 0000 0000 1111 == 0x000F
0000 0000 0001 1110 == 0x001E
0000 0000 0011 1100 == 0x002C
0000 0000 0111 1000 == 0x0078
0000 0000 1111 0000 == 0x00F0
0000 0001 1110 0000 == 0x01E0
0000 0011 1100 0000 == 0x02C0
0000 0111 1000 0000 == 0x0780
0000 1111 0000 0000 == 0x0F00
0001 1110 0000 0000 == 0x1E00
0011 1100 0000 0000 == 0x2C00
0111 1000 0000 0000 == 0x7800
1111 0000 0000 0000 == 0xF000
*/
// ce4 has 13 elements

void cylon_eyes4()
{
	printf_P(PSTR("cylon_eyes4.\r"));
	//_delay_ms(1000);
	
	uint16_t ce4[] = { 0x000F, 0x001E, 0x002C, 0x0078, 0x00F0, 0x01E0, 0x02C0, 0x0780, 0x0F00, 0x1E00, 0x2C00, 0x7800, 0xF000 };
	sweep(ce4, 14);
}

/*
CylonEyes5
0000 0000 0001 1111 == 0x001F
0000 0000 0011 1110 == 0x002E
0000 0000 0111 1100 == 0x007C
0000 0000 1111 1000 == 0x00F8
0000 0001 1111 0000 == 0x01F0
0000 0011 1110 0000 == 0x02E0
0000 0111 1100 0000 == 0x07C0
0000 1111 1000 0000 == 0x0F80
0001 1111 0000 0000 == 0x1F00
0011 1110 0000 0000 == 0x2E00
0111 1100 0000 0000 == 0x7C00
1111 1000 0000 0000 == 0xF800
*/
// ce5 has 12 elements

void cylon_eyes5()
{
	printf_P(PSTR("cylon_eyes4.\r"));
	//_delay_ms(1000);
	
	uint16_t ce5[] = { 0x001F, 0x002E, 0x007C, 0x00F8, 0x01F0, 0x02E0, 0x07C0, 0x0F80, 0x1F00, 0x2E00, 0x7C00, 0xF800 };
	sweep(ce5, 12);
}

/*
Walleyes1
0000 0001 1000 0000 == 0x0180
0000 0010 0100 0000 == 0x0240
0000 0100 0010 0000 == 0x0420
0000 1000 0001 0000 == 0x0810
0001 0000 0000 1000 == 0x1008
0010 0000 0000 0100 == 0x2004
0100 0000 0000 0010 == 0x4002
1000 0000 0000 0001 == 0x8001
*/
// we1 array has 8 elements

void wall_eyes1()
{
	printf_P(PSTR("wall_eyes1.\r"));
	//_delay_ms(1000);
	uint16_t we1[] = { 0x0180, 0x0240, 0x0420, 0x0810, 0x1008, 0x2004, 0x4002, 0x8001 };
	sweep(we1, 8);
}


/*
Walleyes2
0000 0001 1000 0000 == 0x0180
0000 0011 1100 0000 == 0x02C0
0000 0110 0110 0000 == 0x0660
0000 1100 0011 0000 == 0x0C20
0001 1000 0001 1000 == 0x1818
0011 0000 0000 1100 == 0x200C
0110 0000 0000 0110 == 0x6006
1100 0000 0000 0011 == 0xC002
1000 0000 0000 0001 == 0x8001
*/
// we2 array has 9 elements

void wall_eyes2()
{
	printf_P(PSTR("wall_eyes2.\r"));
	//_delay_ms(1000);
	uint16_t we2[] = { 0x0180, 0x02C0, 0x0660, 0x0C20, 0x1818, 0x200C, 0x6006, 0xC002, 0x8001 };
	sweep(we2, 9);
}

/*
SawEyes1
1001 0010 0100 1001 == 0x9249
0010 0100 1001 0010 == 0x2492
0100 1001 0010 0100 == 0x4924
1001 0010 0100 1001 == 0x9249
*/
// se1 array has 3 elements

void saw_eyes1()
{
	printf_P(PSTR("saw_eyes1.\r"));
	//_delay_ms(1000);

	uint16_t se1[] = { 0x9249, 0x2492, 0x4924, 0x9249, 0x2492, 0x4924 };
	sweep(se1, 3);
}


/*
SawEyes2
1101 1011 0110 1101 == 0xDB6D
1011 0110 1101 1011 == 0xB6DB
0110 1101 1011 0110 == 0x6DB6
*/
// se2 array has 3 elements

void saw_eyes2()
{
	printf_P(PSTR("saw_eyes2.\r"));
	//_delay_ms(1000);

	uint16_t se2[] = { 0xDB6D, 0xB6DB, 0x6DB6 };
	sweep(se2, 3);

}
/*
AntEyes1
1001 0010 0100 1001 == 0x9249
0010 0100 1001 0010 == 0x2492
0100 1001 0010 0100 == 0x4924
*/
// ae1 array has 3 elements

void ant_eyes1()
{
	printf_P(PSTR("ant_eyes1.\r"));
	//_delay_ms(1000);

	uint16_t ae1[] = { 0x9249, 0x2492, 0x4924 };//, 0x9249, 0x2492, 0x4924 };
	sweep_left(ae1, 3);
}

/*
AntEyes2
1001 0010 0100 1001 == 0x9249
0010 0100 1001 0010 == 0x2492
0100 1001 0010 0100 == 0x4924
*/
// ae2 array has 3 elements

void ant_eyes2()
{
	printf_P(PSTR("ant_eyes2.\r"));
	//_delay_ms(1000);

	uint16_t ae2[] = { 0x9249, 0x2492, 0x4924 };//, 0x9249, 0x2492, 0x4924 };
	sweep_right(ae2, 3);
}

/*
VibroEyes1
1010 1010 1010 1010 == 0xAAAA
0101 0101 0101 0101	== 0x5555
*/

void vibro_eyes1()
{
	printf_P(PSTR("vibro_eyes1.\r"));
	//_delay_ms(1000);

	uint16_t ve1[] = { 0xAAAA, 0x5555 };
	sweep(ve1, 2);
}
/*
VibroEyes2
1100 1100 1100 1100 == 0xCCCC
0011 0011 0011 0011 == 0x3333
*/

void vibro_eyes2()
{
	printf_P(PSTR("vibro_eyes2.\r"));
	//_delay_ms(1000);

	uint16_t ve2[] = { 0xCCCC, 0x3333 };
	sweep(ve2, 2);
}

/*
BlinkinEyes
0000 0000 0000 0000 == 0x0000
1111 1111 1111 1111 == 0xFFFF
*/
void blinkin_eyes()
{
	printf_P(PSTR("blinkin_eyes.\r"));
	//_delay_ms(1000);

	uint16_t be[] = { 0x0000, 0xFFFF };
	sweep(be, 2);

}


void random_eyes()
{
	printf_P(PSTR("random_eyes.\r"));

	uint16_t re[2];
	re[0] = rand();
	re[1] = rand();

	sweep(re, 2);
}

// let it all hang out
void full_monty()
{
	cylon_eyes1();
	cylon_eyes2();
	cylon_eyes3();
	cylon_eyes4();
	wall_eyes1();
	wall_eyes2();
	saw_eyes1();
	saw_eyes2();
	ant_eyes1();
	ant_eyes2();
	vibro_eyes1();
	vibro_eyes2();
	blinkin_eyes();
	random_eyes();
}

// no movement, just stares at you 
// an blinks till you fix the error
// you won't see this, but I saw it a lot during development
/*
ErrorEyes
00011 1100 0011 1100 == 0x3C3C
00000 0000 0000 0000 == 0x0000
*/
void error_eyes()
{
	printf_P(PSTR("error_eyes.\r"));
	//_delay_ms(1000);

	uint16_t ee[] = { 0x3C3C, 0x0000 };
	sweep(ee, 0);
}





