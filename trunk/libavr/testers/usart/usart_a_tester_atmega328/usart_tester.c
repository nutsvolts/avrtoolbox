// Test line added to check repository
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
 


/*


TODO:
1. In main, copy the doxy tests and use as comments for actual tests.
2. Link functions in doxy with actual functions



*/


/**
	\ingroup usart

	\brief Test the usart module functions exposed by the API


	<B>The USART Driver Library Functional Requirements Specification:</B>
	1.	Initialization of all the parameters.
	2.	Initialization using variable baudrate and common defaults for all other parameters.
	3.	Termination of USART and restoration the default register values.
	4.	Telling if received data is available.
	5.	Input and output of char data type.
	6.	Input and output of uint8_tstring data type.
	7.	Input and output of string data type.
	8.  Output via the C Standard Library printf function.
	
	<B>Functions that meet the requirements and are exposed in the API:</B><code>
	1.	Initialization of all the parameters.
	void usart0_init (uint32_t baud, uint32_t freq_cpu, usart_mode_t mode, usart_databits_t databits, usart_stopbits_t stopbits, usart_parity_t parity, usart_flow_control_t flow_control)
	
	2.	Initialization using variable baudrate and common defaults for all other parameters.
	void usart0_init_baud (uint32_t baud)
	
	3.	Termination of USART and restoration the default register values.
	void usart0_uninit (void)
	
	4.	Telling if received data is available.
	bool usart0_available (void)
	
	5.	Input and output of char data type.
	char usart0_get_char()
	void usart0_put_char(char c)
	
	6.	Input and output of uint8_tstring data type.
	uint8_t usart0_get_byte()
	void usart0_put_byte(uint8_t b)
	
	7.	Input and output of string data type.
	bool usart0_put_pgme string(char *str)
	bool usart0_put_string(char *str)
	
	8.  Output via the C Standard Library printf function.
	int usart0_put_char (char c, FILE *stream)
	int usart0_put_char (char c, FILE *stream)
	
	<B>Test is passed if:</B>
	1.	Initialization of all the parameters.
	Pass if usart0_init() initialize a session allowing sending and receiving of characters to a PC terminal program.

	2.	Initialization using variable baudrate and common defaults for all other parameters.
	Pass if usart0_init_baud() initialize a session allowing sending and receiving of characters to a PC terminal program.

	3.	Termination of USART and restoration the default register values.
	Pass assumed if function uses techniques known to set register bits to set the usart bits to the default values.

	4.	Telling if received data is available.
	Pass if this function can be used in a while loop to monitor input characters and ping back those characters.

	5.	Input and output of char data type.
	Pass if demonstrated via a PC terminal.

	6.	Input and output of string data type.
	Pass if demonstrated via a PC terminal.

	7.	Input and output of string data type.
	Pass if demonstrated via a PC terminal.

	8.  Output via the C Standard Library printf function.
	Pass if the avrlibc simple implementation of printf works according to that manual.
	

	<B>Functions exposed in the API</B>
	<code>
	void usart0_init (uint32_t baud, uint32_t freq_cpu, usart_mode_t mode, usart_databits_t databits, usart_stopbits_t stopbits, usart_parity_t parity, usart_flow_control_t flow_control)
	void usart0_init_baud (uint32_t baud)
	void usart0_uninit (void)
	bool usart0_available (void)
	char usart0_get_char()
	void usart0_put_char(char c)
	uint8_t usart0_get_byte()
	void usart0_put_byte(uint8_t b)
	bool usart0 _put_string_P(char *str)
	bool usart0 _put_string(char *str) 	
	int usart0_put_char (char c, FILE *stream)
	int usart0_put_char (char c, FILE *stream)
	</endcode>


	<B>Support Functions not in API</B>
	These functions are built on the ring module and underlying code is tested there.
	<code>
	void 	usart0_transmit_buffer_clear (void)
	bool 	usart0_transmit_buffer_insert (uint8_t c)
	uint8_t usart0_transmit_buffer_remove (void)
	uint8_t usart0_transmit_buffer_inuse_count (void)
	uint8_t usart0_transmit_buffer_free_count (void)
	uint8_t usart0_transmit_buffer_peek (uint8_t *buf, uint8_t count)
	void 	usart0_receive_buffer_clear (void)
	bool 	usart0_receive_buffer_insert (uint8_t c)
	uint8_t usart0_receive_buffer_remove (void)
	uint8_t usart0_receive_buffer_inuse_count (void)
	uint8_t usart0_receive_buffer_free_count (void)
	uint8_t usart0_receive_buffer_peek (uint8_t *buf, uint8_t count)
	</code>

*/


#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 


//include to use delay function
#include "c:\avrtoolbox\libavr\source\general\util\util.h"


// This is a program memory string defined outside any function
// Used for testing sending a program string in test 7 below
const char pgm_str1[] PROGMEM =  "This is a program memory string defined outside any function.\r";




