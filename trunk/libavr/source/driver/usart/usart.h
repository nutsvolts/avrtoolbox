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
 

#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include <avr/pgmspace.h> 
#include <stdio.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "bit.h"

#include "c:\avrtoolbox\libavr\source\general\ring\ring.h"



//
// Create the buffers
//

ring_t usart0_receive_ring;
#define USART0_RECEIVE_BUFFER_LEN   64
uint8_t usart0_receive_buffer[USART0_RECEIVE_BUFFER_LEN];

ring_t usart0_transmit_ring;
#define USART0_TRANSMIT_BUFFER_LEN  128
uint8_t usart0_transmit_buffer[USART0_TRANSMIT_BUFFER_LEN];


//
// Create some useful typdefs
//

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


//
// API functions
// These functions have doxygen comments for inclusion in the avrtoolbox API
//

/*!
	\defgroup usart USART Drivers
*/
/**
	\ingroup usart

	\brief intializes the uart parameters

	\param mode 
	\code
	typedef enum
	{
	    usart_mode_asynchronous = 0,
	    usart_mode_synchronous = 1
	} usart_mode_t;
	\endcode

	\param baud
	\code
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
	\endcode
	
	\param freq_cpu uint32_t value used to calculate the baud rate parameters
	
	\param databits uint8_t Number of data bits
	\code
	typedef enum
	{
	    5-bit = 5,
	    6-bit = 6,
	    7-bit = 7,
		8-bit = 8,
		9-bit = 9
	} usart_databits_t;
	\endcode
	

	\param stopbits uint8_t Number of stop bits
	\code
	typedef enum
	{
	    1-stopbit = 1,
	    2-stopbit = 6,
	} usart_stopbits_t;	
	\endcode

	\param parity
	\code
	typedef enum
	{
	    parity_none = 0,
		uparity_even = 1,
	    uparity_odd = 2
	} usart_parity_t;
	\endcode

	\param flow_control
	\code
	typedef enum
	{
	    flow_none = 0,
	    flow_sw = 1,
	    flow_hw = 2
	} usart_flow_control_t;
	\endcode
*/
void usart0_init(uint32_t baud, uint32_t freq_cpu, usart_mode_t mode, usart_databits_t databits, usart_stopbits_t stopbits, usart_parity_t parity, usart_flow_control_t flow_control);

/**
	\ingroup usart

	\brief intializes the uart the baudrate and parameters with defaults: 
	 8 data bits, no parity, one stop bit, and no handshaking


	\param baud
	\code
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
	\endcode


*/
void usart0_init_baud(uint32_t baud);


/** \ingroup usart

    \brief Gets the receive buffer count
	This can be used as a boolean since if the buffer is empty it returns 0.
	 
    \return receive buffer count.
*/
bool usart0_available(void);


/** \ingroup usart

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
int usart0_put_char(char c, FILE *stream);

/*


Read or write to the buffers one byte at a time.
uint8_t usart0_get_byte_read()
void usart0_put_byte_write(uint8_t b)


Read or writeg to the buffers one char at a time.
char usart0_get_char()
Read or write simple strings.
bool usart0_send_string(char *str) - TODO: USE PROGMEM
???bool usart0_receive_string(char *str) - TODO: ? BUFFER?
*/




/** 
	\ingroup usart

	\brief This clear function will reset the transmit buffer head_index
	and tail_index to 0. The count value is also set to 0. A memset command 
	is used to reset a particular area in memory as well.

*/
void usart0_transmit_buffer_clear(void);

/** 
	\ingroup usart

	\brief Adds the byte 'c' to the transmit buffer and returns
	True if it was able to add the byte, False otherwise.
  
    \note Data added will be one value less than the size
    of the defined receive buffer. An example of this is a buffer
    size of [10] will only allow 9 values to be added into the buffer
	
	\param c byte to add
	\return boolean result of attempt to add byte
	
*/
bool usart0_transmit_buffer_insert(uint8_t c);

/** \ingroup usart

    \brief Data is retreived from the transmit buffer. Upon
    retrieval, the buffer index is decremented.

    \return tail data byte
*/
uint8_t usart0_transmit_buffer_remove(void);

