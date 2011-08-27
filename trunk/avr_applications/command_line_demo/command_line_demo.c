#/*
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
 
// This code uses the the library libavr_atmega328_002a located at
// c:\avrtoolbox\libavr\librarian\atmega328

#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 
#include "c:\avrtoolbox\libavr\source\general\util\util.h" 

#include <string.h>
#include <ctype.h>

// Arbitrary - keep commands and data under BUFFLENGTH characters + '\n'
#define BUFFLENGTH 20

#define TERMINATOR '!'
#define DELIMITER ','
#define SEPARATOR ' '

void command0(uint16_t data);
void command1(uint16_t data);
void command2(uint16_t data);
void command3(uint16_t data);
void command4(uint16_t data);
void command5(uint16_t data);
void command6(uint16_t data);
void help(uint16_t data);

void parse_command(void);
bool call_command(const char* command, const char* data);

// Create an array of command names in program memory
typedef struct PROGMEM
{
	PGM_P PTEXT; // pointer to text in program memory
	void (*PFUNC)(uint16_t data); // Pointer to a function
}CMDS;

//command, function pointer
const CMDS COMMANDS[] PROGMEM = {
{"COMMAND0",command0},
{"COMMAND1",command1},
{"COMMAND2",command2},
{"COMMAND3",command3},
{"COMMAND4",command4},
{"COMMAND5",command5},
{"COMMAND6",command6},
{"HELP",help},
{0,NULL}
};


int main (void)
{
	usart0_init_baud(57600);

	printf_P(PSTR("command_line_demo 028\n"));
   
	while(1)
	{
		if(usart0_available())//usart0_receive_buffer_inuse_count())
		{
			// Load until terminator received
			if(strchr((const char*)usart0_receive_buffer,TERMINATOR))
			{
				parse_command();
				usart0_receive_buffer_clear();
			}
		}
	}

}

void command0(uint16_t data)
{
	printf_P(PSTR("command0 - data = %u\n"),data);
}

void command1(uint16_t data)
{
	printf_P(PSTR("command1 - data = %u\n"),data);
}

void command2(uint16_t data)
{
	printf_P(PSTR("command2 - data = %u\n"),data);
}

void command3(uint16_t data)
{
	printf_P(PSTR("command3 - data = %u\n"),data);
}
void command4(uint16_t data)
{
	printf_P(PSTR("command4 - data = %u\n"),data);
}
void command5(uint16_t data)
{
	printf_P(PSTR("command5 - data = %u\n"),data);
}
void command6(uint16_t data)
{
	printf_P(PSTR("command6 - data = %u\n"),data);
}

/*
COMMAND - DATATYPE - SUMMARY\n
COMMAND1 - uint16_t data - Brief description of the command\n
COMMAND2 - uint16_t data - Brief description of the command\n
COMMAND3 - uint16_t data - Brief description of the command\n
COMMAND4 - uint16_t data - Brief description of the command\n
COMMAND5 - uint16_t data - Brief description of the command\n
HELP - no data - Display the help list\n"
*/
const char HELP[] PROGMEM = "\nCOMMAND - DATATYPE - SUMMARY\nCOMMAND1 - uint16_t data - Brief description of the command\nCOMMAND2 - uint16_t data - Brief description of the command\nCOMMAND3 - uint16_t data - Brief description of the command\nCOMMAND4 - uint16_t data - Brief description of the command\nCOMMAND5 - uint16_t data - Brief description of the command\nHELP - no data - Display the help list\n";

void help(uint16_t data)
{
	printf_P(HELP);
}


bool call_command(const char* command, const char* data)
{
	bool valid = false;

	// Is it a command?
    void (*p_func)(uint16_t);

	int i;
	// Loop terminates on the 0 entry for the command
	for (i=0; pgm_read_word(&COMMANDS[i].PTEXT); i++)
	{
		if( !strcmp( (char*)pgm_read_word(&COMMANDS[i].PTEXT),command) )
		{
			// Get the function and call it
		    p_func = (PGM_VOID_P)pgm_read_word(&COMMANDS[i].PFUNC); 
			p_func(atoi(data)); 
			valid = true;
		}
	}

	if(valid)
	{
		return true;
		}
	else 
	{
		printf_P(PSTR("ERROR: call_command - not a command: %s\n"),command);
		return false;
	}
}


// Note: this by no means catches every possible error
void parse_command()
{
	int i = 0;
	int j = 0;
	int k = 0;

	uint8_t buf[USART0_RECEIVE_BUFFER_LEN];	

	uint8_t temp_buf[BUFFLENGTH];
	uint8_t command[BUFFLENGTH];
	uint8_t data[BUFFLENGTH];

	// Transfer to input to local buffer
	// TODO: This could cause problems if the ISR is loading new
	// data while the buffer is being transferred. FIX THIS	
	strcpy((char *)buf,(char *)usart0_receive_buffer);	

	// Just FYI
	//#define TERMINATOR '!'
	//#define DELIMITER ','
	//#define SEPARATOR ' '

	// Show each command and data
	for(i = 0; i < strlen((const char *)buf); i++)
	{
		if(buf[i] != DELIMITER)
		{
			temp_buf[j++] = buf[i];
		}
		else // Process command unit
		{
			temp_buf[j] = '\0'; // Turn it into a string
			j = 0;

			// Extract the command name
			for(j = 0; j < 20; j++)
			{
				// Validate that command is all alphabetic or numeric
				if( (temp_buf[j] != SEPARATOR))
				{
					if(isalnum(temp_buf[j]))
					{
						command[k++] = temp_buf[j];
					}
					else
					{
						printf_P(PSTR("ERROR in parse_command(): not a command - not alpha.\n"));
						return;
					}
				}
				else
				{
					command[k] = '\0';
					k = 0;
					j++;
					for(k = 0; k < 20; k++)
					{
						if(temp_buf[j] != '\0')//DELIMITER)
						{
							// Validate that the data is all digits
							if(isdigit(temp_buf[j]))
							{
								data[k] = temp_buf[j++];
							}
							else
							{
								printf_P(PSTR("ERROR in parse_command(): not a number - not digit: %c\n"),temp_buf[j]);
								return;
							}

						}
						else
						{
							data[k] = '\0';
							k = 0;
							j = 0;
							
							//Call the command - bail out if it isn't valid
							if(!call_command((const char *)command,(const char *)data))return;

							break;
						}
					}
					break;
				}
			}	
		}
	}
}


