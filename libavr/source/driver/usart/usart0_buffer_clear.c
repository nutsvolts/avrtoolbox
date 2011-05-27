


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


void usart0_buffer_clear(ring_t *ring)
{
    register uint8_t sreg;
    
    sreg = SREG;
    cli();
    ring_clear(ring);
    SREG = sreg;
    return;
}





