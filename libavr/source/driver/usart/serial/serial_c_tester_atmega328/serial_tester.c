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
	serial_out("Hello71\n");//,0);

	// Send a bunch of stuff to see if it poops out
	serial_out("serial_out The quick brown fox jumped over the lazy dog.");

	serial_out("serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("1serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("2serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("3serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("4serial_printf The quick brown fox jumped over the lazy dog.\n");
	serial_out("5serial_printf The quick brown fox jumped over the lazy dog.\n");

/**/
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
			serial_printf("Before serial_end()\n",0);
			serial_end();
			serial_printf("After serial_end()\n",0);
				serial_begin(57600);
			serial_printf("After serial_begin(57600)\n",0);
			*/
		}
	}
}
