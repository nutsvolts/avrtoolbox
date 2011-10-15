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
#include "C:\avrtoolbox\libavr\source\general\util\bitwise.h"

#include "c:\avrtoolbox\libavr\source\general\ring\ring.h"

//JWP 6/16/11 The Butterfly requires special code for clock and baud
#if defined(__AVR_ATmega169__) // Assume Butterfly
#include "c:\avrtoolbox\libavr\source\board\butterfly\butterfly.h" //"libserial\serial.h"
#endif


//
// Create the buffers
//

ring_t usart0_receive_ring;
#define USART0_RECEIVE_BUFFER_LEN   64
uint8_t usart0_receive_buffer[USART0_RECEIVE_BUFFER_LEN];

ring_t usart0_transmit_ring;
#define USART0_TRANSMIT_BUFFER_LEN  128
uint8_t usart0_transmit_buffer[USART0_TRANSMIT_BUFFER_LEN];


// JWP 6/16/11 flags for revised transmissio logic
volatile uint8_t usart_tx_ready_flag;
volatile uint8_t usart_buffered_tx_flag;

// TODO MOVE AND PUT DOXYGEN COMMENTS
// JWP 6/16/11 added to change transmission logic.
// this function waits until a pending transmission is complete
// then sends a byte. If the usart_buffered_TX_flag is set true
// then the ISR continues to send until the buffer is empty, otherwise
// the ISR just sends the byte. 
//void usart0_send_byte(void);
void usart0_send_buffer(void);

// AVRStudio crashed when I was converting from the above to the below
// TODO FIND AND FIX




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

/** 
	\ingroup usart

	\brief  Restores registers to datasheet default valuse

	Example:
	\code
	// Stop the madness
	usart0_uninit();
	\endcode

*/
void usart0_uninit(void);





/** \ingroup usart

    \brief Initiates the interrupt based transmission of the buffer
	 NOTE: All of the put or insert function only load a byte into the transmission buffer.
	 This function must be called to start the transmission.

	Example:
	\code
	// Put a string from program memory into the transmit buffer
	usart0_put_pgm_string(pgm_str1);
	// Initiate buffer transmission
	usart0_send();
	\endcode
*/
void usart0_send(void);


/** \ingroup usart

    \brief Gets the receive buffer count
	This can be used as a boolean since if the buffer is empty it returns 0.

	Example:
	\code
	char *c;

	if(usart0_available())
	{
		if(usart0_get_char(c)) usart0_put_char(*c);
		usart0_send(); // Starts buffer tansmission
	}
	\endcode
	 
    \return receive buffer count.
*/
bool usart0_available(void);


/** \ingroup usart

    \brief Puts a character into the usart transmit buffer.

	\code
	char *c;
	
	if(usart0_get_char(c)) usart0_put_char(*c);
	\endcode
	 
    \param c the char to be sent.

*/
void usart0_put_char(char c);

/** \ingroup usart

    \brief Gets a character from the usart receive buffer.

	\code
	char *c;
	
	if(usart0_get_char(c)) usart0_put_char(*c);
	\endcode

	 
	\param *c pointer to a character to put the buffer value

    \return character from the buffer

*/
bool usart0_get_char(char *c);

/** \ingroup usart

    \brief Puts a uint8_t byte into the usart transmit buffer.

	\code
	uint8_t *b;

	if(usart0_get_byte(b)) usart0_put_byte(*b);
	\endcode

	 
    \param b the  to be sent.

*/
void usart0_put_byte(uint8_t b);

/** \ingroup usart

    \brief Gets a uint8_t byte from the usart receive buffer.
	
	\param *b pointer to a uint8_t byte to put the buffer value

    \return uint8_t byte from the buffer

	\code
	uint8_t *b;

	if(usart0_get_byte(b)) usart0_put_byte(*b);
	\endcode
	 

*/
bool usart0_get_byte(uint8_t *b);


/** \ingroup usart

    \brief Puts a '\0' terminated string into the transmit buffer.
	To prevent buffer overrun, the string is automatically truncated 
	with '\0'if it exceeds USART0_TRANSMIT_BUFFER_LEN - 1.
	 
	\param *str pointer to a char buffer 

*/
void usart0_put_string(char *str); 


/** \ingroup usart	

	\brief Loads a string from program memory into the transmit buffer.
	
	\param pointer to a constant character string

	Example:
	\code
	// Define string outside any function
	const char pgm_str1[] PROGMEM =  "This is a program memory string defined outside any function.\r";
	...
	// Put the program memory string into the transmit buffer
	usart0_put_pgm_string(pgm_str1);
	// Transmit it
	usart0_send();

	// Use with a string intialized in the function
	usart0_put_pgm_string(PSTR("This is a program memory string using PSTR within a function.\r"));
	usart0_send();

	\endcode

*/ 
void usart0_put_pgm_string(const char *); 


