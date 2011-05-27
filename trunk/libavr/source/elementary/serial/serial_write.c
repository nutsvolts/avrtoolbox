#include "serial.h"

void serial_write(uint8_t *buff, uint8_t size)
{
	for(int i = 0; i < size; i++)
	{
		usart0_transmit_buffer_insert(buff[i]);
	}
}



