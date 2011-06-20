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
	usart0.c holds API functions that will always be required. 

	It also declarations defines and functions used to support the API functions

*/



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

#include "c:\avrtoolbox\libavr\source\general\util\util.h"


//
// defines
//


#define usart_baudrate_to_setting(f_cpu, baud)		(uint16_t)(((uint32_t)(f_cpu) / ((uint32_t)(baud) * (uint32_t)16)) - 1)


// Begin changes 3/17/11 JWP
// Added Atmega328
// TODO:
// This code is tested in the most common uart mode: N,8,1 
// Needs testing in other modes and with the hw and sw flow control
// PLEASE - anyone who adapts this code for the untested modes show
// us what you did so we can patch this.

// 3/18/11 JWP added Atmega169
#if defined(__AVR_ATmega169__)
   // ATMega with one uart that doesn't use 0 after register/bit names
   // like ATmega169
   #define UART_BAUD_RATE_HIGH			UBRRH
   #define UART_BAUD_RATE_LOW			UBRRL
   #define UART_CONTROL_STATUS_REG_A	UCSRA
   #define UART_CONTROL_STATUS_REG_B	UCSRB
   #define UART_CONTROL_STATUS_REG_C	UCSRC

   #define UART_ENABLE_TRANSMITTER		TXEN
   #define UART_ENABLE_RECEIVER			RXEN
   #define UART_READY_TO_TRANSMIT		UDRE
   #define UART_TRANSMIT_COMPLETE		TXC
   #define UART_RECEIVE_COMPLETE		RXC
   #define UART_DATA_REG				UDR
   #define UART_STOP_BIT_SELECT			USBS
   #define UART_CHARACTER_SIZE_0		UCSZ0
   #define UART_CHARACTER_SIZE_1		UCSZ1
   #define UART_CHARACTER_SIZE_2		UCSZ2
   #define UART_MODE_SELECT				UMSEL
   #define UART_DOUBLE_SPEED			U2X
   #define UART_FRAME_ERROR				FE
   #define UART_DATA_OVER_RUN			DOR
   #define UART_PARITY_ERROR			UPE
   #define UART_PARITY_MODE_0			UPM0
   #define UART_PARITY_MODE_1			UPM1
   #define UART_MULTI_PROCESSOR_COMMUNICATION_MODE	MPCM
   #define UART_TX_COMPLETE_INTERRUPT_ENABLE	TXCIE
   #define UART_RX_COMPLETE_INTERRUPT_ENABLE 	RXCIE
   #define UART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE	UDRIE
   #define UART_RX_DATA_BIT_8	RXB8
   #define UART_TX_DATA_BIT_8	TXB8

// JWP 6/19/11
//#define usart0_mode(x) (UART_CONTROL_STATUS_REG_C = (UART_CONTROL_STATUS_REG_C & (uint8_t)~(1<<UART_MODE_SELECT)) | (uint8_t)((x) << UART_MODE_SELECT))


#elif defined(__AVR_ATmega128__) \
|| defined(__AVR_ATmega1281__) \
|| defined(__AVR_ATmega2561__) \
|| defined(__AVR_ATmega328P__)

   // ATMega with two uarts - uart 0
   // or with one uart but using 0 in register/bit names (like ATmega328)
   #define UART_BAUD_RATE_HIGH			UBRR0H
   #define UART_BAUD_RATE_LOW			UBRR0L
   #define UART_CONTROL_STATUS_REG_A	UCSR0A
   #define UART_CONTROL_STATUS_REG_B	UCSR0B
   #define UART_CONTROL_STATUS_REG_C	UCSR0C

   #define UART_ENABLE_TRANSMITTER		TXEN0
   #define UART_ENABLE_RECEIVER			RXEN0
   #define UART_READY_TO_TRANSMIT		UDRE0
   #define UART_TRANSMIT_COMPLETE		TXC0
   #define UART_RECEIVE_COMPLETE		RXC0
   #define UART_DATA_REG				UDR0
   #define UART_STOP_BIT_SELECT			USBS0
   #define UART_CHARACTER_SIZE_0		UCSZ00
   #define UART_CHARACTER_SIZE_1		UCSZ01
   #define UART_CHARACTER_SIZE_2		UCSZ02
   #define UART_MODE_SELECT				UMSEL // ATmega128 
   #define UART_MODE_SELECT_0			UMSEL00
   #define UART_MODE_SELECT_1			UMSEL01
   #define UART_DOUBLE_SPEED			U2X0
   #define UART_FRAME_ERROR				FE0
   #define UART_DATA_OVER_RUN			DOR0
   #define UART_PARITY_ERROR			UPE0
   #define UART_PARITY_MODE_0			UPM00
   #define UART_PARITY_MODE_1			UPM01
   #define UART_MULTI_PROCESSOR_COMMUNICATION_MODE	MPCM0
   #define UART_TX_COMPLETE_INTERRUPT_ENABLE	TXCIE0
   #define UART_RX_COMPLETE_INTERRUPT_ENABLE 	RXCIE0
   #define UART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE	UDRIE0
   #define UART_RX_DATA_BIT_8	RXB80
   #define UART_TX_DATA_BIT_8	TXB08

	// JWP 6/19/11	TODO TEST FOR ATMEGA128
