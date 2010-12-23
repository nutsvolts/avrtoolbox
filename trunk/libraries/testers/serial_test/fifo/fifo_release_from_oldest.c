#include "fifo.h"

/************************************************************/
/*!	
	\brief Some fifo implementations use clear instead of 
	release for this function, but to me 'clear' implies setting
	the value to 0, but no data values are reset, only indexes
	are changed so that locations can be reused. 
	Doesn't actually clear the data, but makes locations available

	\param fifo_struct Pointer to the fifo_struct
	\param number_bytes to release beginning with the oldest

	\author Joe Pardue 
	\date 10/22/10
	\version 1.01
*/
/************************************************************/ 
void fifo_release_from_oldest(struct fifo_struct *fifo, uint8_t number_bytes)
{
	// Are we releasing less than the entire fifo?
	if(number_bytes < fifo->length)
	{
		// Adjust index and length by number of bytes
		fifo->index += number_bytes;
		if(fifo->index >= fifo->size)
		{
			fifo->index %= fifo->size;
		}
		fifo->length -= number_bytes;
	}
	else
	{
		// Release the whole fifo
		fifo->length = 0;
	}
}
