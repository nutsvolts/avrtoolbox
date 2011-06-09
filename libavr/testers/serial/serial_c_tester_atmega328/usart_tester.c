#/*
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
 
#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 


//include to use delay function
#include "c:\avrtoolbox\libavr\source\general\util\util.h"

int main(void)
{
	uint8_t count = 0;
	uint8_t str[64];

	#if defined(BUTTERFLY)
	butterfly_init();
	#endif

	// Test usart initialization with all parameters
/*	cli();

	// Modem parameters used by common serial connections
	usart_mode_t mode = usart_mode_asynchronous;
	uint8_t databits = 8;
	uint8_t stopbits = 1;
	usart_parity_t parity = parity_none;
	usart_flow_control_t flow_control = flow_none;

	usart0_init(57600, F_CPU, mode,  databits, stopbits, parity, flow_control);

	sei();
*/
	// Test usart initialization with defaults
	usart0_init_baud(57600);


	str[0] = 'H';
	str[1] = 'o';
	str[2] = 'w';
	str[3] = 'd';
	str[4] = 'y';
	str[5] = '1';
	str[6] = '5';
	str[7] = '\0';

	int i = 0;
	// Send until encountering string terminator
	while( (str[i] != '\0'))
	{
		usart0_transmit_buffer_insert(str[i++]);
		delay(100); // prevents choking background activity
	}


	while(1)
	{
		// Ping back received values
		if(usart0_receive_buffer_inuse_count())
		{
			count = usart0_receive_buffer_inuse_count();

			for(int i = 0 ; i < count; i++)
			{
				usart0_transmit_buffer_insert(usart0_receive_buffer_remove());
				delay(100);
			}
		}
	}







	// NOTE: If BUTTERFLY is defined then the serial_being() is bypassed
	// and the usart is set to 19200 regardless of what this says
//	serial_begin(57600);


/*
	buf[0] = 'H';
	buf[1] = 'o';
	buf[2] = 'w';
	buf[3] = 'd';
	buf[4] = 'y';
	buf[5] = 0;

//	serial_write(buf,6);
	// Insert a delay to keep this from stepping on the next statement
	delay(10);
*/
/*	serial_out("Hello71\n");//,0);
/
	// Send a bunch of stuff to see if it poops out
	serial_out("serial_out The quick brown fox jumped over the lazy dog.");

	serial_out("serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("1serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("2serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("3serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("4serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("5serial_printf The quick brown fox jumped over the lazy dog.\n");
*/
	//char c = 'A';
	//uint8_t x = 0x22;
	//uint16_t X = 0x1122;

	//serial_out("Test character: %c\n", c);

	//serial_out("Test hexadecimal integer: %x\n", x);

	//serial_out("Test 16-bit hexadecimal integer: %x\n", X);

	//uint8_t  my_day = 21;
	//uint8_t my_month[] = {"July"};
	//uint16_t my_year = 1980;
	
	//serial_out("Your date of birth is:\nDay: %d \nMonth: %s \nYear: %d.", my_day, my_month, my_year); 
	
	/*while(1)
	{
		//delay(1000);
		//usart0_transmit_buffer_insert('#');	

		if(usart0_receive_buffer_inuse_count())//serial_available())
		{
			count = usart0_receive_buffer_inuse_count();

			for(int i = 0 ; i < count; i++)
			{
				//str[i] = 1;//serial_in();
				usart0_transmit_buffer_insert(usart0_receive_buffer_remove());
			}
			*/
			//serial_write(buf,count);
		
			// Test serial_flush
			/*
			serial_write(buf,count);
			serial_flush();
			serial_write(buf,count);
			*/

			// Test usart0_uninit()
			/*
			_delay_ms(500);
			serial_printf("Before serial_end()\n",0);
			serial_end();
			serial_printf("After serial_end()\n",0);
				serial_begin(57600);
			serial_printf("After serial_begin(57600)\n",0);
			*/
		//}
	//}//
}
