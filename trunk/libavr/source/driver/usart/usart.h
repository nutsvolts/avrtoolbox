/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2011, Eric Weddington and Joe Pardue, All rights reserved.
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
 *  - Neither the name of the Eric Weddington nor Joe Pardue nor the names of 
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

#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <stdint.h>


typedef enum
{
    usart_mode_asynchronous = 0,
    usart_mode_synchronous = 1
} usart_mode_t;


typedef enum
{
    parity_none = 0,
	parity_even = 1,
    parity_odd = 2
} usart_parity_t;

typedef enum
{
	baud_1200 = 1200,
	baud_2400 = 2400,
	baud_4800 = 4800,
	baud_9600 = 9600,
	baud_19200 = 19200,
	baud_38400 = 38400,
	baud_57600 = 57600 // 3/17/11 JWP
} usart_baud_t;

// JWP 3/21/11
typedef enum
{
    bit5 = 5,
    bit6 = 6,
    bit7 = 7,
	bit8 = 8,
	bit9 = 9
} usart_databits_t;

typedef enum
{
	stopbit1 = 1,
	stopbit2 = 2
} usart_stopbits_t;	

typedef enum
{
    flow_none = 0,
    flow_sw = 1,
    flow_hw = 2
} usart_flow_control_t;

typedef struct
{
    usart_flow_control_t flow_control;
    uint8_t flow_out;
    uint8_t flow_in;
} usart_flow_t;

typedef struct
{
    usart_baud_t baud;
    usart_parity_t parity;
    usart_flow_control_t flow_control;
} usart_port_settings_t;


#define usart_baudrate2setting(f_cpu, baud)		(uint16_t)(((uint32_t)(f_cpu) / ((uint32_t)(baud) * (uint32_t)16)) - 1)

/*
#if defined(BUTTERFLY)
#include "..\butterfly\butterfly.h"
#endif
*/
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
#else
   #error "no uart definition for MCU"
#endif

// GCC compiler specific.
#if defined(__AVR_ATmega128__) \
|| defined(__AVR_ATmega1281__) \
|| defined(__AVR_ATmega2561__) \
|| defined(__AVR_ATmega169__)
	#define usart0_receive_interrupt_service_routine        ISR(USART0_RX_vect)
	#define usart0_transmit_interrupt_service_routine       ISR(USART0_UDRE_vect)
#elif defined(__AVR_ATmega328P__)
	#define usart0_receive_interrupt_service_routine        ISR(USART_RX_vect)
	#define usart0_transmit_interrupt_service_routine       ISR(USART_UDRE_vect)
#else
   #error "no interrupt definition for MCU"
#endif


// API

// ATmega169 only has UMSEL
// ATmega128 only has UMSEL0
// ATmega1281, 2561, 328P, have UMSEL0 and UMSEL1

// Select synchronous or asynchronous mode
// Note: if you add a device carefully check the bits used
// UMSELn 1 asynchronous
// UMSELn 0 synchronous
#if defined(__AVR_ATmega128__)
    #define usart0_mode(x)          bit_write(x, UART_CONTROL_STATUS_REG_C, BIT(UART_MODE_SELECT))
#elif defined(__AVR_ATmega169__)
    #define usart0_mode(x)          bit_write(x, UART_CONTROL_STATUS_REG_C, BIT(UART_MODE_SELECT))
#elif defined(__AVR_ATmega1281__) \
|| defined(__AVR_ATmega2561__) \
|| defined(__AVR_ATmega328P__) \
|| defined(__AVR_ATmega169__)
    #define usart0_mode(x)      (UART_CONTROL_STATUS_REG_C = (UART_CONTROL_STATUS_REG_C & (uint8_t)~((1<<UART_MODE_SELECT_0)|(1<<UART_MODE_SELECT_1))) | (uint8_t)((x) << UART_MODE_SELECT_0))
#else
   #error "no usart0_mode(x) definition for MCU"
#endif

// End changes
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

//void usart0_init(usart_mode_t mode, uint32_t baud, uint8_t databits, uint8_t stopbits, usart_parity_t parity, flow_control_t flow_control);

void usart0_baud_set(uint32_t baudrate, uint32_t freq_cpu);
void usart0_parity_set(usart_parity_t parity);
void usart0_flow_control_set(usart_flow_control_t flow_control);


#endif



