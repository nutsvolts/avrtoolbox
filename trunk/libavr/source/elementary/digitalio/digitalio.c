#include "digitalio.h"

int main()
{
// Test functions from Workshop 39
/*
void pin_mode(uint8_t pin, uint8_t mode)
 -  Sets the specified pin to either input or output.

uint8_t digital_read(uint8_t pin)
 -  Reads the state of the indicated input pin

void digital_write(uint8_t pin, uint8_t value)
 -  Sets the state of the indicated output pin.
 */
/* 
Show the state of an 8-bit DIP switch on 8 LEDs
Passed August 1, 2011

	int newvalue = 0;
	int oldvalue = 0;

	pin_mode(2,OUTPUT);
	pin_mode(3,OUTPUT);
	pin_mode(4,OUTPUT);
	pin_mode(5,OUTPUT);
	pin_mode(6,OUTPUT);
	pin_mode(7,OUTPUT);
	pin_mode(8,OUTPUT);
	pin_mode(9,OUTPUT);
	
	pin_mode(10,INPUT);
	pin_mode(11,INPUT);
	pin_mode(12,INPUT);
	pin_mode(14,INPUT);
	pin_mode(15,INPUT);
	pin_mode(16,INPUT);
	pin_mode(17,INPUT);
	pin_mode(18,INPUT);

	// set the pullups
	digital_write(10,HIGH);
	digital_write(11,HIGH);
	digital_write(12,HIGH);
	digital_write(14,HIGH);
	digital_write(15,HIGH);
	digital_write(16,HIGH);
	digital_write(17,HIGH);
	digital_write(18,HIGH);

	serial_begin(57600);

	serial_out("Digitalio tester 037\n");//,0);

	while(1)
	{

		digital_write(2,digital_read(10));
		digital_write(3,digital_read(11));
		digital_write(4,digital_read(12));
		digital_write(5,digital_read(14));
		digital_write(6,digital_read(15));
		digital_write(7,digital_read(16));
		digital_write(8,digital_read(17));
		digital_write(9,digital_read(18));

		newvalue = (digital_read(10)) + (digital_read(11) << 1) + (digital_read(12) << 2) + (digital_read(14) << 3) + (digital_read(15) << 4) + (digital_read(16) << 5) + (digital_read(17) << 6) + (digital_read(18) << 7);
		if(newvalue != oldvalue)
		{
			serial_out("DIP 8-bits: %x\n", newvalue);	
			oldvalue = newvalue;
		}
	
	
	}
*/

// Test functions from Workshop 40
// Repeat Workshop 39 tests but using the alternate functions

	int newvalue = 0;
	int oldvalue = 0;

	port_pin_mode(PORTD,PD2,OUTPUT);
	port_pin_mode(PORTD,PD3,OUTPUT);
	port_pin_mode(PORTD,PD4,OUTPUT);
	port_pin_mode(PORTD,PD5,OUTPUT);
	port_pin_mode(PORTD,PD6,OUTPUT);
	port_pin_mode(PORTD,PD7,OUTPUT);
	port_pin_mode(PORTB,PB0,OUTPUT);
	port_pin_mode(PORTB,PB1,OUTPUT);
	
	port_pin_mode(PORTB,PB2,INPUT);
	port_pin_mode(PORTB,PB3,INPUT);
	port_pin_mode(PORTB,PB4,INPUT);
	port_pin_mode(PORTC,PC0,INPUT);
	port_pin_mode(PORTC,PC1,INPUT);
	port_pin_mode(PORTC,PC2,INPUT);
	port_pin_mode(PORTC,PC3,INPUT);
	port_pin_mode(PORTC,PC4,INPUT);

	// set the pullups
	port_pin_activate_pullup(PORTB,PB2);
	port_pin_activate_pullup(PORTB,PB3);
	port_pin_activate_pullup(PORTB,PB4);
	port_pin_activate_pullup(PORTC,PC0);
	port_pin_activate_pullup(PORTC,PC1);
	port_pin_activate_pullup(PORTC,PC2);
	port_pin_activate_pullup(PORTC,PC3);
	port_pin_activate_pullup(PORTC,PC4);

	serial_begin(57600);

	serial_out("Digitalio tester 037\n");//,0);

	while(1)
	{
		port_pin_write(port_pin_read(PORTB,PB2),PORTD,PD2);
		port_pin_write(port_pin_read(PORTB,PB3),PORTD,PD3);
		port_pin_write(port_pin_read(PORTB,PB4),PORTD,PD4);
		port_pin_write(port_pin_read(PORTC,PC0),PORTD,PD5);
		port_pin_write(port_pin_read(PORTC,PC1),PORTD,PD6);
		port_pin_write(port_pin_read(PORTC,PC2),PORTD,PD7);
		port_pin_write(port_pin_read(PORTC,PC3),PORTB,PB0);
		port_pin_write(port_pin_read(PORTC,PC4),PORTB,PB1);

		newvalue = port_pin_read(PORTB,PB2) \
		+ (port_pin_read(PORTB,PB3) << 1) \
		+ (port_pin_read(PORTB,PB4) << 2) \
		+ (port_pin_read(PORTC,PC0) << 3) \
		+ (port_pin_read(PORTC,PC1) << 4) \
		+ (port_pin_read(PORTC,PC2) << 5) \
		+ (port_pin_read(PORTC,PC3) << 6) \
		+ (port_pin_read(PORTC,PC4) << 7);
		
		if(newvalue != oldvalue)
		{
			serial_out("DIP 8-bits: %x\n", newvalue);	
			oldvalue = newvalue;
		}
		
	}
// Test all but toggle with Simple Chaser Lights

//Set port pin modes to input 8-bit DIP switch
//Activate pull-ups for inputs
//Set port pin modes to output to 8 LEDs

//Simple Cylon Pattern
//Get direction, polarity, and speed from DIP switch
//Follow pattern to set and clear bits


//Test toggle by showing DIP pattern on LED and toggling once per second



}

