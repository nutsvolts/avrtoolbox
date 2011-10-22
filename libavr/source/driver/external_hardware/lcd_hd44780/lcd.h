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

#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include "c:\avrtoolbox\libavr\source\general\util\bitwise.h"
#include <avr/pgmspace.h>
#include <util/delay.h>



// Define the specific ports and pins used for the LCD
#define LCD_D4_PORT PORTD
#define LCD_D4_DDR DDRD
#define LCD_D4_PIN PD5

#define LCD_D5_PORT PORTD
#define LCD_D5_DDR DDRD
#define LCD_D5_PIN PD4

#define LCD_D6_PORT PORTD
#define LCD_D6_DDR DDRD
#define LCD_D6_PIN PD3

#define LCD_D7_PORT PORTD
#define LCD_D7_DDR DDRD
#define LCD_D7_PIN PD2

#define LCD_E_PORT PORTB
#define LCD_E_DDR DDRB
#define LCD_E_PIN PB3

#define LCD_RS_PORT PORTB
#define LCD_RS_DDR DDRB
#define LCD_RS_PIN PB4





/***************************************************************************/
/*                       define the wanted LCD type:                       */
/***************************************************************************/
//#define LCD_1X8
//#define LCD_1X16
//#define LCD_1X20
//#define LCD_1X40
#define LCD_2X8       // some 1x16 are wired as 2x8
//#define LCD_2X12
//#define LCD_2X16
//#define LCD_2X20
//#define LCD_2X24
//#define LCD_2X40
//#define LCD_4X16
//#define LCD_4X20

/***************************************************************************/
/*                       define the LCD connections:                       */
/***************************************************************************/
/* LCDNAV PCB follows the Arduino pins
LCD RS pin to digital pin 12 - PB4
LCD Enable pin to digital pin 11 - PB3
LCD D4 pin to digital pin 5 - PD5
LCD D5 pin to digital pin 4 - PD4
LCD D6 pin to digital pin 3 - PD3
LCD D7 pin to digital pin 2 - PD2
*/






#ifdef LCD_1X8
#define LCD_COLUMN      8
#define LCD_LINE        1
#define LCD_LINE1       0x80
#endif

#ifdef LCD_1X16
#define LCD_COLUMN      16
#define LCD_LINE        1
#define LCD_LINE1       0x80
#endif

#ifdef LCD_1X20
#define LCD_COLUMN      20
#define LCD_LINE        1
#define LCD_LINE1       0x80
#endif

#ifdef LCD_1X40
#define LCD_COLUMN      40
#define LCD_LINE        1
#define LCD_LINE1       0x80
#endif

#ifdef LCD_2X8
#define LCD_COLUMN      8
#define LCD_LINE        2
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)
#endif

#ifdef LCD_2X12
#define LCD_COLUMN      12
#define LCD_LINE        2
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)
#endif

#ifdef LCD_2X16
#define LCD_COLUMN      16
#define LCD_LINE        2
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)
#endif

#ifdef LCD_2X20
#define LCD_COLUMN      20
#define LCD_LINE        2
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)
#endif

#ifdef LCD_2X24
#define LCD_COLUMN      24
#define LCD_LINE        2
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)
#endif

#ifdef LCD_2X40
#define LCD_COLUMN      40
#define LCD_LINE        2
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)
#endif

#ifdef LCD_4X16
#define LCD_COLUMN      16
#define LCD_LINE        4
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)
#define LCD_LINE3       (0x80 + 0x10)
#define LCD_LINE4       (0x80 + 0x50)
#endif

#ifdef LCD_4X20
#define LCD_COLUMN      20
#define LCD_LINE        4
#define LCD_LINE1       0x80
#define LCD_LINE2       (0x80 + 0x40)
#define LCD_LINE3       (0x80 + 0x14)
#define LCD_LINE4       (0x80 + 0x54)
#endif

#define	LCD_TIME_ENA    1.0             // 1µs
#define LCD_TIME_DAT    50.0            // 50µs
#define LCD_TIME_CLR    2000.0          // 2ms




#ifdef LCD_LINE4
#define lcd_set_cursor(x, y)    lcd_command((x) + ((y==3) ? LCD_LINE4 : \
                                           (y==2) ? LCD_LINE3 : \
                                           (y==1) ? LCD_LINE2 : LCD_LINE1 ))
#else
#ifdef LCD_LINE3
#define lcd_set_cursor(x, y)    lcd_command((x) + ((y==2) ? LCD_LINE3 : \
                                           (y==1) ? LCD_LINE2 : LCD_LINE1 ))
#else
#ifdef LCD_LINE2
#define lcd_set_cursor(x, y)    lcd_command((x) + ((y==1) ? LCD_LINE2 : LCD_LINE1 ))
#else
#define lcd_set_cursor(x, y)    lcd_command((x) + LCD_LINE1 )
#endif  
#endif  
#endif  

