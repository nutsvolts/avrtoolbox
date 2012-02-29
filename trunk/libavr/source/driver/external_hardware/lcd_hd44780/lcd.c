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

// lcd_hd44780.c 
// Oct 21, 2011

#include "c:\avrtoolbox\libavr\source\general\util\util.h"
#include "lcd.h"

static void lcd_nibble( uint8_t d );

static void lcd_byte( uint8_t d );


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

// TODO - verify that lcd_pos is really needed in lcd_command
uint8_t lcd_pos = LCD_LINE1;

/*
const char line1[] PROGMEM =  "Line 1";
#ifdef LCD_LINE2
const char line2[] PROGMEM =  "Line 2";
#ifdef LCD_LINE3
const char line3[] PROGMEM =  "Line 3";
#ifdef LCD_LINE4
const char line4[] PROGMEM =  "Line 4";
#endif  
#endif  
#endif

const char pgm_str1[] PROGMEM =  "!Smiley!";
const char pgm_str2[] PROGMEM =  "!Micros!";
*/
/*
int main( void )
{
	lcd_init();

	lcd_puts("Hello!");
	delay(1000);
	lcd_clear();
	lcd_puts("REV002");
	delay(1000);

  lcd_set_cursor( 0, 0 );
  lcd_puts_p(line1 );
#ifdef LCD_LINE2
  lcd_set_cursor( 0, 1 );
  lcd_puts_p(line2 );
#ifdef LCD_LINE3
  lcd_set_cursor( 0, 2 );
  lcd_puts_p(line3);
#ifdef LCD_LINE4
  lcd_set_cursor( 0, 3 );
  lcd_puts_p(line4);
#endif  
#endif  
#endif 


  for(;;){

*//*   	lcd_set_cursor( 0, 0 );
	lcd_puts("Hello!5");
	delay(500);
	lcd_clear();
	delay(500);

	for(int i = 0x30 ; i < 0x038; i++)
	{
		lcd_putc(i);
	}
	delay(500);
*/

	/*
	// Test lcd_set_cursor, lcd_putc, and lcd_clear 
	// writes 0 to 7 in opposite directions in lines 1 and 2
	for(int i = 0x30 ; i < 0x038; i++)
	{
		lcd_set_cursor(7-(i-0x30),0);
		lcd_putc(i);
		lcd_set_cursor(i-0x30,1);
		lcd_putc(i);

		delay(500);	
	}
	lcd_clear();
	delay(500);
	*/

	
	/*// Test lcd_home
	// writes 0 to 7 in opposite directions in lines 1 and 2
	for(int i = 0x30 ; i < 0x038; i++)
	{
		lcd_home();
		lcd_putc(i);

		delay(500);	
	}
	lcd_clear();
	delay(500);
	*/

/*	// Test lcd_puts
	lcd_home();
	lcd_puts("*Smiley*");
	lcd_set_cursor(0,1);
	lcd_puts("*Micros*");
	delay(500);	
	lcd_clear();
	delay(500);
*/

/*	// Test lcd_puts_p and lcd_blank
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
*/	

/*	// Test lcd_cursor_on and lcd_cursor_off 
	// and lcd_blink_on and lcd_blink_off
	// and lcd_display_on and lcd_display_off
	lcd_putc('A');
	lcd_cursor_on();
	delay(500);
	lcd_putc('B');
	lcd_cursor_off();
	delay(500);
	lcd_blink_on();
	delay(500);
	lcd_blink_off();
	delay(500);
	lcd_display_off();
	delay(500);
	lcd_display_on();
	delay(500);
*/
/*	lcd_clear();
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

	



  }
}
*/


// Public functions
/*
lcd_init()
lcd_clear()
lcd_home()
lcd_set_cursor()
lcd_putc()
lcd_puts()
lcd_puts_p()
lcd_cursor_on()
lcd_cursor_off()
lcd_blink_on()
lcd_blink_off()
lcd_display_on()
lcd_display_off()

// omit
lcd_scroll_display_left()
lcd_scroll_display_right()
lcd_autoscroll_on()
lcd_autoscroll_off()
left_to_right()
lcd_right_To_left()
lcd_create_char()

*/

