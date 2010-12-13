/*****************************************************
	serial_test.c Joe Pardue November 8, 2010
	Location: avrtoolbox\Libraries\Elementary\serial_tester
******************************************************/

/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2010, Smiley Micros, All rights reserved.
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
 *  - Neither the name of the Smiley Micros nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission. 
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

#include <stdlib.h>  // for rand() and itoa()
#include <inttypes.h>

#define DEBUG

// Pick one 
// TODO: REQUIRED FOR WHICH LIBRARY?
#define BUTTERFLY
//#define ARDUINO
//#define BEAVR

//volatile uint8_t usart_flag;
 

#include "serial.h"
#include "fifo.h"
#include "usart.h"


#if defined (DEBUG)
#define F_CPU 1000000L
#include <util\delay.h>
#endif


int main(void)
{
	serial_begin(19200);

	// Who are you?
	serial_printf("serial_test 1.18\r",0);


/*	serial_printf("This is a byte %d\r",22);

	char c = 'A';
	uint8_t d = 11;
	uint8_t x = 0x22;
	uint16_t X = 0x1122;

	serial_printf("Test character: %c\r", c);
	serial_printf("Test decimal integer: %d\r", d);
	serial_printf("Test hexadecimal integer: %x\r", x);
	serial_printf("Test 16-bit hexadecimal integer: %x\r", X);
*/

	while(1)
	{

		// First test - usart receive ISR pings byte back to sender.

		// Second test - usart sets flag 
/*		if(usart_flag)
		{
			// Ping what was received
			serial_printf("Got a byte.\n",0);				
			usart_flag = 0; // Reset flag
		}

		// Third test - usart loads fifo
		if(serial_available())
		{
			serial_printf("Got: %c\n",serial_read());
		}
*/
		_delay_ms(500);

		// Test baudrates:
		





	}

}// main()







	// Create an instance of the cmd_packet
//	struct cmd_packet cmd;


                  /*	// Forever (or at least until 1 changes meaning.
	while(1)
	{
		// Check to see if a cmd_packet has arrived
		uint8_t cmd_packet_status = (find_next_packet(&cmd));
		
		// Is it valid?
		if(cmd_packet_status == VALID_CMD_PACKET )
		{
			#if defined (DEBUG)
			printf_P(PSTR("find_next_packet(&cmd) = VALID_CMD_PACKET.\r"));
			show_cmd_packet(&cmd);
			#endif

			// Process the cmd_packet
			// Parse the commands
			switch(cmd.command)
			{
				case(0x30):
					start_monitoring();
					break;
				case(0x31):
					//send_temperature();
					break;
				case(0x32):
					//set_temp_fudge(cmd.data0);
					break;
				case(0x33):
					stop_monitor();
					break;
				case(0x34):
					send_entries_count();
					break;
				case(0x35):
					send_entries(cmd.data0,cmd.data1,cmd.data2);
					break;
				case(0x36):
					send_inception_bytes();
					break;
				case(0x37):
					//send_light();
					break;
				case(0x38):
					//set_light_change(cmd.data0,cmd.data1);
					break;
				default:
					cmd_error(cmd.command,cmd.data0,cmd.data1,cmd.data2,cmd.data3);
					break;
		
			}// switch(cmd.command)			// TODO DEAL WITH ACK
			
		}//if(cmd_packet_status == VALID_CMD_PACKET )
		else if(cmd_packet_status == INVALID_CMD_PACKET )
		{
			#if defined (DEBUG)
			printf_P(PSTR("find_next_packet(&cmd) = INVALID_CMD_PACKET.\r"));
			#endif

			// Send NAK TODO
		}// else if(cmd_packet_status == INVALID_CMD_PACKET )
		else if(cmd_packet_status == NOT_ENOUGH_DATA )
		{
			#if defined (DEBUG)
			printf_P(PSTR("find_next_packet(&cmd) = NOT_ENOUGH_DATA.\r"));
			#endif
		}// else if(cmd_packet_status == NOT_ENOUGH_DATA )
		

		// Gimme some time to think
		#if defined (DEBUG)
		_delay_ms(10000);
		#endif
	}// while(1)
*/

/*
void receive_packet(void);

#define PACKET_SIZE 6

struct cmd_packet
{
	uint8_t command;
	uint8_t data0;
	uint8_t data1;
	uint8_t data2;
	uint8_t data3;
	uint8_t checksum;
};

uint8_t find_next_packet(struct cmd_packet *c);
void set_cmd_packet_to_zero(struct cmd_packet *c);
void show_cmd_packet(struct cmd_packet *c);

void receive_packet(void);
void start_monitoring(void);

void stop_monitor(void);
void send_entries_count(void);
void send_entries(uint8_t, uint8_t, uint8_t);
void send_inception_bytes(void);
void cmd_error(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);


#define LOW_CMD 0x30
#define HIGH_CMD 0x38

#define INVALID_CMD_PACKET 0
#define VALID_CMD_PACKET 1
#define NOT_ENOUGH_DATA 2
*/



