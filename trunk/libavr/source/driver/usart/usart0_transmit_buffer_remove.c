


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


uint8_t usart0_transmit_buffer_remove(void)
{
    register uint8_t result;
    result = usart0_buffer_remove(&usart0_transmit_ring);
    usart0_transmit_check();
    return(result);
}




