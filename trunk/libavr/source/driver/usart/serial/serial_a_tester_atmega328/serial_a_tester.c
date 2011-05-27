#include "c:\avrtoolbox\libavr\source\elementary\serial\serial.h" //"libserial\serial.h"

int main(void)
{
	uint8_t count = 0;
	uint8_t buf[64];

	#if defined(BUTTERFLY)
	butterfly_init();
	#endif

	// NOTE: If BUTTERFLY is defined then the serial_being() is bypassed
	// and the usart is set to 19200 regardless of what this says
	serial_begin(57600);


/*
	buf[0] = 'H';
	buf[1] = 'o';
	buf[2] = 'w';
	buf[3] = 'd';
	buf[4] = 'y';
	buf[5] = 0;

	serial_write(buf,6);
	// Insert a delay to keep this from stepping on the next statement
	delay(10);
*/
	serial_out("Hello70");

	// Send a bunch of stuff to see if it poops out
	serial_out("serial_println The quick brown fox jumped over the lazy dog.");

	serial_out("serial_out The quick brown fox jumped over the lazy dog.\n",0);
	serial_out("1serial_out The quick brown fox jumped over the lazy dog.\n",0);
	serial_out("2serial_out The quick brown fox jumped over the lazy dog.\n",0);
	serial_out("3serial_out The quick brown fox jumped over the lazy dog.\n",0);
	serial_out("4serial_out The quick brown fox jumped over the lazy dog.\n",0);
	serial_out("5serial_out The quick brown fox jumped over the lazy dog.\n",0);


	char c = 'A';
	uint8_t x = 0x22;
	uint16_t X = 0x1122;

	serial_out("Test character: %c\n", c);

	serial_out("Test hexadecimal integer: %x\n", x);

	serial_out("Test 16-bit hexadecimal integer: %x\n", X);

	while(1)
	{
		delay(1000);
		usart0_transmit_buffer_insert('#');	

		if(serial_available())
		{
			count = usart0_receive_buffer_inuse_count();

			for(int i = 0 ; i < count; i++)
			{
				buf[i] = serial_in();
				//usart0_transmit_buffer_insert(serial_read());//usart0_receive_buffer_remove());
			}
			
			serial_write(buf,count);
		
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


