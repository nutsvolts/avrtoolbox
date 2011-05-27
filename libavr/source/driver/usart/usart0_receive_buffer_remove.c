


#include "c:\avrtoolbox\libavr\source\general\ring\ring.h" 
#include "usart.h"
#include "usart0.h"


uint8_t usart0_receive_buffer_remove(void)
{
    uint8_t data;
    
    data = usart0_buffer_remove(&usart0_receive_ring);

	/* JWP 3/27/11 commented out
    // Check flow control of data input.
    if(!flow.flow_in)
    {
        if(ring_below_lowmark(&usart0_receive_ring))
        {
            // Turn on incoming data.
            usart0_flow_in_enable();
        }
    }
	*/
    return(data);
}




