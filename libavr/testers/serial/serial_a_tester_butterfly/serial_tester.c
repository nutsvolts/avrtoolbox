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

#include "c:\avrtoolbox\libavr\source\elementary\serial\serial.h"

int main(void)
{ 
	uint8_t count = 0;
	uint8_t buf[64];


	// NOTE: If BUTTERFLY is defined then the serial_being() is bypassed
	// and the usart is set to 19200 regardless of what this says
	serial_begin(57600);


	serial_out("Serial tester 014\n");//,0);

	// Send a bunch of stuff to see if it poops out
	serial_out("serial_out The quick brown fox jumped over the lazy dog.");
	serial_out("serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("1serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("2serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("3serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("4serial_out The quick brown fox jumped over the lazy dog.\n");
	serial_out("5serial_out The quick brown fox jumped over the lazy dog.\n");

	char c = 'A';
	uint8_t x = 0x22;
	uint16_t X = 0x1122;

	serial_out("Test character: %c\n", c);

	serial_out("Test hexadecimal integer: %x\n", x);

	serial_out("Test 16-bit hexadecimal integer: %x\n", X);

	uint8_t  my_day = 21;
	uint8_t my_month[] = {"July"};
	uint16_t my_year = 1980;
	
	serial_out("Your date of birth is:\nDay: %d \nMonth: %s \nYear: %d.", my_day, my_month, my_year); 
	
	buf[1] = '\0';
	while(1)
	{
		if(serial_available())
		{
			buf[0] = serial_in();
			serial_write(buf,1);
/*			count = usart0_receive_buffer_inuse_count();

			for(int i = 0 ; i < count; i++)
			{
				buf[i] = serial_in();
				//usart0_transmit_buffer_insert(serial_read());//usart0_receive_buffer_remove());
			}
			
			serial_write(buf,count);
*/		
			// Test serial_flush
			/*
			serial_write(buf,count);
			serial_flush();
			serial_write(buf,count);
			*/

			// Test usart0_uninit()
			/*
			_delay_ms(500);
			serial_out("Before serial_end()\n",0);
			serial_end();
			serial_out("After serial_end()\n",0);
				serial_begin(57600);
			serial_out("After serial_begin(57600)\n",0);
			*/
		}
	}
}



