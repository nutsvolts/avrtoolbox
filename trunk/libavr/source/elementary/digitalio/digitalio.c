#include "digitalio.h"

// It is difficult to keep track of which LED and DIP switch is associated 
// with which port and pin so start off with some descriptive aliaes
#define LED0_5_PORT PORTD 
#define LED0_PIN PD2 
#define LED1_PIN PD3
#define LED2_PIN PD4
#define LED3_PIN PD5
#define LED4_PIN PD6
#define LED5_PIN PD7

#define LED6_7_PORT PORTB
#define LED6_PIN PB0
#define LED7_PIN PB1

#define DIP0_2_PORT PORTB
#define DIP_PIN0 PB2
#define DIP_PIN1 PB3
#define DIP_PIN2 PB4

#define DIP3_7_PORT PORTC
#define DIP_PIN3 PC0
#define DIP_PIN4 PC1
#define DIP_PIN5 PC2
#define DIP_PIN6 PC3
#define DIP_PIN7 PC4

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

//Show the state of an 8-bit DIP switch on 8 LEDs
//Passed August 1, 2011

	int newvalue = 0;
	int oldvalue = 0;

/*	port_pin_mode(PORTD,PD2,OUTPUT);
	port_pin_mode(PORTD,PD3,OUTPUT);
	port_pin_mode(PORTD,PD4,OUTPUT);
	port_pin_mode(PORTD,PD5,OUTPUT);
	port_pin_mode(PORTD,PD6,OUTPUT);
	port_pin_mode(PORTD,PD7,OUTPUT);
	port_pin_mode(PORTB,PB0,OUTPUT);
	port_pin_mode(PORTB,PB1,OUTPUT);
*/

	port_pin_mode(LED0_5_PORT,LED0_PIN,OUTPUT);
	port_pin_mode(LED0_5_PORT,LED1_PIN,OUTPUT);
	port_pin_mode(LED0_5_PORT,LED2_PIN,OUTPUT);
	port_pin_mode(LED0_5_PORT,LED3_PIN,OUTPUT);
	port_pin_mode(LED0_5_PORT,LED4_PIN,OUTPUT);
	port_pin_mode(LED0_5_PORT,LED5_PIN,OUTPUT);
	port_pin_mode(LED6_7_PORT,LED6_PIN,OUTPUT);
	port_pin_mode(LED6_7_PORT,LED7_PIN,OUTPUT);



/*	port_pin_mode(PORTB,PB2,INPUT);
	port_pin_mode(PORTB,PB3,INPUT);
	port_pin_mode(PORTB,PB4,INPUT);
	port_pin_mode(PORTC,PC0,INPUT);
	port_pin_mode(PORTC,PC1,INPUT);
	port_pin_mode(PORTC,PC2,INPUT);
	port_pin_mode(PORTC,PC3,INPUT);
	port_pin_mode(PORTC,PC4,INPUT);
*/
/* 	port_pin_mode(DIP0_2_PORT,DIP_PIN0,INPUT);
	port_pin_mode(DIP0_2_PORT,DIP_PIN1,INPUT);
	port_pin_mode(DIP0_2_PORT,DIP_PIN2,INPUT);
*/
// SOMETHING IN THIS IS MESSING UP THE OUTPUT ON PORTB
/*	port_pin_mode(DIP3_7_PORT,DIP_PIN3,INPUT);
	port_pin_mode(DIP3_7_PORT,DIP_PIN4,INPUT);
	port_pin_mode(DIP3_7_PORT,DIP_PIN5,INPUT);
	port_pin_mode(DIP3_7_PORT,DIP_PIN6,INPUT);
	port_pin_mode(DIP3_7_PORT,DIP_PIN7,INPUT);
*/// BUT THIS IS PORTC - HOW IS PORTC MESSING UP THE OUTPUT ON PB0 AND PB1???
                                             
	// set the pullups
/**/	
	port_pin_activate_pullup(DIP0_2_PORT,DIP_PIN0);
	port_pin_activate_pullup(DIP0_2_PORT,DIP_PIN1);
	port_pin_activate_pullup(DIP0_2_PORT,DIP_PIN2);
	port_pin_activate_pullup(DIP3_7_PORT,DIP_PIN3);
	port_pin_activate_pullup(DIP3_7_PORT,DIP_PIN4);
	port_pin_activate_pullup(DIP3_7_PORT,DIP_PIN5);
	port_pin_activate_pullup(DIP3_7_PORT,DIP_PIN6);
	port_pin_activate_pullup(DIP3_7_PORT,DIP_PIN7);


	serial_begin(57600);

	serial_out("Digitalio tester 069\n");

