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

#ifndef USART0_H
#define USART0_H

#include <avr/pgmspace.h> 
#include <stdio.h>



#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "bit.h"
#include "usart.h"

//#include "ring.h"
#include "c:\avrtoolbox\libavr\source\general\ring\ring.h"

usart_flow_t flow;

   // FUNCTION PROTOTYPES
void usart0_flow_in_disable(void);
void usart0_flow_in_enable(void);
void usart0_flow_out_disable(void);
void usart0_flow_out_enable(void);
#if 0
void usart0_flow_out_hw_task(void);
#endif
void usart0_transmit_check(void);

ring_t usart0_receive_ring;
#define USART0_RECEIVE_BUFFER_LEN   64
uint8_t usart0_receive_buffer[USART0_RECEIVE_BUFFER_LEN];

ring_t usart0_transmit_ring;
#define USART0_TRANSMIT_BUFFER_LEN  128
uint8_t usart0_transmit_buffer[USART0_TRANSMIT_BUFFER_LEN];

void usart0_transmit_check(void);

void usart0_buffer_clear(ring_t *ring);
bool usart0_buffer_insert(ring_t *ring, uint8_t c);
uint8_t usart0_buffer_remove(ring_t *ring);

uint8_t usart0_buffer_inuse_count(ring_t *ring);
uint8_t usart0_buffer_peek(ring_t *ring, uint8_t *buf, uint8_t count);
uint8_t usart0_buffer_free_count(ring_t *ring);

void usart0_putc(char c);



// API functions
/**
	\ingroup usart

	\brief intializes the uart parameters

	\param mode 
	/code
	typedef enum
	{
	    usart_mode_asynchronous = 0,
	    usart_mode_synchronous = 1
	} usart_mode_t;
	/endcode

	\param baud
	/code
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
	/enccode

	\param databits uint8_t Number of data bits
	/code
	typedef enum
	{
	    5-bit = 5,
	    6-bit = 6,
	    7-bit = 7,
		8-bit = 8,
		9-bit = 9
	} usart_databits_t;
	/endcode
	

	\param stopbits uint8_t Number of stop bits
	/todo - use enum typedef to be consistent
	/code
	typedef enum
	{
	    1-stopbit = 1,
	    2-stopbit = 6,
	} usart_stopbits_t;	
	/endcode

	\param parity
	/code
	typedef enum
	{
	    parity_none = 0,
		uparity_even = 1,
	    uparity_odd = 2
	} usart_parity_t;
	/endcode

	\param flow_control
	/code
	typedef enum
	{
	    flow_none = 0,
	    flow_sw = 1,
	    flow_hw = 2
	} usart_flow_control_t;
	/encode
*/
void usart0_init(uint32_t baud, uint32_t freq_cpu, usart_mode_t mode, usart_databits_t databits, usart_stopbits_t stopbits, usart_parity_t parity, usart_flow_control_t flow_control);
//void usart0_init(uint32_t baud, uint32_t freq_cpu, uint8_t *rxbuf, uint8_t *txbuf, usart_mode_t mode, usart_databits_t databits, usart_stopbits_t stopbits, usart_parity_t parity, usart_flow_control_t flow_control);
//void usart0_init(usart_mode_t mode, usart_baud_t baud, usart_databits_t databits, usart_stopbits_t stopbits, usart_parity_t parity, usart_flow_control_t flow_control, uint32_t freq_cpu);

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



//#endif
#endif





