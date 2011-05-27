#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


uint8_t usart0_transmit_buffer_peek(uint8_t *buf, uint8_t count)
{
    return(usart0_buffer_peek(&usart0_transmit_ring, buf, count));
}




