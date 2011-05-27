


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


uint8_t usart0_buffer_remove(ring_t *ring)
{
    register uint8_t result;
    register uint8_t sreg;
    
    sreg = SREG;
    cli();
    result = ring_remove(ring);
    SREG = sreg;
    return(result);
}




