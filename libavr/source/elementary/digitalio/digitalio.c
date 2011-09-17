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

	port_pin_mode(uint8_t PORTx, uint8_t pin, uint8_t mode)

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
// Test all but toggle with Simple Chaser Lights

//Set port pin modes to input 8-bit DIP switch
//Activate pull-ups for inputs
//Set port pin modes to output to 8 LEDs

//Simple Cylon Pattern
//Get direction, polarity, and speed from DIP switch
//Follow pattern to set and clear bits


//Test toggle by showing DIP pattern on LED and toggling once per second









/*

Test all but toggle with Simple Chaser Lights

Set port pin modes to input 8-bit DIP switch
Activate pull-ups for inputs
Set port pin modes to output to 8 LEDs

Simple Cylon Pattern
Get direction, polarity, and speed from DIP switch
Follow pattern to set and clear bits

Test toggle by showing DIP pattern on LED and toggling once per second


void port_pin_mode(uint8_t PORTx, uint8_t pin, uint8_t mode)
 - Set a port pin mode to input or output.

uint8_t port_pin_read(uint8_t PORTx, uint8_t pin)
 - Reads the state of a pin in a port.

void port_pin_set(uint8_t PORTx, uint8_t pin)
 - Sets a pin in a port to 1.

void port_pin_clear(uint8_t PORTx, uint8_t pin)
 - Clears a pin in a port to 0.

void port_pin_activate_pullup(uint8_t DDRx, uint8_t PORTx, uint8_t pin)
 - Activates the pull-up resistor for a pin in a port.

void port_pin_deactivate_pullup(uint8_t PORTx, uint8_t pin)
 - Deactivates the pull-up resistor for a pin in a port.

void port_pin_toggle(uint8_t PORTx, uint8_t pin)
 - Toggles (if 0, sets to 1 – if 1 sets to 0)the state  of a pin in a port.

*/

/*
pin_mode(): digitalio initialization function.
Description:  Sets the specified pin to either input or output.
Syntax:  void pin_mode(uint8_t pin, uint8_t mode)
Parameters: 
	pin: pin to set the mode for
mode: either INPUT or OUTPUT
Returns:   Nothing
Example:   pin_mode(9, OUTPUT);
*/

/*
digital_read() - digitalio input function.
Description:  Reads the state of the indicated input pin.
Syntax:  int digital_read(uint8_t pin)
Parameters:  
	pin: the number of the pin to read.
Returns:   HIGH, LOW, or ERROR
Example: 
// wait until the monkey pushes the 
// button then give him some candy
while(digital_read(8) == HIGH); // wait forever for the button push
digital_write(9,HIGH); // open the candy door
*/

/*
digital_write(): digitalio output function.
Description:  Sets the state of the indicated output pin.
Syntax:  void digital_write(uint8_t pin, uint8_t value)
Parameters:  
	pin: pin to set either HIGH or LOW
	value: HIGH or LOW
Returns:   Nothing
Example:   
if(digital_read(8) == LOW) // did somebody trip the door sensor?
{
	digital_write(7) = HIGH; // if so, turn on the lights
}
*/

/*
port_pin_mode()
Description: Set a port pin mode to input or output.
Syntax: port_pin_mode(uint8_t PORTx, uint8_t pin, uint8_t mode)
Parameters:  
	uint8_t PORTx: The port as identified in io.h
	uint8_t pin: The pin number 0 to 7.
	Uint8_t mode: either INPUT or OUTPUT
Returns: nothing
Example:
// Set PORTB pin 4 to output
port_pin_mode(PORTB, 7, OUTPUT);
*/

/*
port_pin_read()
Description: Reads the state of a pin in a port.
Syntax: port_pin_read(uint8_t PORTx, uint8_t pin)
Parameters:  
	uint8_t PORTx: The port as identified in io.h
	uint8_t pin: The pin number 0 to 7.
Returns: HIGH, LOW
Example:
// Get the pin state
myPinState = port_pin_read(myPort, myPin);
*/

/*
port_pin_set()
Description: Sets a pin in a port to 1.
Syntax: port_pin_set(uint8_t PORTx, uint8_t pin)
Parameters: 
	uint8_t PORTx: The port as identified in io.h
	uint8_t pin: The pin number 0 to 7.
Returns: Nothing
Example:
// if myPin is clear, set  myOtherPin
if (port_pin_read(myPort, myPin) ) port_pin_set(myPort, myOtherPin);
*/

/*
port_pin_clear()
Description: Clears a pin in a port to 0.
Syntax: port_pin_clear(uint8_t PORTx, uint8_t pin)
Parameters: 
	uint8_t PORTx: The port as identified in io.h
	uint8_t pin: The pin number 0 to 7.
Returns: Nothing
Example:
// if myPin is set, clear  myOtherPin
if (port_pin_read(myPort, myPin) ) port_pin_set(myPort, myOtherPin);
*/

/*
port_pin_activate_pullup()
Description: Activates the pull-up resistor for a pin in a port.
Syntax: port_pin_activate_pullup(uint8_t DDRx, uint8_t PORTx, uint8_t pin)
Parameters: 
	uint8_t PORTx: The port as identified in io.h
	uint8_t pin: The pin number 0 to 7.
Returns: Nothing
Example:
// Activate the pullup on PORTB pin 5
port_pin_activate_pullup(DDRB, PORTB, 5)
*/

/*
port_pin_deactivate_pullup()
Description: Deactivates the pull-up resistor for a pin in a port.
Syntax: port_pin_deactivate_pullup(uint8_t PORTx, uint8_t pin)
Parameters: 
	uint8_t PORTx: The port as identified in io.h
	uint8_t pin: The pin number 0 to 7.
Returns: Nothing
Example:
// Deactivate the pullup on PORTB pin 5
port_pin_deactivate_pullup(DDRB, PORTB, 5)
*/

/*
port_pin_toggle()
Description: Toggles (if 0, sets to 1 – if 1 sets to 0)the state  of a pin in a port.
Syntax: port_pin_toggle(uint8_t PORTx, uint8_t pin)
Parameters: 
	uint8_t PORTx: The port as identified in io.h
	uint8_t pin: The pin number 0 to 7.
Returns: Nothing
Example:
// Force pin 5 to change state regardless of state
port_pin_toggle(PORTB, 5)
*/


}

