//#include "..\devices\devices.h"


// We use a delay in serial_printf if the string to be printed comes withing 2/3
// of the maximum buffer length. The 2/3 and the delays were determined empirically
// to prevent the test code from stepping on the usart buffer. If you are certian that
// you won't send serial_printf strings greater than the buffer size and that you won't
// use the serial_printf to send long strings more frequently than about 20ms then you 
// can remove the if() condition. We have this as the default condition for the serial
// library since we assume the users are novices and might miss a note to avoid long or
// frequent use of the serial_printf function.
#if defined(BUTTERFLY)
#include ".\butterfly\butterfly.h"
#define serial_printf(val1, val2) {printf_P(PSTR(val1),val2); if(usart0_transmit_buffer_inuse_count() > ((2*USART0_TRANSMIT_BUFFER_LEN)/3)) delay(20);}
#else
#define serial_printf(val1, val2) {printf_P(PSTR(val1),val2); if(usart0_transmit_buffer_inuse_count() > ((2*USART0_TRANSMIT_BUFFER_LEN)/3)) delay(10);}
#endif

#include "c:\avrtoolbox\libavr\source\driver\usart\usart0.h"

#include <util\delay.h>

void serial_begin(uint32_t baudrate);
void serial_end(void);
void serial_print(char *s);
void serial_println(char *s);
uint8_t serial_available(void);
uint8_t serial_read(void);
void serial_write(uint8_t *buff, uint8_t size);
void serial_flush(void);


void delay(uint16_t ms);


void delay(uint16_t ms)
{
	for(int i = 0 ; i < ms ; i++)
	{
		_delay_ms(1);
	}
}




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

uint8_t serial_available(void)
{
	return usart0_receive_buffer_inuse_count();	
}

uint8_t serial_read(void)
{
	return usart0_receive_buffer_remove();
}

void serial_write(uint8_t *buff, uint8_t size)
{
	for(int i = 0; i < size; i++)
	{
		usart0_transmit_buffer_insert(buff[i]);
	}
}

void serial_flush(void)
{
	cli();
	usart0_receive_buffer_clear();
	usart0_transmit_buffer_clear();
	sei();

}

void serial_end(void)
{
	usart0_uninit();
}



