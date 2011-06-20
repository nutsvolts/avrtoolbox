/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2011, and Joe Pardue, All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 *   
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *   
 *  - Neither the name of Joe Pardue nor the names of 
 *    its contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission. 
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
 
 // Some of this code may have elements taken from other code without attribution.
 // If this is the case it was due to oversight while debugging and I apologize.
 // If anyone has any reason to believe that any of this code violates other licenses
 // please contact me with details so that I may correct the situation. 


// TODO - THE DELAY MAY NO LONGER BE NECESSARY DUE TO A FIX IN THE USART CODE
// TODO - RETEST THIS WITHOUT THE DELAY
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



