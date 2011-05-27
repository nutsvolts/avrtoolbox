


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"

bool usart0_buffer_insert(ring_t *ring, uint8_t c)
{
    register bool result;
    register uint8_t sreg;
    
    sreg = SREG;
    cli();
    result = ring_add(ring, c);
    SREG = sreg;
    return(result);
}




