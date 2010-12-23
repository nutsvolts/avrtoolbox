/*****************************************************
	fifo.c 10/27/10 Joe Pardue
******************************************************/
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


/************************************************************/
/*!	
	\brief Test to see if the fifo is empty, meaning that
	the length of the data is 0

	\param fifo_struct Pointer to the fifo_struct

	\return Returns 1 is fifo is empty, 0 otherwise.

	\author Joe Pardue 
	\date 10/22/10
	\version 1.01
*/
/************************************************************/
uint8_t fifo_is_empty(struct fifo_struct *fifo)
{
	if( fifo->length == 0 ) return(1);
	else return(0);
}

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

/************************************************************/
/*!	
	\brief Sets length to 0 making all memory locations usable
	
	Doesn't actually clear the data, but makes locations available

	\param fifo_struct Pointer to the fifo_struct

	\author Joe Pardue 
	\date 10/22/10
	\version 1.01
*/
/************************************************************/
void fifo_release_all(struct fifo_struct *fifo)
{
	fifo->length = 0;
}

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

