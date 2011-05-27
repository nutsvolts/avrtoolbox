#include "serial.h"

uint8_t serial_in(void)
{
	return usart0_receive_buffer_remove();
}


