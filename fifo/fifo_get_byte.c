#include "fifo.h"

/************************************************************/
/*! 
	\brief Gets a byte from tail.

	This function returns the oldest byte in the buffer.
	If the buffer is empty it sets the 
	fifo->error = FIFO_ATTEMPT_GET_WHEN_EMPTY

	\param fifo_struct Pointer to the fifo

	\return The requested byte

	\author Joe Pardue 
	\date 10/22/10
	\version 1.01
*/
/************************************************************/
uint8_t fifo_get_byte(struct fifo_struct *fifo)
{
	uint8_t data = 0;
	
	if(fifo->length)
	{
		// get the oldest byte
		data = fifo->ptr[fifo->index];

		// set the index to the next oldest byte
		fifo->index++;

		// move the index
		if(fifo->index >= fifo->size)
		{
			fifo->index %= fifo->size;
		}

		// the buffer is now reduced by the one byte
		fifo->length--;
	}	
	else fifo->error = FIFO_ATTEMPT_GET_WHEN_EMPTY;

	return data;
}
