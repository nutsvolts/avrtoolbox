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

// nav_buttons.c 
// Oct 22, 2011

#include "c:\avrtoolbox\libavr\source\general\util\util.h"
#include "c:\avrtoolbox\libavr\source\driver\external_hardware\lcd_hd44780\lcd.h"
#include "c:\avrtoolbox\libavr\source\driver\external_hardware\nav_button\nav.h"


int main( void )
{
	uint8_t key = 0;

	lcd_init();
	nav_init();

	lcd_puts("NavButt");
	delay(500);
	lcd_clear();
	lcd_puts("REV028");
	delay(1000);
	lcd_clear();


  for(;;)
  {
	if(nav_available())
	{
		key = nav_get_key();

		if(key == CTR)
		{
			lcd_home();
			lcd_blank(16);
			lcd_puts("CTR!");
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
			lcd_home();
			lcd_blank(16);
			lcd_puts("UP!");
		}
		
		if(key == DWN)
		{
			lcd_home();
			lcd_blank(16);
			lcd_puts("DWN!");
		}

		delay(100);
		lcd_home();
		lcd_blank(16);
	
	}
  }
}
