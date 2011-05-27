#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"

uint8_t usart0_receive_buffer_free_count(void)
{
    return(usart0_buffer_free_count(&usart0_receive_ring));
}




