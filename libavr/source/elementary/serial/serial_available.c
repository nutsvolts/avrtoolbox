#include "serial.h"

uint8_t serial_available(void)
{
	return usart0_receive_buffer_inuse_count();	
}