/*	#if defined(__AVR_ATmega128__)
	#define usart0_mode(x) (UART_CONTROL_STATUS_REG_C = (UART_CONTROL_STATUS_REG_C & (uint8_t)~(1<<UART_MODE_SELECT)) | (uint8_t)((x) << UART_MODE_SELECT))
	#else
	#define usart0_mode(x) (UART_CONTROL_STATUS_REG_C = (UART_CONTROL_STATUS_REG_C & (uint8_t)~((1<<UART_MODE_SELECT_0)|(1<<UART_MODE_SELECT_1))) | (uint8_t)((x) << UART_MODE_SELECT_0))
	#endif
*/
#else
   #error "no uart definition for MCU"
#endif

// GCC compiler specific.
#if defined(__AVR_ATmega128__) \
|| defined(__AVR_ATmega1281__) \
|| defined(__AVR_ATmega2561__) \
|| defined(__AVR_ATmega169__)
	#define usart0_receive_interrupt_service_routine        ISR(USART0_RX_vect)
	//#define usart0_transmit_interrupt_service_routine       ISR(USART0_UDRE_vect)
	// JWP 6/16/11 changed interrupt vector
	#define usart0_transmit_interrupt_service_routine       ISR(USART0_TX_vect)
#elif defined(__AVR_ATmega328P__)
	#define usart0_receive_interrupt_service_routine        ISR(USART_RX_vect)
	//#define usart0_transmit_interrupt_service_routine       ISR(USART_UDRE_vect)
	// JWP 6/16/11 changed interrupt vector
	#define usart0_transmit_interrupt_service_routine       ISR(USART_TX_vect)
#else
   #error "no interrupt definition for MCU"
#endif


#define usart0_mode(x) (UART_CONTROL_STATUS_REG_C = (UART_CONTROL_STATUS_REG_C & (uint8_t)~((1<<UART_MODE_SELECT_0)|(1<<UART_MODE_SELECT_1))) | (uint8_t)((x) << UART_MODE_SELECT_0))


#define usart0_clock_polarity(x)    bit_write(x, UART_CONTROL_STATUS_REG_C, BIT(UCPOL0))

#define usart0_transmit_enable()    (UART_CONTROL_STATUS_REG_B |= (uint8_t)(1 << UART_ENABLE_TRANSMITTER))
#define usart0_transmit_disable()   (UART_CONTROL_STATUS_REG_B &= (uint8_t)~(1 << UART_ENABLE_TRANSMITTER))

#define usart0_receive_enable()     (UART_CONTROL_STATUS_REG_B |= (uint8_t)(1 << UART_ENABLE_RECEIVER))
#define usart0_receive_disable()    (UART_CONTROL_STATUS_REG_B &= (uint8_t)~(1 << UART_ENABLE_RECEIVER))

#define usart0_transmit_speed_double_enable()   (UART_CONTROL_STATUS_REG_A |= (uint8_t)(1 << UART_DOUBLE_SPEED))
#define usart0_transmit_speed_double_disable()  (UART_CONTROL_STATUS_REG_A &= (uint8_t)~(1 << UART_DOUBLE_SPEED))

#define usart0_receive_complete()           bit_read(UART_CONTROL_STATUS_REG_A, BIT(UART_RECEIVE_COMPLETE))

#define usart0_transmit_complete()          bit_read(UART_CONTROL_STATUS_REG_A, BIT(UART_TRANSMIT_COMPLETE))

#define usart0_data_register_empty()        bit_read(UART_CONTROL_STATUS_REG_A, BIT(UART_READY_TO_TRANSMIT))

#define usart0_frame_error()                bit_read(UART_CONTROL_STATUS_REG_A, BIT(UART_FRAME_ERROR))

