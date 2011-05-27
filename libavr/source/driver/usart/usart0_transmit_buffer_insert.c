


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


bool usart0_transmit_buffer_insert(uint8_t c)
{
    register bool result;
    result = usart0_buffer_insert(&usart0_transmit_ring, c);
    if(result == true) usart0_transmit_check();

    return(result);
}



