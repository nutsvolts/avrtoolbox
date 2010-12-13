/*****************************************************
	fifo.h 10/27/10 Joe Pardue
******************************************************/

// Prevent duplicate inclusion of this file
#ifndef FIFO_H
#define FIFO_H

#include <inttypes.h>
#include <stdio.h>

/* ********************************************************** */
/*!	
	\struct fifo_struct
	
	\brief Defines the fifo data structure: fifo_struct

	\author Joe Pardue 
	\date 8/22/08
	\version 1.00
*/
/* ********************************************************** */
struct fifo_struct
{
	//! pointer to the FIFO	
	uint8_t *ptr;
	
	//! size of the FIFO
	uint16_t size; 
				
	//! data start index
	uint16_t index; 
		
	//! length of data stored in the FIFO
	uint16_t length;
	
	//! error number
	uint8_t error; 			
};


/*!	
	\def FIFO_NO_ERROR
 	fifo_struct error member set to 0 if there was no error using the FIFO
*/
#define FIFO_NO_ERROR 	0

/*!	\def FIFO_ATTEMPT_GET_WHEN_EMPTY
 	fifo_struct error member set to 1 if there was an attempt to get a byte from an empty FIFO
	
*/
#define FIFO_ATTEMPT_PUT_WHEN_FULL	1

/*!	\def FIFO_ATTEMPT_PUT_WHEN_FULL
 	fifo_struct error member set to 2 if there was an attempt to put a byte into an empty FIFO

*/
#define FIFO_ATTEMPT_GET_WHEN_EMPTY	2


// Function prototypes

// Initialize a fifo with a given array start address and size.
void fifo_init(struct fifo_struct *fifo, uint8_t *arrayStart, uint8_t size);

// Returns 1 if empty, 0 otherwise.
uint8_t fifo_is_empty(struct fifo_struct *fifo);


/************************************************************/
/*! 
	\brief Gets oldest byte from tail.

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
uint8_t fifo_get_byte(struct fifo_struct *fifo);

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
uint8_t fifo_put_byte(struct fifo_struct *fifo, uint8_t b);


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
uint8_t fifo_get_byte_at_index(struct fifo_struct *fifo, uint16_t index);

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
uint8_t fifo_not_full(struct fifo_struct *fifo);


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
void fifo_release_all(struct fifo_struct *fifo);

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
void fifo_release_from_oldest(struct fifo_struct *fifo, uint8_t number);

#endif
