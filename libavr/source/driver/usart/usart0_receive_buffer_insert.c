


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


bool usart0_receive_buffer_insert(uint8_t c)
{
    return(usart0_buffer_insert(&usart0_receive_ring, c));
}