/** 
	\ingroup usart

	\brief This clear function will reset the transmit buffer head_index
	and tail_index to 0. The count value is also set to 0. A memset command 
	is used to reset a particular area in memory as well.

	Example:
	\code
	void end_this()
	{
		usart0_transmit_buffer_clear();
	}
	\endcode

*/
void usart0_transmit_buffer_clear(void);

/** 
	\ingroup usart

	\brief Adds the byte 'c' to the transmit buffer and returns
	True if it was able to add the byte, False otherwise.
  
    \note Data added will be one value less than the size
    of the defined receive buffer. An example of this is a buffer
    size of [10] will only allow 9 values to be added into the buffer
	
	Example:
	\code
	\\ Add a string termination character
	usart0_transmit_buffer_insert('\0');
	\endcode

	\param c byte to add
	\return boolean result of attempt to add byte
	
*/
bool usart0_transmit_buffer_insert(uint8_t c);


/** \ingroup usart

    \brief Data is retreived from the transmit buffer. Upon
    retrieval, the buffer index is decremented.

	Example:
	\code
	char c;

	c = usart0_transmit_buffer_remove();
	\endcode

    \return tail data byte
*/
uint8_t usart0_transmit_buffer_remove(void);

/** \ingroup usart

    \brief Gets the transmit buffer count
	 
	Example:
	\code
	if(usart0_transmit_buffer_inuse_count())// Is there data in the buffer?
	{
		// Send next byte in the buffer.
 	      UART_DATA_REG = ring_remove(&usart0_transmit_ring);
	}
	\endcode

    \return Transmit buffer count.
*/
uint8_t usart0_transmit_buffer_inuse_count(void);

/** 
	\ingroup usart

	\brief Transmit buffer counter initialization

	Example:
	\code
	uint8_t free;

	free = usart0_transmit_buffer_free_count();	
	\endcode

	\return Transmit buffer size minus receive buffer count
*/
uint8_t usart0_transmit_buffer_free_count(void);

/** 
	\ingroup usart

	\brief Looks at a number of bytes of data in the transmit buffer

	Example:
	\code
	uint8_t myBuf[10];
	uint8_t toGet = 10;
	uint8_t got = 0;

	got = usart0_transmit_buffer_peek(myBuf, toGet);
	if(got != get)
	{
		\\ didn't get requested bytes
	}
	else
	}
		\\got requested bytes 
		...
	}
	\endcode

	\param *buf pointer a buffer to hold the bytes requested
	\param count The number of bytes to look at.

	\return Total bytes read
*/
uint8_t usart0_transmit_buffer_peek(uint8_t *buf, uint8_t count);


/** 
	\ingroup usart

	\brief This clear function will reset the receive buffer head_index
	and tail_index to 0. The count value is also set to 0. A memset command 
	is used to reset a particular area in memory as well.

	Example:
	\code
	void end_this()
	{
		usart0_receive__buffer_clear();
	}
	\endcode

*/
void usart0_receive_buffer_clear(void);


/** \ingroup usart

    \brief Data is retreived from the receive buffer. Upon
    retrieval, the buffer index is decremented.

	Example:
	\code
	\\ Remove a byte from the receive buffer and put it in the transmit buffer
	sart0_transmit_buffer_insert(usart0_receive_buffer_remove());
	\endcode

    \return tail data byte

*/
uint8_t usart0_receive_buffer_remove(void);

/** \ingroup usart

    \brief Gets the receive buffer count

    \return receive buffer count.

	Example:
	\code
	while(1)
		// Ping back received values
		if(usart0_available())
		{
			count = usart0_receive_buffer_inuse_count();

			for(int i = 0 ; i < count; i++)
			{
				usart0_transmit_buffer_insert(usart0_receive_buffer_remove());
			}	
			usart0_send();		
		}
	}
	\endcode
	 
*/
uint8_t usart0_receive_buffer_inuse_count(void);

/** 
	\ingroup usart

	\brief Receive buffer counter initialization

	Example:
	\code
	uint8_t free;

	free = usart0_receive_buffer_free_count();	
	\endcode

	\return receive buffer size minus receive buffer count
*/
uint8_t usart0_receive_buffer_free_count(void);

/** 
	\ingroup usart

	\brief Looks at a number of bytes of data in the receive buffer

	Example:
	\code
	uint8_t peekByte = 0;

	peekByte = usart0_receive_peek();
	\endcode

	\param *buf pointer a buffer to hold the bytes requested
	\param count The number of bytes to look at.

	\return Total bytes read
*/
uint8_t usart0_receive_buffer_peek(uint8_t *buf, uint8_t count);


// These functions are used by API functions but not exposed in the API
void usart0_buffer_clear(ring_t *ring);
bool usart0_buffer_insert(ring_t *ring, uint8_t c);
uint8_t usart0_buffer_remove(ring_t *ring);
uint8_t usart0_buffer_inuse_count(ring_t *ring);
uint8_t usart0_buffer_peek(ring_t *ring, uint8_t *buf, uint8_t count);
uint8_t usart0_buffer_free_count(ring_t *ring);


#endif


















