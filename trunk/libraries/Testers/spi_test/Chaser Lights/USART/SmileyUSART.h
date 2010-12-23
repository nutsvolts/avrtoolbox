/*****************************************************
	SmileyUSART.h September 8, 2010 Joe Pardue
	Device specfic USART Definitions

	NOTE: THIS IS INCLUDE FOR DEBUG PURPOSES ONLY
	A NEW USART / PRINTF LIBRARY IS FORTH COMING
	ONE OF THESE DAYS.
******************************************************/

#ifndef SMILEY_USART_H
#define SMILEY_USART_H

#include <avr/io.h>
#include <avr/pgmspace.h> 
#include <avr/wdt.h>

#include "..\device\device.h"

/*****************************************************
	From Mike Perks, a generous AVRFreak
	 - modified quite a bit
******************************************************/
/* defines for the various USART registers */

#if defined(Butterfly)

   // ATMega with one USART 
   #define USART_BAUD_RATE_HIGH        	UBRRH
   #define USART_BAUD_RATE_LOW        	UBRRL
   #define USART_CONTROL_STATUS_REG_A	UCSRA
   #define USART_CONTROL_STATUS_REG_B	UCSRB
   #define USART_CONTROL_STATUS_REG_C	UCSRC
   #define USART_ENABLE_TRANSMITTER		TXEN
   #define USART_ENABLE_RECEIVER		RXEN
   #define USART_READY_TO_TRANSMIT		UDRE
   #define USART_TRANSMIT_COMPLETE		TXC
   #define USART_RECEIVE_COMPLETE		RXC
   #define USART_DATA_REG				UDR
   #define USART_STOP_BIT_SELECT 		USBS
   #define USART_CHARACTER_SIZE_0 		UCSZ0
   #define USART_CHARACTER_SIZE_1 		UCSZ1
   #define USART_REGISTER_SELECT		URSEL

#elif defined(BeAVR40) || defined(Arduino)

   // ATMega with two USARTs - USART 0
   #define USART_BAUD_RATE_HIGH			UBRR0H
   #define USART_BAUD_RATE_LOW			UBRR0L
   #define USART_CONTROL_STATUS_REG_A	UCSR0A
   #define USART_CONTROL_STATUS_REG_B	UCSR0B
   #define USART_CONTROL_STATUS_REG_C	UCSR0C
   #define USART_ENABLE_TRANSMITTER		TXEN0
   #define USART_ENABLE_RECEIVER		RXEN0
   #define USART_READY_TO_TRANSMIT		UDRE0
   #define USART_TRANSMIT_COMPLETE		TXC0
   #define USART_RECEIVE_COMPLETE		RXC0
   #define USART_DATA_REG				UDR0
   #define USART_STOP_BIT_SELECT		USBS0
   #define USART_CHARACTER_SIZE			UCSZ00

#else
   #error "no USART definition for MCU"
#endif

/*****************************************************
	USART function declarations	 
******************************************************/
//static void Initialization();
void uart_init(void);
void uart_send_byte( uint8_t );
//static uint8_t receiveByte( void );
void uart_send_stringP(const char *); 
void uart_send_string(const char *);
void uart_send_bit(uint8_t);

#endif
