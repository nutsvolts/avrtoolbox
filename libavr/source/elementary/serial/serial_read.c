#include "serial.h"

uint8_t serial_read(void)
{
	return usart0_receive_buffer_remove();
}


