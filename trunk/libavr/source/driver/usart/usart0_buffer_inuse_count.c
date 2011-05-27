#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 

#include "usart.h"
#include "usart0.h"

uint8_t usart0_buffer_inuse_count(ring_t *ring)
{
    register uint8_t result;
    register uint8_t sreg;
    
    sreg = SREG;
    cli();
    result = ring->count;
    SREG = sreg;
    return(result);
}