// this tells me that the data direction isn't getting set properly
	//DDRB = 0x03;
	//PORTB = 0x03;
	//DDRD = 0xFC;
	//PORTD = 0xFC;
	//delay(5000);

	

	while(1)
	{


/*
		if(port_pin_read(PORTB,PB2)) digital_write(10,1); else digital_write(10,0);
		if(port_pin_read(PORTB,PB3)) digital_write(11,1); else digital_write(11,0);
		if(port_pin_read(PORTB,PB4)) digital_write(12,1); else digital_write(12,0);
		if(port_pin_read(PORTC,PC0)) digital_write(14,1); else digital_write(14,0);
		if(port_pin_read(PORTC,PC1)) digital_write(15,1); else digital_write(15,0);
		if(port_pin_read(PORTC,PC2)) digital_write(16,1); else digital_write(16,0);	
		if(port_pin_read(PORTC,PC3)) digital_write(17,1); else digital_write(17,0);
		if(port_pin_read(PORTC,PC4)) digital_write(18,1); else digital_write(18,0);
		


		digital_write(2,1);//digital_read(10));
		digital_write(3,1);//digital_read(11));
		digital_write(4,1);//digital_read(12));
		digital_write(5,1);//digital_read(14));
		digital_write(6,1);//digital_read(15));
		digital_write(7,1);//digital_read(16));
		digital_write(8,1);//digital_read(17));
		digital_write(9,1);//digital_read(18));
*/
/*
PORTB = 0x03;
PORTD = 0xFC;
delay(1000);
PORTB = 0;
PORTD = 0;
delay(1000);
	
*/


		port_pin_write(LED0_5_PORT,LED0_PIN,port_pin_read(DIP0_2_PORT,DIP_PIN0));
		port_pin_write(LED0_5_PORT,LED1_PIN,port_pin_read(DIP0_2_PORT,DIP_PIN1));
		port_pin_write(LED0_5_PORT,LED2_PIN,port_pin_read(DIP0_2_PORT,DIP_PIN2));
		port_pin_write(LED0_5_PORT,LED3_PIN,port_pin_read(DIP3_7_PORT,DIP_PIN3));
		port_pin_write(LED0_5_PORT,LED4_PIN,port_pin_read(DIP3_7_PORT,DIP_PIN4));
		port_pin_write(LED0_5_PORT,LED5_PIN,port_pin_read(DIP3_7_PORT,DIP_PIN5));
		port_pin_write(LED6_7_PORT,LED6_PIN,port_pin_read(DIP3_7_PORT,DIP_PIN6));
		port_pin_write(LED6_7_PORT,LED7_PIN,port_pin_read(DIP3_7_PORT,DIP_PIN7));

		newvalue = (port_pin_read(DIP0_2_PORT,DIP_PIN0)) \
			     + (port_pin_read(DIP0_2_PORT,DIP_PIN1) << 1) \
				 + (port_pin_read(DIP0_2_PORT,DIP_PIN2) << 2) \
				 + (port_pin_read(DIP3_7_PORT,DIP_PIN3) << 3) \
				 + (port_pin_read(DIP3_7_PORT,DIP_PIN4) << 4) \
				 + (port_pin_read(DIP3_7_PORT,DIP_PIN5) << 5) \
				 + (port_pin_read(DIP3_7_PORT,DIP_PIN6) << 6) \
				 + (port_pin_read(DIP3_7_PORT,DIP_PIN7) << 7);
		if(newvalue != oldvalue)
		{
			serial_out("DIP 8-bits: %x\n", newvalue);	
			oldvalue = newvalue;
		}

/**/
/*
		port_pin_write(PORTD,PD2,port_pin_read(PORTB,PB2));
		port_pin_write(PORTD,PD3,port_pin_read(PORTB,PB3));
		port_pin_write(PORTD,PD4,port_pin_read(PORTB,PB4));
		port_pin_write(PORTD,PD5,port_pin_read(PORTC,PC0));
		port_pin_write(PORTD,PD6,port_pin_read(PORTC,PC1));
		port_pin_write(PORTD,PD7,port_pin_read(PORTC,PC2));
		port_pin_write(PORTB,PB0,port_pin_read(PORTC,PC3));
		port_pin_write(PORTB,PB1,port_pin_read(PORTC,PC4));
//delay(1000);
		newvalue = (port_pin_read(PORTB,PB2)) \
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
*/
	
	}


// Test functions from Workshop 40
// Repeat Workshop 39 tests but using the alternate functions

/*	int newvalue = 0;
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
*//*	// set the pullups
	port_pin_activate_pullup(PORTB,PB2);
	port_pin_activate_pullup(PORTB,PB3);
	port_pin_activate_pullup(PORTB,PB4);
	port_pin_activate_pullup(PORTC,PC0);
	port_pin_activate_pullup(PORTC,PC1);
	port_pin_activate_pullup(PORTC,PC2);
	port_pin_activate_pullup(PORTC,PC3);
	port_pin_activate_pullup(PORTC,PC4);
*/
/*
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

	serial_out("Digitalio tester 047\n");//,0);

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
*/
// Test all but toggle with Simple Chaser Lights

//Set port pin modes to input 8-bit DIP switch
//Activate pull-ups for inputs
//Set port pin modes to output to 8 LEDs

//Simple Cylon Pattern
//Get direction, polarity, and speed from DIP switch
//Follow pattern to set and clear bits


//Test toggle by showing DIP pattern on LED and toggling once per second



}