#define usart0_data_overrun()               bit_read(UART_CONTROL_STATUS_REG_A, BIT(UART_DATA_OVER_RUN))

#define usart0_parity_error()               bit_read(UART_CONTROL_STATUS_REG_A, BIT(UART_PARITY_ERROR))

#define usart0_multiprocessor_mode(x)       bit_write(x, UART_CONTROL_STATUS_REG_A, BIT(UART_MULTI-PROCESSOR_COMMUNICATION_MODE))

#define usart0_receive_complete_interrupt_enable()      (UART_CONTROL_STATUS_REG_B |= (uint8_t)(1 << UART_RX_COMPLETE_INTERRUPT_ENABLE))
#define usart0_receive_complete_interrupt_disable()     (UART_CONTROL_STATUS_REG_B &= (uint8_t)~(1 << UART_RX_COMPLETE_INTERRUPT_ENABLE))

#define usart0_receive_complete_interrupt_get()         (UART_CONTROL_STATUS_REG_B & (1 << UART_RX_COMPLETE_INTERRUPT_ENABLE))

#define usart0_transmit_complete_interrupt_enable()     UART_CONTROL_STATUS_REG_B |= (uint8_t)(1 << UART_TX_COMPLETE_INTERRUPT_ENABLE)
#define usart0_transmit_complete_interrupt_disable()    UART_CONTROL_STATUS_REG_B &= (uint8_t)~(1 << UART_TX_COMPLETE_INTERRUPT_ENABLE)

#define usart0_transmit_complete_interrupt_get()        (UART_CONTROL_STATUS_REG_B & (1 << TXCIE0))

#define usart0_data_register_empty_interrupt_enable()   (UART_CONTROL_STATUS_REG_B |= (uint8_t)(1 << UART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE))
#define usart0_data_register_empty_interrupt_disable()  (UART_CONTROL_STATUS_REG_B &= (uint8_t)~(1 << UART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE))

#define usart0_data_register_empty_interrupt_get()      bit_read(UART_CONTROL_STATUS_REG_B, BIT(UART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE))

#define usart0_receive_data_bit_8(x)                    bit_write(x, UART_CONTROL_STATUS_REG_B, BIT(UART_RX_DATA_BIT_8))

#define usart0_transmit_data_bit_8(x)                   bit_write(x, UART_CONTROL_STATUS_REG_B, BIT(UART_tX_DATA_BIT_8))

#define usart0_stop_bits_set(stop_bits) \
do{                                     \
    if((stop_bits) >= 1 && (stop_bits) <= 2)    \
    {                                           \
        bit_write((stop_bits) - 1, UART_CONTROL_STATUS_REG_C, BIT(UART_STOP_BIT_SELECT)); \
    }                                           \
}while(0)


#define usart0_data_bits_set(data_bits) \
do{         \
    if((data_bits) >= 5 && (data_bits) <= 8)    \
    {       \
        bit_write(bit_read(((data_bits) - 5), BIT(0)), UART_CONTROL_STATUS_REG_C, BIT(UART_CHARACTER_SIZE_0)); \
        bit_write(bit_read(((data_bits) - 5), BIT(1)), UART_CONTROL_STATUS_REG_C, BIT(UART_CHARACTER_SIZE_1)); \
        bit_clear(UART_CONTROL_STATUS_REG_B, BIT(UART_CHARACTER_SIZE_2));     \
    }       \
    if((data_bits) == 9)    \
    {       \
        bit_set(UART_CONTROL_STATUS_REG_C, BIT(UART_CHARACTER_SIZE_0));    \
        bit_set(UART_CONTROL_STATUS_REG_C, BIT(UART_CHARACTER_SIZE_1));    \
        bit_set(UART_CONTROL_STATUS_REG_B, BIT(UART_CHARACTER_SIZE_2));    \
    }       \
}while(0)

#define usart0_rts_enable()     bit_clear(USART0_RTS_PORT, USART0_RTS)

#define usart0_rts_disable()    bit_set(USART0_RTS_PORT, USART0_RTS)

#define usart0_rts_init()   \
do{     \
    usart0_rts_enable();    \
    bit_set(USART0_RTS_PORT_DIRECTION, USART0_RTS); \
}while(0)

#define usart0_cts_read()       bit_read(USART0_CTS_PORT, USART0_CTS)

#define usart0_cts_init()   \
do{     \
    bit_clear(USART0_CTS_PORT_DIRECTION, USART0_CTS); \
}while(0)


//
// Non-API functions
//

