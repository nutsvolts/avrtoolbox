#include "fifo.h"

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