/** \ingroup usart

    \brief Gets the transmit buffer count
	 
    \return Transmit buffer count.
*/
uint8_t usart0_transmit_buffer_inuse_count(void);

/** 
	\ingroup usart

	\brief Transmit buffer counter initialization

	\return Transmit buffer size minus receive buffer count
*/
uint8_t usart0_transmit_buffer_free_count(void);

/** 
	\ingroup usart

	\brief Looks at a number of bytes of data in the transmit buffer

	\param *buf pointer a buffer to hold the bytes requested
	\param count The number of bytes to look at.

	\return Total bytes read
*/
uint8_t usart0_transmit_buffer_peek(uint8_t *buf, uint8_t count);

/** 
	\ingroup usart

	\brief 	Looks at the tail byte of data in the Transmit buffer

	\return Transmit buffer tail byte
*/
uint8_t usart0_transmit_peek(void);



/** 
	\ingroup usart

	\brief This clear function will reset the receive buffer head_index
	and tail_index to 0. The count value is also set to 0. A memset command 
	is used to reset a particular area in memory as well.

*/
void usart0_receive_buffer_clear(void);

/** 
	\ingroup usart

	\brief Adds the byte 'c' to the receive buffer and returns
	True if it was able to add the byte, False otherwise.
  
    \note Data added will be one value less than the size
    of the defined receive buffer. An example of this is a buffer
    size of [10] will only allow 9 values to be added into the buffer
	
	\param c byte to add
	\return boolean result of attempt to add byte
	
*/
bool usart0_receive_buffer_insert(uint8_t c);

/** \ingroup usart

    \brief Data is retreived from the receive buffer. Upon
    retrieval, the buffer index is decremented.

    \return tail data byte
*/
uint8_t usart0_receive_buffer_remove(void);

/** \ingroup usart

    \brief Gets the receive buffer count
	 
    \return receive buffer count.
*/
uint8_t usart0_receive_buffer_inuse_count(void);

/** 
	\ingroup usart

	\brief Receive buffer counter initialization

	\return receive buffer size minus receive buffer count
*/
uint8_t usart0_receive_buffer_free_count(void);

/** 
	\ingroup usart

	\brief Looks at a number of bytes of data in the receive buffer

	\param *buf pointer a buffer to hold the bytes requested
	\param count The number of bytes to look at.

	\return Total bytes read
*/
uint8_t usart0_receive_buffer_peek(uint8_t *buf, uint8_t count);

/** 
	\ingroup usart

	\brief 	Looks at the tail byte of data in the receive buffer

	\return Receive buffer tail byte
*/
uint8_t usart0_receive_peek(void);


/** 
	\ingroup usart

	\brief  Restores registers to datasheet default valuse

*/
void usart0_uninit(void);


//
// defines
//


#define usart_baudrate_to_setting(f_cpu, baud)		(uint16_t)(((uint32_t)(f_cpu) / ((uint32_t)(baud) * (uint32_t)16)) - 1)

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


#define usart0_mode(x)      (UART_CONTROL_STATUS_REG_C = (UART_CONTROL_STATUS_REG_C & (uint8_t)~((1<<UART_MODE_SELECT_0)|(1<<UART_MODE_SELECT_1))) | (uint8_t)((x) << UART_MODE_SELECT_0))

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

//void usart0_init(usart_mode_t mode, uint32_t baud, uint8_t databits, uint8_t stopbits, usart_parity_t parity, flow_control_t flow_control);

void usart0_baud_set(uint32_t baudrate, uint32_t freq_cpu);
void usart0_parity_set(usart_parity_t parity);
void usart0_flow_control_set(usart_flow_control_t flow_control);

void usart0_transmit_check(void);

void usart0_buffer_clear(ring_t *ring);
bool usart0_buffer_insert(ring_t *ring, uint8_t c);
uint8_t usart0_buffer_remove(ring_t *ring);

uint8_t usart0_buffer_inuse_count(ring_t *ring);
uint8_t usart0_buffer_peek(ring_t *ring, uint8_t *buf, uint8_t count);
uint8_t usart0_buffer_free_count(ring_t *ring);

//#endif
#endif


















