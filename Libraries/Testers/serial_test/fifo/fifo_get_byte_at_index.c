#include "fifo.h"

/************************************************************/
/*!	
	\brief Works like an array access and returns the byte
	at the given index.
	
	This does not clear the byte nor affect the index

	\param fifo_struct Pointer to the fifo_struct
	\param index location of the byte to be returned

	\return The requested byte

	\author Joe Pardue 
	\date 10/22/10
	\version 1.01
*/
/************************************************************/
uint8_t fifo_get_byte_at_index(struct fifo_struct *fifo, uint16_t index)
{
	// return byte located at index in fifo
	return fifo->ptr[(fifo->index+index)%(fifo->size)];
}
