/*
 *  BSD License
 *  -----------
 *
 *  Copyright (c) 2011, Eric Weddington and Joe Pardue, All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer. 
 *   
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *   
 *  - Neither the name of the Eric Weddington nor Joe Pardue nor the names of 
 *    its contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission. 
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RING_H
#define RING_H

#include <stdint.h>
#include <stdbool.h>

typedef uint16_t ring_index_t;
typedef uint8_t *ring_buffer_t;
typedef uint8_t ring_count_t;
typedef uint8_t ring_size_t;
typedef struct
{
    ring_buffer_t buffer;
    ring_size_t size;
    ring_index_t head_index;
    ring_index_t tail_index;
    ring_count_t count;
} ring_t;

/** 
	\ingroup libring

	\brief Sets up the ring buffer with ring_t parameters.
	The clear command is also called to set 0 values within
    the ring buffer functions. 

	\param *r pointer to the ring_t structure
	\param a pointer to buffer you want to use for the ring buffer.
	\param size size in bytes of the buffer and must be equal to or greater than 2. he actual amount of storage available in the ring buffer is size - 1.
    
    \return boolean true if the ring buffer was initialized, false otherwise.
    
	\code
	Example:
	void setup()
	{
		// Initialize the ring buffer
		if(!ring_init(ring_t *r, ring_buffer_t buffer, ring_size_t size))
		{
			// Buffer not intitialized so handle the error
		}
		
	// Okay to use the buffer 
	\endcode
}	
*/
bool ring_init(ring_t *r, ring_buffer_t buffer, ring_size_t size);

/** 
	\ingroup libring

	\brief This clear function will reset the head_index and tail_index to 0.
    The count value is also set to 0. A memset command is used to reset
    a particular area in memory as well.

	\param *r pointer to ring buffer
	/\return boolean result of attempt to add byte
	
	\code
	Example:
	void end_this()
	{
		ring_clear(&receive_ring);
	}
	\endcode
*/
bool ring_clear(ring_t *r);

/** 
	\ingroup libring

	\brief This boolean will reference the ring_t structure and add data
    to the ring buffer as it increments the index. If data
    can be added to the ring buffer, the boolean will then return
    a true. If no addition was done, then a false will be
    returned.
    
    \note Data added will be one value less than the size
    of the defined ring buffer. An example of this is a buffer
    size of [10] will only allow 9 values to be added into the buffer
	
	\param *r pointer to ring buffer
	\param data byte to add
	\return boolean result of attempt to add byte
	
	\code
	Example:
	// receive_ring structure defined elsewhere
	bool put_byte(uint8_t b)
	{
		return(ring_add(&receive_ring, b));
	}
	\endcode
*/
bool ring_add(ring_t *r, uint8_t data);


/** 
	\ingroup libring

    \brief  Removes a byte of data from the ring buffer.
	 
    \param *r a pointer to the ring_t structure.
	
    \return The byte of data removed.
	
	\code
	// receive_ring structure defined elsewhere
	uint8_t get_byte()
	{
		return(ring_remove(&receive_ring));
	}
	\endcode
*/	
uint8_t ring_remove(ring_t *r);

/** 
	\ingroup libring

    \brief Reads uint8_t count bytes from the ring buffer into a new buffer provided 
	as a parameter. It does not remove any of the values read from the ring buffer.
	Nor does it change the ring buffer indexes.	It returns the number of bytes read.
	 
    \param *r a pointer to the ring_t structure.
    \param *buf a pointer to a buffer to hold the data.
    \param count the number of bytes to load from the ring buffer to buf.
	
    \return the actual number of bytes read.
	
	\code
	Example:
	// receive_ring structure defined elsewhere
	uint8_t get_bytes(uint8_t *buf, uint8_t count)
	{
		return(ring_peek(&receive_ring, buf, count));
	}
	\endcode
*/
uint8_t ring_peek(ring_t *r, uint8_t *buf, uint8_t count);

/** 
	\ingroup libring

    \brief Determines if the count is above the highmark used for flow-control.
	 
    \param ring_t *r : a pointer to a ring_t structure.
	
    \return true if the count is >= 3/4 of the buffer size.
	
	\code
	Example:
	// receive_ring structure defined elsewhere
	void do_something()
	{
		if(ring_above_highmark(&receive_ring))
		{
			pause_reception();
		}
		else
		{
			continue_reception();
		}
	}
	\endcode
*/
bool ring_above_highmark(ring_t *r);

/** 
	\ingroup libring

    \brief Determines if the count is belowthe lowmark used for flow-control.
	 
    \param ring_t *r : a pointer to a ring_t structure.
	
    \return true if the count is <= 1/4 of the buffer size.
	
	\code
	Example:
	// receive_ring structure defined elsewhere
	void do_something()
	{
		if(ring_above_lowmark(&receive_ring))
		{
			start_transmission();
		}
		else
		{
			wait_till_later();
		}
	}
	\endcode
*/
bool ring_below_lowmark(ring_t *r);

/* ring buffer counter initialization */
#define ring_free_count(r)      (((r)->size) - ((r)->count))

#endif