// Public
/*!
	\defgroup lcd LCD driver functions for hd44780 LCD display

	This code uses #defines for I/O pins specific to the LCDNAV PCB 
	which follows those used by the LiquidCrystal library for the Arduino:
	\li RS pin to digital pin 12 - PB4
	\li Enable pin to digital pin 11 - PB3
	\li D4 pin to digital pin 5 - PD5
	\li D5 pin to digital pin 4 - PD4
	\li D6 pin to digital pin 3 - PD3
	\li D7 pin to digital pin 2 - PD2
	

	If you want to use another I/O pin configuration you need to redo the #defines for the pins.

*/
/** 
	\ingroup lcd

	\brief Initialize the LCD
  
	\return nothing
	
*/
void lcd_init(void);

/** 
	\ingroup lcd

	\brief Clear the LCD display
  
	\return nothing
	
	Example:
	\code
	// Say hello and show revision
	lcd_puts("Hello!");
	delay(1000);
	lcd_clear();
	lcd_puts("REV001");
	\endcode
*/
void lcd_clear(void);



/** 
	\ingroup lcd

	\brief Set cursor to upper left corner of LCD
  
	\return nothing
	
	Example:
	\code
	lcd_clear();
	// Reveal the answer
	char answer[] = "LOVE YOU";
	lcd_puts("????????");
	delay(1000);
	lcd_home();
	for(int i = 0; i < 8; i++)
	{
		lcd_putc((uint8_t) answer[i]);
		delay(1000); 
	}
 	\endcode
*/
void lcd_home();

/** 
	\ingroup lcd

	\brief Puts a character in the next available location.
	Note that this will wrap to the next line.
  
	\return nothing
	
	Example:
	\code
	lcd_clear();
	// Reveal the answer
	char answer[] = "LOVE YOU";
	lcd_puts("????????");
	delay(1000);
	lcd_home();
	for(int i = 0; i < 8; i++)
	{
		lcd_putc((uint8_t) answer[i]);
		delay(1000); 
	}
 	\endcode
*/
void lcd_putc( uint8_t d );

/** 
	\ingroup lcd

	\brief Show a string on the display
	Note that this will wrap to the next line.
  
  	\param * point to a string
	\return nothing
	
	Example:
	\code
	// Say hello and show revision
	lcd_puts("Hello!");
	delay(1000);
	lcd_clear();
	lcd_puts("REV001");
	\endcode
*/
void lcd_puts(char *);


/*	// Test lcd_puts_p and lcd_blank
	lcd_home();
	lcd_puts_p(pgm_str1);
	lcd_set_cursor(0,1);
	lcd_puts_p(pgm_str2);
	delay(500);
	*/
/** 
	\ingroup lcd

	\brief Show a string stored in flash memory on the display
	Note since regular strings are stored in SRAM, this is often 
	a better choice than lcd_puts because the string is stored in flash.
  
  	\param * point to a PROGMEM string
	\return nothing
	
	Example:
	\code
	const char pgm_str1[] PROGMEM =  "!Smiley!";
	const char pgm_str2[] PROGMEM =  "!Micros!";

	// Show flash memory strings in lines 1 and 2
	lcd_home();
	lcd_puts_p(pgm_str1);
	lcd_set_cursor(0,1);
	lcd_puts_p(pgm_str2);
	delay(1000);
	\endcode
*/
void lcd_puts_p(const char *);

/** 
	\ingroup lcd

	\brief 
  
  	\param len the number of characters to blank
	\return nothing
	
	Example:
	\code
	\\ sequenually remove 4 char blocks.
 	lcd_home();
	lcd_puts_p(pgm_str1);
	lcd_set_cursor(0,1);
	lcd_puts_p(pgm_str2);
	delay(500);	
	//lcd_clear();
	lcd_blank(4);
	delay(500);
	lcd_blank(4);
	delay(500);
	lcd_blank(4);
	delay(500);
	lcd_blank(4);
	delay(500);
 	\endcode
*/
void lcd_blank( uint8_t len );// blank n digits

/** 
	\ingroup lcd

	\brief Turns the underline cursor on
  
	\return nothing
	
	Example:
	\code
 	lcd_cursor_on();
 	\endcode
*/
void lcd_cursor_on(void);

/** 
	\ingroup lcd

	\brief Turns the underline cursor off
  
	\return nothing
	
	Example:
	\code
 	lcd_cursor_off();
 	\endcode
*/
void lcd_cursor_off(void);

/** 
	\ingroup lcd

	\brief Causes the next available character space to blink
  
	\return nothing
	
	Example:
	\code
 	lcd_blink_on();
 	\endcode
*/
void lcd_blink_on(void);


/** 
	\ingroup lcd

	\brief Causes the next available character space to stop blinking
  
	\return nothing
	
	Example:
	\code
 	lcd_blink_off();
 	\endcode
*/
void lcd_blink_off(void);

/** 
	\ingroup lcd

	\brief Turns the display on
  
	\return nothing
	
	Example:
	\code
 	lcd_display_on();
 	\endcode
*/
void lcd_display_on(void);

/** 
	\ingroup lcd

	\brief Turns the display of
  
 	\return nothing
	
	Example:
	\code
 	lcd_display_of();
 	\endcode
*/
void lcd_display_off(void);


// Private
/*
static void lcd_nibble( uint8_t d );

static void lcd_byte( uint8_t d );
*/
void lcd_command( uint8_t d );

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

uint8_t _displayfunction;
uint8_t _displaycontrol;
uint8_t _displaymode;

#endif


