


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


void usart0_transmit_buffer_clear(void)
{
    usart0_buffer_clear(&usart0_transmit_ring);
    usart0_transmit_check();
	return;
}







