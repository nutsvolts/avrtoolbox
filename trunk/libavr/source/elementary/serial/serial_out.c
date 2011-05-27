#include "serial.h"
#include <stdio.h>
#include <stdarg.h>



// The delay is added to prevent buffer overrun
// The variadic (va_) stuff is magic 
//void serial_out(const char *fmt, ...)
void serial_out(const char *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	if(usart0_transmit_buffer_inuse_count() > ((2*USART0_TRANSMIT_BUFFER_LEN)/3)) delay(BUFFER_DELAY);
	vprintf(fmt, arg);
	va_end(arg);
}


