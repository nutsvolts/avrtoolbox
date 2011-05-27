


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


uint8_t usart0_receive_peek(void)
{
	uint8_t data;
	usart0_receive_buffer_peek(&data, 1);
	return(data);
}







