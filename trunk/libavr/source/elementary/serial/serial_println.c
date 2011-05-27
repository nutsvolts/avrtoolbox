#include "serial.h"

void serial_println(char *str)
{
	serial_print(str);
	//finish by sending a newline character
	//usart0_transmit_buffer_insert(0x0D);
	//loop_until_bit_is_set(UCSRA, UDRE); // wait for UDR to be clear 
   	//UDR = 0x0D;    //send the character 
   	loop_until_bit_is_set(UART_CONTROL_STATUS_REG_A, UART_READY_TO_TRANSMIT); // wait for UDR to be clear 
   	UART_DATA_REG = 0x0D;    //send the character 


}
