#include "fifo.h"

/* ********************************************************** */
/*!	
	\brief Initializes the fifo data structure: fifo_struct

	\param fifo_struct Pointer to fifo_struct
	\param start Pointer to start position in the fifo
	\param size of the fifo buffer

	\note The fifo_struct elements index and length are set to 0

	\author Joe Pardue 
	\date 10/22/10
	\version 1.01
*/
/* ********************************************************** */
void fifo_init(struct fifo_struct *fifo, uint8_t *start, uint8_t size)
{	
	// set start pointer and size of the buffer
	fifo->ptr = start;
	fifo->size = size;
	// initialize index and length
	fifo->index = 0;
	fifo->length = 0;
	fifo->error = FIFO_NO_ERROR;
}
