#include "serial.h"


void serial_begin(uint32_t baud)
{
	cli();

	// Modem parameters used by common serial connections
	usart_mode_t mode = usart_mode_asynchronous;
	uint8_t databits = 8;
	uint8_t stopbits = 1;
	usart_parity_t parity = parity_none;
	usart_flow_control_t flow_control = flow_none;

	usart0_init(baud, F_CPU, mode,  databits, stopbits, parity, flow_control);

	sei();

}



