#include "serial.h"

void serial_flush(void)
{
	cli();
	usart0_receive_buffer_clear();
	usart0_transmit_buffer_clear();
	sei();

}

