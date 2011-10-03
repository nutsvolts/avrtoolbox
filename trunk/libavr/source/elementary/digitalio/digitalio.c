#include "digitalio.h"

// It is difficult to keep track of which LED and DIP switch is associated 
// with which port and pin so start off with some descriptive aliaes
#define LED0_1_PORT portc
#define LED0_PIN PC4
#define LED1_PIN PC5


#define LED2_7_PORT portd 
#define LED2_PIN PD2 
#define LED3_PIN PD3
#define LED4_PIN PD4
#define LED5_PIN PD5
#define LED6_PIN PD6
#define LED7_PIN PD7

#define DIP0_4_PORT portb
#define DIP_PIN0 PB0
#define DIP_PIN1 PB1
#define DIP_PIN2 PB2
#define DIP_PIN3 PB3
#define DIP_PIN4 PB4

#define DIP5_7_PORT portc
#define DIP_PIN5 PC0
#define DIP_PIN6 PC1
#define DIP_PIN7 PC2

int main()
{

	serial_begin(57600);
	serial_out("Digitalio tester 073\n");

	int newvalue = 0;
	int oldvalue = 1;

	// Set LED port pins to output
	port_pin_mode(LED0_1_PORT,LED0_PIN,OUTPUT);
	port_pin_mode(LED0_1_PORT,LED1_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED2_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED3_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED4_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED5_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED6_PIN,OUTPUT);
	port_pin_mode(LED2_7_PORT,LED7_PIN,OUTPUT);

	// set the pullups for the DIP switch
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN0);
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN1);
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN2);
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN3);
	port_pin_activate_pullup(DIP0_4_PORT,DIP_PIN4);
	port_pin_activate_pullup(DIP5_7_PORT,DIP_PIN5);
	port_pin_activate_pullup(DIP5_7_PORT,DIP_PIN6);
	port_pin_activate_pullup(DIP5_7_PORT,DIP_PIN7);


	

	while(1)
	{
		port_pin_write(LED0_1_PORT,LED0_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN0));
		port_pin_write(LED0_1_PORT,LED1_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN1));
		port_pin_write(LED2_7_PORT,LED2_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN2));
		port_pin_write(LED2_7_PORT,LED3_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN3));
		port_pin_write(LED2_7_PORT,LED4_PIN,port_pin_read(DIP0_4_PORT,DIP_PIN4));
		port_pin_write(LED2_7_PORT,LED5_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN5));
		port_pin_write(LED2_7_PORT,LED6_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN6));
		port_pin_write(LED2_7_PORT,LED7_PIN,port_pin_read(DIP5_7_PORT,DIP_PIN7));

		newvalue = (port_pin_read(DIP0_4_PORT,DIP_PIN0)) \
			     + (port_pin_read(DIP0_4_PORT,DIP_PIN1) << 1) \
				 + (port_pin_read(DIP0_4_PORT,DIP_PIN2) << 2) \
				 + (port_pin_read(DIP0_4_PORT,DIP_PIN3) << 3) \
				 + (port_pin_read(DIP0_4_PORT,DIP_PIN4) << 4) \
				 + (port_pin_read(DIP5_7_PORT,DIP_PIN5) << 5) \
				 + (port_pin_read(DIP5_7_PORT,DIP_PIN6) << 6) \
				 + (port_pin_read(DIP5_7_PORT,DIP_PIN7) << 7);
		
		if(newvalue != oldvalue)
		{
			serial_out("DIP 8-bits: %x\n", newvalue);	
			oldvalue = newvalue;
		}
	}
}



