#include "fifo.h"

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
