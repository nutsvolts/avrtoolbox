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


#ifndef DIGITALIO_H
#define DIGITALIO_H

#include <avr/io.h>

#include "c:\avrtoolbox\libavr\source\elementary\serial\serial.h"
//#include "c:\avrtoolbox\libavr\source\general\util\bitwise.h"


#define HIGH 1
#define LOW  0
#define ERROR -1

#define INPUT 0
#define OUTPUT 1

#define true 1
#define false 0 

#define porta 0
#define portb 1
#define portc 2
#define portd 3

// From Smiley's Workshop 39, 40, and 41 Nuts&Volts October, November, and December 2011

/*!
	\defgroup Elementary Digital I/O Functions
*/

/*! 
	\ingroup digitalio  

	\brief Sets the specified pin to either input or output.

	\param pin uint8_t number for a device specific predefined pin
	\param mode use the define INPUT or OUTPUT

	\return 1 if okay, -1 if error
	
	Example:
	\code
		pin_mode(9, OUTPUT);
	\endcode
*/
int8_t pin_mode(uint8_t pin, uint8_t mode);


/*! 
	\ingroup digitalio  

	\brief Reads the state of the indicated input pin.

	\param pin number for a device specific predefined pin

	\return HIGH, LOW, or ERROR (1, 0, or -1)
	
	Example:
	\code
	// wait until the monkey pushes the 
	// button then give him some candy
	while(digital_read(8) == HIGH); // wait forever for the button push	
	digital_write(9,HIGH); // open the candy door
	\endcode
*/
int8_t digital_read(uint8_t pin);


/*! 
	\ingroup digitalio  

	\brief Sets the state of the indicated output pin.

	\param pin number for a device specific predefined pin 
	\param value to set pin to either HIGH or LOW (1 or 0)

	\return 1 if okay, -1 if error
	
	Example:
	\code
	if(digital_read(8) == LOW) // did somebody trip the door sensor?
	{
		digital_write(7) = HIGH; // if so, turn on the lights
	}		
	\endcode
*/
int8_t digital_write(uint8_t pin, uint8_t value);

/*! 
	\ingroup digitalio  

	\todo redo doc for pin_read and pin_write

	\def pin_read(portx, pinx)
	Defines a function-like macro to read pin# from pinx
	pinx is defined in the io.h header
	
	Example:
	\code
	if ( pin < 8) // it is PORTB
	{
		pin_read(PINB,pin);
	}
	\endcode
*/
#define pin_read(portx, pin) (portx & (1<<pin))

/*! 
	\ingroup digitalio  
	\todo redo doc for pin_read and pin_write

	\def pin_write(portx, pinx, value)
	Defines a function-like macro to read pinx of portx
	portx and pinx are defined in the io.h header
	value is either 0 or 1.
	
	Example:
	\code
	if (pin_read(PINB,pin)) 
	{
		pin_write(PINB,pin,0);
	}
	\endcode
*/
#define pin_write(portx, pinx, value) value ? (portx |= (1<<pinx)) : (portx &= ~(1<<pinx))


/*! 
	\ingroup digitalio  

	\brief Set a port pin mode to input or output.

	\param portx The port as identified in io.h
	\param pin The pin number 0 to 7.
	\param mode either INPUT or OUTPUT

	\return 1 if okay, -1 if error
	
	Example:
	\code
	// Set PORTB pin 4 to output
	port_pin_mode(PORTB, 7, OUTPUT);
	\endcode
*/
int8_t port_pin_mode(uint8_t portx, uint8_t pin, uint8_t mode);



/*! 
	\ingroup digitalio  

	\brief Reads the state of a pin in a port.

	\param portx The port as identified in io.h
	\param pin The pin number 0 to 7.
	
	\return HIGH, LOW, or ERROR (1, 0, or -1)
	
	Example:
	\code
	// Get the pin state
	myPinState = port_pin_read(myPort, myPin);
	\endcode
*/
int8_t port_pin_read(uint8_t portx, uint8_t pin);


/*! 
	\ingroup digitalio  

	\brief Sets a pin in a port to 1.

	\param portx The port as identified in io.h
	\param pin The pin number 0 to 7.
	
	\return 1 if okay, -1 if error

	Example:
	\code
	// if myPin is clear, set  myOtherPin
	if (port_pin_read(myPort, myPin) ) port_pin_set(myPort, myOtherPin);
	\endcode
*/
int8_t port_pin_set(uint8_t portx, uint8_t pin);

/*! 
	\ingroup digitalio  

	\brief Clears a pin in a port to 0.

	\param portx The port as identified in io.h
	\param pin The pin number 0 to 7.
	
	\return 1 if okay, -1 if error

	Example:
	\code
	// if myPin is set, clear  myOtherPin
	if (port_pin_read(myPort, myPin) ) port_pin_set(myPort, myOtherPin);
	\endcode
*/
int8_t port_pin_clear(uint8_t portx, uint8_t pin);


/*! 
	\ingroup digitalio  

	\brief Writes O or 1 to pin in portx

	\param state 0 or 1
	\param portx The port as identified in io.h
	\param pin The pin number 0 to 7.
	
	\return 1 if okay, -1 if error

	Example:
	\code
	// set 'state' 0 or 1 to myPin on myPort
	port_pin_write(myState,myPort, myPin) 
	\endcode
*/
int8_t port_pin_write(uint8_t state, uint8_t portx, uint8_t pin);