int main(void)
{

/* Test 1.	Initialization of all the parameters.
	Pass if usart0_init() initialize a session allowing sending and receiving of characters to a PC terminal program.
*/

/*	// PASSED
	// Modem parameters used by common serial connections
	usart_mode_t mode = usart_mode_asynchronous;
	uint8_t databits = 8;
	uint8_t stopbits = 1;
	usart_parity_t parity = parity_none;
	usart_flow_control_t flow_control = flow_none;

	usart0_init(57600, F_CPU, mode,  databits, stopbits, parity, flow_control);
*/

<<<<<<< .mine
/* Test 2.	Initialization using variable baudrate and common defaults for all other parameters.
	Pass if usart0_init_baud() initialize a session allowing sending and receiving of characters to a PC terminal program.

	// PASSED
*/	// Leave in code since the function is used by remaining tests
=======
<<<<<<< .mine
/* Test 2.	Initialization using variable baudrate and common defaults for all other parameters.
	Pass if usart0_init_baud() initialize a session allowing sending and receiving of characters to a PC terminal program.

	// PASSED
*/	// Leave in code since the function is used by remaining tests
=======
/* Test 2.	Initialization using variable baudrate and common defaults for all other parameters.
	Pass if usart0_init_baud() initialize a session allowing sending and receiving of characters to a PC terminal program.

	// PASSED
*/	// Leave in code since the function is used by remaining tests
// NOTE: this is tested for the Butterfly which will set the baud to 19200 regardless of what you put here.
>>>>>>> .r100
>>>>>>> .r101
	usart0_init_baud(57600);


<<<<<<< .mine
	// Debug test and track versions
	uint8_t str[] = { 'H','o','w','d','y','7','2','\0'};
=======
<<<<<<< .mine
	// Debug test and track versions
	uint8_t str[] = { 'H','o','w','d','y','7','2','\0'};
=======
<<<<<<< .mine
	// Debug test and track versions
	uint8_t str[] = { 'H','o','w','d','y','7','3','\0'};
=======
	// Debug test and track versions
	uint8_t str[] = { 'H','o','w','d','y','7','4','\0'};
>>>>>>> .r97
>>>>>>> .r100
>>>>>>> .r101

	int i = 0;

	while( (str[i] != '\0'))
	{
		usart0_transmit_buffer_insert(str[i++]);
	}
	// Send a new line
	usart0_transmit_buffer_insert('\r');
	
	//usart0_send_buffer();
	usart0_send();


/* Test 3.	Termination of USART and restoration the default register values.
	Pass assumed if function uses techniques known to set register bits to set the usart bits to the default values.
*/
	// This test is deferred

/* Test 4.	Telling if received data is available.
	Pass if this function can be used in a while loop to monitor input characters and ping back those characters.
*/
/* Test 5. Input and output of char.
	Pass if demonstrated via a PC terminal.
*/

/*	// Tests 4 and 5 - PASSED
	char *c;

	while(1)
	{
		if(usart0_available())
		{
			if(usart0_get_char(c)) usart0_put_char(*c);
			usart0_send(); // Starts buffer tansmission
		}
	}
*/

/* Test	6.	Input and output of string data type.
	Pass if demonstrated via a PC terminal.
*/
/*	// PASSED - Tested with Developer Terminal sending bytes in hex mode
	uint8_t *b;

	while(1)
	{
		if(usart0_available())
		{
			if(usart0_get_byte(b)) usart0_put_byte(*b);
			usart0_send();  // Starts buffer tansmission
		}
	}
*/

/* Test	7.	Input and output of string data type.
	Pass if demonstrated via a PC terminal.
	NOTE: These function get and put to the buffers. Sending them requires a call to usart0_send();

*/
/*	PASSED
	// Test with const char array intialized outside any function
	// const char pgm_str1[] PROGMEM =  "This is a program memory string defined outside any function.\r";
	usart0_put_pgm_string(pgm_str1);
	usart0_send();

	// Test with string intialized in a function
	usart0_put_pgm_string(PSTR("This is a program memory string using PSTR within a function.\r"));
	usart0_send();

	usart0_put_string("Put a string from RAM.\r");
	usart0_send();
*/
/* Test	8.  Output via the C Standard Library printf function.
	Pass if the avrlibc simple implementation of printf works according to that manual.
*/

	printf("printf Hello, World! - from RAM\r");
	printf_P(PSTR("printf Hello, World! - from program memory\r"));

	// Test to see if you can choke it.
	printf("Hello, World!\n");
	printf("Now is the time for all good men to come to the aid of their country.\n");
	printf("The quick brown fox jumjped over the lazy dog.\n");
	printf("Hello, World!\n");
	printf("Now is the time for all good men to come to the aid of their country.\n");
	printf("The quick brown fox jumjped over the lazy dog.\n");
	printf("Hello, World!\n");
	printf("Now is the time for all good men to come to the aid of their country.\n");
	printf("The quick brown fox jumjped over the lazy dog.\n");


//	while(1);
	uint8_t count = 0;

	while(1)
	{
		// Ping back received values
		if(usart0_available())//usart0_receive_buffer_inuse_count())
		{
			count = usart0_receive_buffer_inuse_count();

			for(int i = 0 ; i < count; i++)
			{
				usart0_transmit_buffer_insert(usart0_receive_buffer_remove());
			}	
			usart0_send();
			
		}
	}

}