void usart0_baud_set(uint32_t baudrate, uint32_t freq_cpu);
void usart0_parity_set(usart_parity_t parity);
void usart0_flow_control_set(usart_flow_control_t flow_control);


// Removed from usart.h since it isn't available in the API
/*
 \ingroup usart

    \brief Puts a character into the usart transmit buffer.
	 
    \param c the char to be sent.
	\param stream a pointer to the C output stream. 

	The C output stream is attached with the following:
	\code
	FILE mystdout = FDEV_SETUP_STREAM(usart0_put_char, NULL, _FDEV_SETUP_WRITE);
	\endcode
	See the avrlibc manual for details

	\return 0

*/
int usart0_put_char_stream(char c, FILE *stream);

// Keep this in the same file as the usart0_put_char function
FILE mystdout = FDEV_SETUP_STREAM(usart0_put_char_stream, NULL, _FDEV_SETUP_WRITE);
int usart0_put_char_stream(char c, FILE *stream) 
{ 
	if (c == '\n') usart0_put_char_stream('\r', stream);

	usart0_transmit_buffer_insert((uint8_t)c);
   	
	usart0_send();

   	return 0; 
} 

void usart0_init(uint32_t baud, uint32_t freq_cpu, usart_mode_t mode, usart_databits_t databits, usart_stopbits_t stopbits, usart_parity_t parity, usart_flow_control_t flow_control)
{

	cli();

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

 
 	usart0_transmit_disable();
    usart0_receive_disable();
	usart0_transmit_complete_interrupt_disable();
    usart0_receive_complete_interrupt_disable();

//  JWP 6/19/11 Just use default while testing
// TODO: figure this out someday   
//	usart0_mode(mode);
 	usart0_baud_set(baud, freq_cpu);
    usart0_data_bits_set(databits);
    usart0_stop_bits_set(stopbits);
    usart0_parity_set(parity);
 
 	usart0_baud_set(baud, freq_cpu);

//JWP 6/16/11 The Butterfly requires special code for clock and baud
#if defined(__AVR_ATmega169__) // Assume Butterfly
	butterfly_init();
#endif


	ring_init(&usart0_receive_ring, usart0_receive_buffer, USART0_RECEIVE_BUFFER_LEN);
    ring_init(&usart0_transmit_ring, usart0_transmit_buffer, USART0_TRANSMIT_BUFFER_LEN);

	// JWP 6/16/11 
	usart0_transmit_enable();
    usart0_receive_enable();
	usart0_transmit_complete_interrupt_enable();
    usart0_receive_complete_interrupt_enable();

	// JWP 6/16/11 - set flags for revised transmission logic
	usart_buffered_tx_flag = false;
	usart_tx_ready_flag = true;

	sei();

	return;
}


void usart0_uninit(void)
{
	// restore to datasheet defaults
	UART_CONTROL_STATUS_REG_A = 0x20;
	UART_CONTROL_STATUS_REG_B = 0;
	UART_CONTROL_STATUS_REG_C = 0x06;
}


// JWP 6/16/11 added to change transmission logic.
// this function waits until a pending transmission is complete
// then sends a byte. If the usart_buffered_TX_flag is set true
// then the ISR continues to send until the buffer is empty, otherwise
// the ISR just sends the byte. 
void usart0_send(void)
{

	// Wait until the transmitter is ready
	while(!usart_tx_ready_flag);

	// Set flag for ISR
	usart_buffered_tx_flag = true;
	
	// Send the byte
	UART_DATA_REG = ring_remove(&usart0_transmit_ring);

	// Set the ready flag to false
	usart_tx_ready_flag = false;
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

// JWP 6/16/11 rewrote transmit interrupt to use TX complete vector
// rather than the Data Register Empty vector
// The interrupt service routines are included in the initialization .c file 
// since they must be associated with a .c file for the compiler
usart0_transmit_interrupt_service_routine
{

	// Is buffered transmission enabled?
	if(usart_buffered_tx_flag)
	{		
		//if(usart0_transmit_ring.count)// Alternate technique
		if(usart0_transmit_buffer_inuse_count())// Is there data in the buffer?
		{
			// Send next byte in the buffer.
 	       UART_DATA_REG = ring_remove(&usart0_transmit_ring);
		}
		else
		{
			// The buffer is empty
			usart_buffered_tx_flag = false;
			// Set the ready flag
			usart_tx_ready_flag = true;
		}
	}
	else // Not buffered so transmited single byte
	{
		// Set transmit ready flag
		usart_tx_ready_flag = true;
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