void lcd_init( void )
{

	// set LCD DDR pins to 1 for output
	LCD_D4_DDR |= (1<<LCD_D4_PIN);
	LCD_D5_DDR |= (1<<LCD_D5_PIN);
	LCD_D6_DDR |= (1<<LCD_D6_PIN);
	LCD_D7_DDR |= (1<<LCD_D7_PIN);
	LCD_E_DDR |= (1<<LCD_E_PIN);
	LCD_RS_DDR |= (1<<LCD_RS_PIN);


/*// set LCD DDR pins to 1 for output
	bit_set(LCD_D4_DDR,LCD_D4_PIN);
	bit_set(LCD_D5_DDR,LCD_D5_PIN);
	bit_set(LCD_D6_DDR,LCD_D6_PIN);
	bit_set(LCD_D7_DDR,LCD_D7_PIN);
	bit_set(LCD_E_DDR,LCD_E_PIN);
*/	bit_set(LCD_RS_DDR,LCD_RS_PIN);
/**/

// set the E and RS PORT pins to 0
	LCD_E_PORT &= ~(1<<LCD_E_PIN);
	LCD_RS_PORT &= ~(1<<LCD_RS_PIN);

/*
// set the E and RS PORT pins to 0
	bit_clear(LCD_E_PORT,LCD_E_PIN);
	bit_clear(LCD_RS_PORT,LCD_RS_PIN);*//**/

  _delay_ms( 15 );
  lcd_nibble( 0x30 );
  _delay_ms( 4.1 );
  lcd_nibble( 0x30 );
  _delay_us( 100 );
  lcd_nibble( 0x30 );
  _delay_us( LCD_TIME_DAT );
  lcd_nibble( 0x20 );                           // 4 bit mode
  _delay_us( LCD_TIME_DAT );
#if LCD_LINE == 1
  lcd_command( 0x20 );                          // 1 line
#else
  lcd_command( 0x28 );                          // 2 lines 5*7
#endif
  lcd_command( 0x08 );                          // display off
  lcd_command( 0x01 );                          // display clear
  lcd_command( 0x06 );                          // cursor increment
  lcd_command( 0x0C );                          // on, no cursor, no blink

  // Set initial display conditions
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF; 

 // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  lcd_command(LCD_ENTRYMODESET | _displaymode);


}

void lcd_clear()
{
	lcd_command(0x01);
}

void lcd_home()
{
	lcd_set_cursor(0,0);
}

void lcd_putc( uint8_t d )
{
  bit_set(LCD_RS_PORT,LCD_RS_PIN);

  lcd_byte( d );

  switch( ++lcd_pos ){
    case LCD_LINE1 + LCD_COLUMN:
#ifdef LCD_LINE2
      d = LCD_LINE2;
      break;
    case LCD_LINE2 + LCD_COLUMN:
#ifdef LCD_LINE3
      d = LCD_LINE3;
      break;
    case LCD_LINE3 + LCD_COLUMN:
#ifdef LCD_LINE4
      d = LCD_LINE4;
      break;
    case LCD_LINE4 + LCD_COLUMN:
#endif
#endif
#endif
      d = LCD_LINE1;
      break;
    default: 
      return;
  }
  lcd_command( d );
}


void lcd_puts(char *s )                        // display string from SRAM
{
  for( char *s1 = s; *s1; s1++ )             // until zero byte
    lcd_putc((uint8_t) *s1 );
}


void lcd_puts_p(const char *FlashString)
{
	uint8_t i = 0;
	// Check for '\0' string terminator or maximum LCD width
	while(pgm_read_byte(&FlashString[i]) && (i < LCD_COLUMN))
	{
		lcd_putc(pgm_read_byte(&FlashString[i++]));
	}
}

void lcd_blank( uint8_t len )                   // blank n digits
{
  while( len-- )
    lcd_putc( ' ' );
}

void lcd_cursor_on(void)
{
  _displaycontrol |= LCD_CURSORON;
  lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);   
}
void lcd_cursor_off(void)
{
  _displaycontrol &= ~LCD_CURSORON;
  lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcd_blink_on(void)
{
  _displaycontrol |= LCD_BLINKON;
  lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void lcd_blink_off(void)
{
  _displaycontrol &= ~LCD_BLINKON;
  lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);   

}
void lcd_display_on(void)
{
  _displaycontrol |= LCD_DISPLAYON;
  lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);

}
void lcd_display_off(void)
{
  _displaycontrol &= ~LCD_DISPLAYON;
  lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);   

}

// Private functions
static void lcd_nibble( uint8_t d )
{

	bit_clear(LCD_D7_PORT,LCD_D7_PIN);
	if( d & 1<<7 ) bit_set(LCD_D7_PORT,LCD_D7_PIN);
	bit_clear(LCD_D6_PORT,LCD_D6_PIN);
	if( d & 1<<6 ) bit_set(LCD_D6_PORT,LCD_D6_PIN);
	bit_clear(LCD_D5_PORT,LCD_D5_PIN);
	if( d & 1<<5 ) bit_set(LCD_D5_PORT,LCD_D5_PIN);
	bit_clear(LCD_D4_PORT,LCD_D4_PIN);
	if( d & 1<<4 ) bit_set(LCD_D4_PORT,LCD_D4_PIN);
	
	bit_set(LCD_E_PORT,LCD_E_PIN);
  	_delay_us( LCD_TIME_ENA );
	bit_clear(LCD_E_PORT,LCD_E_PIN);
}

static void lcd_byte( uint8_t d )
{
  lcd_nibble( d );
  lcd_nibble( d<<4 );
  _delay_us( LCD_TIME_DAT );
}

void lcd_command( uint8_t d )
{
  bit_clear(LCD_RS_PORT,LCD_RS_PIN);
  lcd_byte( d );
  switch( d ){
    case 0 ... 3:                       // on longer commands
      _delay_us( LCD_TIME_CLR );
      d = LCD_LINE1;
    case 0x80 ... 0xFF:                 // set position
      lcd_pos = d;
  }
}