/*
// Takes a pointer to a cmd_packet structure
// if it gets a correctly formed cmd_packet it
// will load the cmd_packet pointer c with the 
// values and return 1. If it doesn't, then it
// loads the cmd_packet with zeros and returns 0
uint8_t find_next_packet(struct cmd_packet *c)
{
	uint8_t buffer_size, temp;
	uint8_t command,data0,data1,data2,data3,checksum;

	// Get the number of bytes available
	buffer_size = serial_available();

	// If there are more than a packet, then check for validity
	if(buffer_size >= PACKET_SIZE)
	{ 
		// Get the first PACKET_SIZE group
		temp = 0;

		// Find a valid command
		// Only look until you've either found a command with 
		// PACKET_SIZE - 1 remaining
		for(int i = 0 ; i < buffer_size ; i++ )
		{		
			command = serial_read_at_index(i);

			#if defined (DEBUG)
			printf("find_next_packet got: %X\r",command);
			#endif

			// Is it a command?
			if( (command >= LOW_CMD) & (command <= HIGH_CMD) )
			{
				// Check for a valid packet
				#if defined (DEBUG)
				printf("Identified possible packet command: %X\r",command);
				#endif

				// Load the rest of the variables
				data0 = serial_read_at_index(i+1);
				data1 = serial_read_at_index(i+2);
				data2 = serial_read_at_index(i+3);
				data3 = serial_read_at_index(i+4);
				checksum = serial_read_at_index(i+5);

				// Is the checksum valid
				temp = command;
				temp += data0;
				temp += data1;
				temp += data2;
				temp += data3;
	
				// If it is a good packet load it and return 1
				if( temp == checksum)
				{ 
					#if defined(DEBUG)
					printf("Checksum GOOD\r");
					#endif

					// Load the cmd_packet
					c->command = command;
					c->data0 = data0;
					c->data1 = data1;
					c->data2 = data2;
					c->data3 = data3;
					c->checksum = checksum;

					// Got a valid cmd_packet so flush the buffer
					serial_flush();

					#if defined(DEBUG)
					printf_P(PSTR("find_next_packet: about to return 1st VALID_CMD_PACKET \r"));
					#endif

					return VALID_CMD_PACKET;

				}//if( temp == checksum)
				else // it isn't a good packet so move to next byte
				{
					#if defined(DEBUG)
				 	printf("Checksum BAD\r");
					#endif


					// Clear the cmd_packet
					//set_cmd_packet_to_zero(c);


			// Advance the cmd buffer index
			 serial_read();

					#if defined(DEBUG)
					printf_P(PSTR("find_next_packet: about to return INVALID_CMD_PACKET \r"));
					#endif

					return INVALID_CMD_PACKET;
				}//else temp != checksum	


				// Reset the buffer to the next byte
				

			}//if( (command >= LOW_CMD) & (command <= HIGH_CMD) )
		}//for(int i = 0 ; i < buffer_size ; i++ )
		
		#if defined(DEBUG)
		printf_P(PSTR("find_next_packet: about to return 2nd VALID_CMD_PACKET \r"));
		#endif

		return VALID_CMD_PACKET;
	}//if(buffer_size >= PACKET_SIZE)
	else // Less than a packet so bail
	{
		set_cmd_packet_to_zero(c);

		#if defined(DEBUG)
		printf_P(PSTR("find_next_packet: valid packet NOT found\r"));
		#endif

		return NOT_ENOUGH_DATA;
	}//else Less than a packet so bail

	#if defined(DEBUG)
	printf_P(PSTR("find_next_packet ERROR - shouldn't ever be here!\r"));
	#endif
}

// Set a cmd_packet to zero
void set_cmd_packet_to_zero(struct cmd_packet *c)
{
	c->command = 0;
	c->data0 = 0;
	c->data1 = 0;
	c->data2 = 0;
	c->data3 = 0;
	c->checksum = 0;
}

void show_cmd_packet(struct cmd_packet *c)
{
	printf_P(PSTR("show_cmd_packet:\r"));
	printf("command: %X\r",c->command);
	printf("data0: %X\r",c->data0);
	printf("data1: %X\r",c->data1);
	printf("data2: %X\r",c->data2);
	printf("data3: %X\r",c->data3);
	printf("checksum: %X\r",c->checksum);
}

void start_monitoring(void)
{
	#if defined(DEBUG) 
		printf("start_monitoring\r");
	#endif
}


void stop_monitor(void)
{
	#if defined(DEBUG)
		printf("stop_monitoring\r");
	#endif
}


void send_entries_count()
{
	#if defined(DEBUG)
		printf("send_entries_count\r");
	#endif
}
void send_entries(uint8_t data1, uint8_t data2, uint8_t data3)
{
	#if defined(DEBUG)
		printf("send_entries\r");

		char temp[]= {'\0','\0','\0','\0','\0'};

		itoa(data1, temp, 16);
		printf("data1: %X\r",temp);
		itoa(data2, temp, 16);
		printf("data2: %X\r",temp);
		itoa(data3, temp, 16);
		printf("data3: %X\r",temp);
	#endif

}
void send_inception_bytes()
{
	#if defined(DEBUG)
		printf("send_inception_bytes\r");
	#endif

}

void cmd_error(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
	#if defined(DEBUG)
		char temp[]= {'\0','\0','\0','\0','\0'};

		printf("Command Error: \r");
		printf("cmd: ");
		itoa(cmd, temp, 16);
		printf(temp);
		printf("\rdata1 ");
		itoa(data1, temp, 16);
		printf(temp);
		printf("\rdata2 ");
		itoa(data2, temp, 16);
		printf(temp);
		printf("\rdata3 ");
		itoa(data3, temp, 16);
		printf(temp);
		printf("\rdata4 ");
		itoa(data4, temp, 16);
		printf(temp);
		printf("\r");
	#endif
}*/
