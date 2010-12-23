#include "fifo.h"

/************************************************************/
/*!	
	\brief Puts a new byte in the fifo.

	Checks to make sure there is space available.
	If no then 0 is returned. 
	If yes, the byte is put in the index location 
	and the fifo length is incremented.

	\param fifo_struct Pointer to the fifo_struct
	\param b the byte to be put into the fifo

	\return 1 if successful, 0 if not

	\author Joe Pardue 
	\date 10/22/10
	\version 1.01
*/
/************************************************************/
uint8_t fifo_put_byte(struct fifo_struct *fifo, uint8_t b)
{
	//printf("fifo->length: %d fifo->size: %d\r",fifo->length,fifo->size);

	// Does the fifo have available space?
	if(fifo->length < fifo->size)
	{
		// Put the byte at the index of the fifo
		fifo->ptr[(fifo->index + fifo->length) % fifo->size] = b;
		// Increment the length
		fifo->length++;
	//printf("--fifo->length: %d fifo->size: %d\r",fifo->length,fifo->size);
		
		return 1; // return success
	}
	else
	{
		fifo->error = FIFO_ATTEMPT_PUT_WHEN_FULL;
 		return 0; // return failure
	}

}
