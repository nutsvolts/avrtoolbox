#include "lcd.h"

uint8_t lcd_pos = LCD_LINE1;

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
