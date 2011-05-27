


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


uint8_t usart0_buffer_peek(ring_t *ring, uint8_t *buf, uint8_t count)
{
    register uint8_t result;
    register uint8_t sreg;
    
    sreg = SREG;
    cli();
    result = ring_peek(ring, buf, count);
    SREG = sreg;
    return(result);
}




