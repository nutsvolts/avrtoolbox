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
 

/*
	JWP 3/27/11 made many modifications to xxx code over the 
	past several weeks and I didn't document each and every one.

	The functions in this file should all be compiled into one object module

	NOTE: the flow control from xxx code hasn't been tested and is commented
	out here since I don't need it but other's may want to uncomment it and test it.
*/


#define USART0_C

// INCLUDES
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ascii.h"
#include "slice.h"
#include "usart.h"

#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "c:\avrtoolbox\libavr\source\general\util\util.h"
#include "c:\avrtoolbox\libavr\source\elementary\serial\serial.h"


#if defined(BUTTERFLY)
#include "..\butterfly\butterfly.h"
#endif



// Keep this in the same file as the usart0_put_char function
FILE mystdout = FDEV_SETUP_STREAM(usart0_put_char, NULL, _FDEV_SETUP_WRITE);

int usart0_put_char(char c, FILE *stream) 
{ 
	if (c == '\n') usart0_put_char('\r', stream);

	// Waiting when the buffer is 2/3 full prevents overrun.
	while(usart0_transmit_buffer_inuse_count() > ((2*USART0_TRANSMIT_BUFFER_LEN)/3)) delay(1);

	usart0_transmit_buffer_insert((uint8_t)c);
   	
   	return 0; 
} 

/*
bool usart0_transmit_buffer_fill(uint8_t c)
{
    register bool result;
    result = usart0_buffer_insert(&usart0_transmit_ring, c);

    return(result);

}
*/


void usart0_init(uint32_t baud, uint32_t freq_cpu, usart_mode_t mode, usart_databits_t databits, usart_stopbits_t stopbits, usart_parity_t parity, usart_flow_control_t flow_control)
{

   	stdout = &mystdout;    //set the output stream 

    //flow.flow_control = flow_control;
    //flow.flow_out = true;
    //flow.flow_in = true;

	// JWP 3/27/11 the following was already commented out in xxx code
    // Initialize hw flow control task.
    // flow_out_tcb.handler = usart0_flow_out_hw_task;
    // flow_out_tcb.absolute_timing = false;
    // flow_out_tcb.run_interval = 0;
    // flow_out_tcb.enabled = false;
    // task_add(&flow_out_tcb);


	usart0_receive_disable();
	usart0_transmit_disable();

    usart0_receive_complete_interrupt_disable();
	usart0_data_register_empty_interrupt_disable();
    
	usart0_mode(mode);
 	usart0_baud_set(baud, freq_cpu);
    usart0_data_bits_set(databits);
    usart0_stop_bits_set(stopbits);
    usart0_parity_set(parity);

/*
//#if defined(BUTTERFLY)
	//butterfly_uart_init();
	// Butterfly specific 

	/// boost IntRC to 2Mhz to achieve 19200 baudrate
    CLKPR = (1<<CLKPCE);        /// set Clock Prescaler Change Enable
    /// set prescaler = 4, Inter RC 8Mhz / 4 = 2Mhz
    CLKPR = (1<<CLKPS1);  

    /// Enable 2x speed
    UART_CONTROL_STATUS_REG_A = (1<<UART_DOUBLE_SPEED);

	/// At this point you have doubled the F_CPU and doubled the 
	/// uart speed so the Butterfly F_CPU 1000000 is for baudrate
	/// purposes 4000000 thus the *4
	UART_BAUD_RATE_HIGH = 0;//((F_CPU*4)/(baudrate*16L)-1) >> 8;
	UART_BAUD_RATE_LOW = 12;//(uint8_t)((F_CPU*4)/(baudrate*16L)-1);

    /// Enable receiver and transmitter
	// JWP added | 10/22/10
	UART_CONTROL_STATUS_REG_B |= (1 << UART_ENABLE_RECEIVER) | (1 << UART_ENABLE_TRANSMITTER);

    /// Async. mode, 8N1
	UART_CONTROL_STATUS_REG_C |= (1 << UART_CHARACTER_SIZE_0) | (1 << UART_CHARACTER_SIZE_1);
//#endif
*/

	ring_init(&usart0_receive_ring, usart0_receive_buffer, USART0_RECEIVE_BUFFER_LEN);
    ring_init(&usart0_transmit_ring, usart0_transmit_buffer, USART0_TRANSMIT_BUFFER_LEN);

    usart0_receive_complete_interrupt_enable();
    usart0_data_register_empty_interrupt_enable();
    
    usart0_receive_enable();
	usart0_transmit_enable();

	// JWP 3/27/11 the following was already commented out in Exxx code.
    //usart0_rts_init();
    //usart0_cts_init();

	sei();

	return;
}

// 3/18/11 JWP removed magic number for clock and added freq_cpu
void usart0_baud_set(uint32_t baudrate, uint32_t freq_cpu)
{
	uint16_t setting;
	
	setting = usart_baudrate_to_setting(freq_cpu,baudrate);
	
	// Write hi byte first as writing lo byte will trigger immediate update of baud prescaler.
	UART_BAUD_RATE_HIGH = hi_byte(setting);
	UART_BAUD_RATE_LOW= lo_byte(setting);
	
	return;
}

void usart0_parity_set(usart_parity_t parity)
{
    if(parity > 0)
    {
        parity++;
    }
    bit_write(bit_read(parity, BIT(0)), UART_CONTROL_STATUS_REG_C, BIT(UART_PARITY_MODE_0));
    bit_write(bit_read(parity, BIT(1)), UART_CONTROL_STATUS_REG_C, BIT(UART_PARITY_MODE_1));
    return;
}

// The interrupt service routines are included in the initialization .c file 
// since they must be associated with a .c file for the compiler
usart0_transmit_interrupt_service_routine
{	
    if(usart0_transmit_ring.count)
    {
        UART_DATA_REG = ring_remove(&usart0_transmit_ring);
    }

    if (usart0_transmit_ring.count > 0)// && flow.flow_out)
    {
        usart0_data_register_empty_interrupt_enable();
    }
    else
    {
        usart0_data_register_empty_interrupt_disable();
    }
    
    return;
}


void usart0_transmit_check(void)
{
    register uint8_t sreg;
    register uint8_t count;

    sreg = SREG;
    cli();
    count = usart0_transmit_ring.count;
    SREG = sreg;

    if (count > 0)// && flow.flow_out)
    {
        usart0_data_register_empty_interrupt_enable();
    }
    else
    {
        usart0_data_register_empty_interrupt_disable();
    }

    return;
}


// The interrupt service routines are included in the initialization .c file 
// since they must be associated with a .c file for the compiler
usart0_receive_interrupt_service_routine
{
	register uint8_t data;
	register uint8_t parity_error = false;
	register uint8_t frame_error = false;

	// Get error conditions before getting the data.
	frame_error = usart0_frame_error();
	parity_error = usart0_parity_error();
	
	data = UART_DATA_REG;
    
	if(!frame_error && !parity_error)
	{
		// Store data in ring buffer.
        ring_add(&usart0_receive_ring, data);
	}

	return;
}




