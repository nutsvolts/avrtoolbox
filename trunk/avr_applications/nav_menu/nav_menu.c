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

// nav_menu.c 
// Nov 28, 2011

#include <stdlib.h>


#include "c:\avrtoolbox\libavr\source\general\util\util.h"
#include "c:\avrtoolbox\libavr\source\driver\external_hardware\lcd_hd44780\lcd.h"
#include "c:\avrtoolbox\libavr\source\driver\external_hardware\nav_button\nav.h"


void get_top(uint8_t get);
void entr_txt();
void entr_num();
void view_txt();
void view_num();
void erse_txt();
void erse_num();


const char prog_name[] PROGMEM =  "nav_menu";
const char prog_version[] PROGMEM =  "rev 001";

const char entr_txt_txt[] PROGMEM =  "entr_txt";
const char entr_num_txt[] PROGMEM =  "entr_num";
const char view_txt_txt[] PROGMEM =  "view_txt";
const char view_num_txt[] PROGMEM =  "view_num";
const char erse_txt_txt[] PROGMEM =  "erse_txt";
const char erse_num_txt[] PROGMEM =  "erse_num";

#define MAX_TOP 5

int main( void )
{
	uint8_t key = 0;
	uint8_t top = 0;
	char num[10];

	lcd_init();
	nav_init();

  lcd_set_cursor( 0, 0 );
  lcd_puts_p(prog_name );
  lcd_set_cursor( 0, 1 );
  lcd_puts_p(prog_version );
  delay(2000);
  lcd_clear();

  for(;;)
  {
	if(nav_available())
	{
		key = nav_get_key();

		if(key == CTR)
		{
			get_top(top);
			/*lcd_home();
			lcd_blank(16);
			lcd_puts("CTR!");*/
		}

		if(key == LFT)
		{
			lcd_home();
			lcd_blank(16);
			lcd_puts("LFT!");
		}

		if(key == RGT)
		{
			lcd_home();
			lcd_blank(16);
			lcd_puts("RGT!");
		}

		if(key == UP)
		{
			if (top <= MAX_TOP) top++;
			/*lcd_home();
			lcd_blank(16);
			lcd_puts("UP!");*/
		}
		
		if(key == DWN)
		{
			if (top > 0) top--;
			/*lcd_home();
			lcd_blank(16);
			lcd_puts("DWN!");*/
		}


		delay(500); // give 'em a chance to get their fat fingers off the keys
  		lcd_set_cursor( 0, 1 );
  		lcd_puts(itoa(top,num,10) );
		//lcd_home();
		//lcd_blank(16);
	
	}
  }
}


void get_top(uint8_t get)
{
	switch (get)
	{
		case 0:
			entr_txt();
			break;
		case 1:
			entr_num();
			break;
		case 2:
			view_txt();
			break;
		case 3:
			view_num();
			break;
		case 4:
			erse_txt();
			break;
		case 5:
			erse_num();
			break;
		default:
			break;
	}
}

//Enter text
void entr_txt()
{
	lcd_clear();
	lcd_puts_p(entr_txt_txt);
}
//Enter number
void entr_num()
{
	lcd_clear();
	lcd_puts_p(entr_num_txt);
}
//View text
void view_txt()
{
	lcd_clear();
	lcd_puts_p(view_txt_txt);
}
//View number
void view_num()
{
	lcd_clear();
	lcd_puts_p(view_num_txt);
}
//Erase text 
void erse_txt()
{
	lcd_clear();
	lcd_puts_p(erse_txt_txt);
}
//Erase number
void erse_num()
{
	lcd_clear();
	lcd_puts_p(erse_num_txt);
}

