//#include "..\devices\devices.h"
#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h"
#include "c:\avrtoolbox\libavr\source\general\util\util.h"

#define BUFFER_DELAY 20

/*! 
	\ingroup serial

	\brief Gets the number of bytes that have arrived from the serial port and are available for reading from the 128 byte buffer.

	\param none
	
	\return uint8_t bytes available in the serial receive buffer – up to 128.
	
	\code
	Example:
	void loop()
	{
		if(serial_available() > 16) 
		{
			process_serial_input();
		}
	}
	\endcode
*/
uint8_t serial_available(void);


/*! 
	\ingroup serial

	 Sets up the serial communication with the transmission data rate (baudrate).
	
	\param baudrate: 32-bit integer (uint32_t). Recommended that you only use one of the standard rates of: 300, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200.

	\return nothing
	
	\code	
	Example:
	void setup()
	{
		// Set up serial port for 57600 baud
		serial_begin(57600);
	}
	\endcode
*/
void serial_begin(uint32_t baudrate);

/*! 
	\ingroup serial

	\brief Returns the serial communications elements to their default values.


	\param None
	\return Nothing
	
	\code	
	Example:
	void shut_down()
	{
		serial_end();
		sleep();
	}
	\endcode
*/
void serial_end(void);

/*! 
	\ingroup serial

	\brief Clear out any data in the serial buffer. Subsequent calls to serial_in() or serial_available() will only return data that has arrived since the call to serial_flush().

	\param none
	
	\return nothing
	
	\code
	Example:
	// Received unknown command, restart the conversation 
	serial_out(“Unknown command: %d, flushing buffer.”, last_command);
	// Throw out everything
	serial_flush();
	\endcode

*/
void serial_flush(void);

/*! 
	\ingroup serial

	\brief Inputs incoming serial data one byte at a time, returns –1 if no data is available.

	\param none
	
	\return 8-bit signed integer (int8_t) - the first byte of incoming data or returns –1 if no data available.

	\code	
	Example:
	// Define and receive a serial byte
	int8_t myByte = serial_in();

	// Is it ‘!’
	if(myByte == ‘!’)
	{
		process_exclamation();
	}	
	\endcode
	
*/
uint8_t serial_in(void);

/*! 
	\ingroup serial

	\brief Outputs formatted data based on conversion symbols and escape character sequences contained in a string of text. 
	Syntax: serial_out(string_with_N_data_format_symbols, data1, data2, … dataN);

	\param 
	First parameter: string with data to format
	Following parameters: the data to be formatted for printing in the first parameter string.

	\return The number of characters printed or a negative number if an error occurred.
	
	\note
	Conversion symbols: 
	%c – print an ASCII character
	%s – print a character string
	%d or %i – print a decimal integer
	%x – print a hexadecimal integer. Note that we usually precede this with the characters 0x to output, for instance if the hexadecimal number is 5A, the output will be 0x5A.

	Control characters:
	\n – print a new line
	\” – print a quotation mark
	\\ - print a forward slash	
	
	\code	
	Example 1: 
	uint8_t my_char = ‘!’;
	uint8_t my_string[] = { ‘H’, ‘e’, ‘l’, ‘l’, ‘o’, 0};
	my_byte = 42;

	serial_out(“Print a character: %c, a string: %c, a decimal integer: %d, a hexadecimal integer: 0x%X, a forward slash: \\, a quote: \”, a new line: \n next line.”, my_char, my_string, my_byte, my_byte);

	Which shows in the terminal as: 
	Print a character: !, a string: Hello, a decimal integer: 42, a hexadecimal integer: 0x2A, a forward slash \, a quote “, and a new line:
	next line.

	Example 2:
	uint8_t  my_day = 21;
	uint8_t my_month[] = {‘J’,’u’,’l’,’y’,0};
	uint16_t my_year = 1980;

	serial_out( “Your date of birth is:\n Day %d \nMonth: %s  \nYear %d.”, my_day, my_month, my_year); 

	Which shows in the terminal as: 

	Your date of birth is:
	Day 21
	Month July
	Year 1980
	\endcode


	\note More advanced users may note that this is a macro wrapper for the standard library printf() function with the string stored in flash and the output directed to the USART, but the documentation here is kept simple for use by novices. If you want to use floating point conversions – DON’T. That facility is not included since it causes the code size to increase more than is warranted by the convenience. If you really need floating point consider using the special printf() functions as documented in avrlibc.
*/




void serial_write(uint8_t *buff, uint8_t size);


// We use a delay in serial_printf if the string to be printed comes withing 2/3
// of the maximum buffer length. The 2/3 and the delays were determined empirically
// to prevent the test code from stepping on the usart buffer. If you are certian that
// you won't send serial_printf strings greater than the buffer size and that you won't
// use the serial_printf to send long strings more frequently than about 20ms then you 
// can remove the if() condition. We have this as the default condition for the serial
// library since we assume the users are novices and might miss a note to avoid long or
// frequent use of the serial_printf function.
/*#if defined(BUTTERFLY)
#include ".\butterfly\butterfly.h"
#define serial_out(val1, val2) {printf_P(PSTR(val1), val2); if(usart0_transmit_buffer_inuse_count() > ((2*USART0_TRANSMIT_BUFFER_LEN)/3)) delay(20);}
#else
#define serial_out(val1, ... ) {printf_P(PSTR(val1), __VA_ARGS__); if(usart0_transmit_buffer_inuse_count() > ((2*USART0_TRANSMIT_BUFFER_LEN)/3)) delay(10);}
#endif*/

void serial_out(const char *fmt, ...);





