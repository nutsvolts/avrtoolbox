#include "fifo.h"

/************************************************************/
/*!	
	\brief Test to see if the fifo is NOT full, meaning that
	the length of the data is less than the size of the buffer

	\param fifo_struct Pointer to the fifo_struct

	\return Returns 1 is fifo is not full, 0 otherwise.

	\author Joe Pardue 
	\date 10/22/10
	\version 1.01
*/
/************************************************************/
uint8_t fifo_not_full(struct fifo_struct *fifo)
{
	return (fifo->length < fifo->size);
}