/*! 
	\ingroup digitalio  

	\brief Activates the pull-up resistor for a pin in a port.
 
	\param portx The port as identified in io.h
	\param pin The pin number 0 to 7.

	\return Nothing
	Example:
	\code
	// Activate the pullup on PORTB pin 5
	port_pin_activate_pullup(PORTB, 5)
	\endcode
*/
int8_t port_pin_activate_pullup(uint8_t portx, uint8_t pin);

/*! 
	\ingroup digitalio  

	\brief Deactivates the pull-up resistor for a pin in a port.

	\param portx The port as identified in io.h
	\param pin The pin number 0 to 7.

	\return 1 if okay, -1 if error

	Example:
	\code
	// Deactivate the pullup on PORTB pin 5
	port_pin_deactivate_pullup(PORTB, 5)
	\endcode
*/
int8_t port_pin_deactivate_pullup(uint8_t portx, uint8_t pin);


/*! 
	\ingroup digitalio  

	\brief Toggles (if 0, sets to 1 – if 1 sets to 0)the state  of a pin in a port.
: 
	\param portx The port as identified in io.h
	\param pin The pin number 0 to 7.
	
	\return 1 if okay, -1 if error
	
	Example:
	\code
	// Force pin 5 to change state regardless of state
	port_pin_toggle(PORTB, 5)
	\endcode
*/
int8_t port_pin_toggle(uint8_t portx, uint8_t pin);


/*! 
	\ingroup digitalio  

	\brief Rotates an 8-bit pattern one bit to the right
	Courtesy of Cliff Lawson: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=872900#872900
 
	\param n the pattern to rotate
	
	\return rotated pattern
	
	Example:
	\code
	// Pattern 0xAA rotated right becomes 0x55
	myPattern = 0xAA;
	myPattern = rotate_right8(myPattern);
	\endcode
*/
static inline uint8_t rotate_right8(uint8_t n)
{
  uint8_t carry = 0;

  if (n & 1) {
    carry = 1;
  }
  n >>= 1;
  if (carry) {
    n |= 0x80;
  }
  return n;
}

/*! 
	\ingroup digitalio  

	\brief Rotates an 8-bit pattern one bit to the left
	Courtesy of Cliff Lawson: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=872900#872900

	\param n the pattern to rotate
	
	\return rotated pattern
	
	Example:
	\code
	// Pattern 0x55 rotated right becomes 0xAA
	myPattern = 0x55;
	myPattern = rotate_left8(myPattern);
	\endcode
*/
static inline uint8_t rotate_left8(uint8_t n) 
{
  uint8_t carry = 0;

  if (n & 0x80) {
    carry = 1;
  }
  n <<= 1;
  if (carry) {
    n |= 0x01;
  }
  return n;
}

/*! 
	\ingroup digitalio  

	\brief Rotates a 16-bit pattern one bit to the right
	Courtesy of Cliff Lawson: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=872900#872900

	\param n the pattern to rotate
	
	\return rotated pattern
	
	Example:
	\code
	// Pattern 0xAAAA rotated right becomes 0x5555
	myPattern = 0xAAAA;
	myPattern = rotate_right8(myPattern);
	\endcode
*/
static inline uint16_t rotate_right16(uint16_t n) 
{
  uint8_t carry = 0;

  if (n & 1) {
    carry = 1;
  }
  n >>= 1;
  if (carry) {
    n |= (uint16_t)0x8000;
  }
  return n;
}

/*! 
	\ingroup digitalio  

	\brief Rotates an 16-bit pattern one bit to the left
	Courtesy of Cliff Lawson: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=872900#872900

	\param n the pattern to rotate
	
	\return rotated pattern
	
	Example:
	\code
	// Pattern 0x5555 rotated left becomes 0xAAAA
	myPattern = 0x5555;
	myPattern = rotate_left16(myPattern);
	\endcode
*/
static inline uint16_t rotate_left16(uint16_t n) 
{
  uint8_t carry = 0;

  if (n & (uint16_t)0x8000) {
    carry = 1;
  }
  n <<= 1;
  if (carry) {
    n |= 0x01;
  }
  return n;
}

/*! 
	\ingroup digitalio  

	\brief Rotates an 32-bit pattern one bit to the right
	Courtesy of Cliff Lawson: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=872900#872900

	\param the pattern to rotate
	
	\return rotated pattern
	
	Example:
	\code
	// Pattern 0xAAAAAAAA rotated right becomes 0x55555555
	myPattern = 0xAAAAAAAA;
	myPattern = rotate_right32(myPattern);
	\endcode
*/
static inline uint32_t rotate_right32(uint32_t n) 
{
  uint8_t carry = 0;

  if (n & 1) {
    carry = 1;
  }
  n >>= 1;
  if (carry) {
    n |= (uint32_t)0x80000000;
  }
  return n;
}

/*! 
	\ingroup digitalio  

	\brief Rotates an 32-bit pattern one bit to the left
	Courtesy of Cliff Lawson: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=872900#872900

	\param n the pattern to rotate
	
	\return rotated pattern
	
	Example:
	\code
	// Pattern 0x55555555 rotated right becomes 0xAAAAAAAA
	myPattern = 0x55555555;
	myPattern = rotate_left32(myPattern);
	\endcode
*/
static inline uint16_t rotate_left32(uint32_t n) 
{
  uint8_t carry = 0;

  if (n & (uint32_t)0x80000000) {
    carry = 1;
  }
  n <<= 1;
  if (carry) {
    n |= 0x01;
  }
  return n;
}

#endif
