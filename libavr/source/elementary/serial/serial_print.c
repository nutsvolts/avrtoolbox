#include "serial.h"

#define MAX_STRING 255 // stop if not a string
void serial_print(char *str)
{

	int i = 0;
	// Send until encountering string terminator
	// or exceeding MAX_STRING size in case str is not a string
	while( (str[i] != '\0') && ( i < MAX_STRING) )
	{
		//loop_until_bit_is_set(UCSRA, UDRE); // wait for UDR to be clear 
   		//UDR = str[i++];    //send the character 
   		loop_until_bit_is_set(UART_CONTROL_STATUS_REG_A, UART_READY_TO_TRANSMIT); // wait for UDR to be clear 
   		UART_DATA_REG = str[i++];    //send the character 


		//usart0_transmit_buffer_insert(str[i++]);
	}	
}
