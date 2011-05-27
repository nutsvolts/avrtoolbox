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

/**
    @file
   \brief Test the ring buffer library in libavr_atmega328_001.a
   May 7, 2011 - Joe Pardue

*/
#include "C:\avrtoolbox\libavr\source\general\ring\ring.h"
#include "C:\avrtoolbox\libavr\source\elementary\serial\serial.h"

#define BUFFER_SIZE 16

static uint8_t array1[BUFFER_SIZE];
static uint8_t array2[BUFFER_SIZE];
static uint8_t array3[BUFFER_SIZE];

int main(void)
{
	//smFifoStruct fifoStruct1;
	//smFifoStruct fifoStruct2;	
	//smFifoStruct fifoStruct3;
	ring_t ring1;
	ring_t ring2;
	ring_t ring3;

		
	// Create fifos
	//fifoInit(&fifoStruct1, array1, BUFFER_SIZE);
	//fifoInit(&fifoStruct2, array2, BUFFER_SIZE);
	//fifoInit(&fifoStruct3, array3, BUFFER_SIZE);

	ring_init(&ring1, array1, BUFFER_SIZE);
	ring_init(&ring2, array2, BUFFER_SIZE);
	ring_init(&ring3, array3, BUFFER_SIZE);


	// Assign temporary variables so that we can look at
	// them in the Breakpoints and Tracepoint window
	uint16_t volatile temp_head_index = 0;
	uint16_t volatile temp_tail_index = 0;
	uint8_t volatile temp_count = 0;


	// Test 1

	// Store six 0x01 bytes in ring 1
	for(uint8_t i = 0; i < 6; i++)
	{
		ring_add(&ring1, 0x01);	
	}
	temp_head_index = ring1.head_index;
	temp_tail_index = ring1.tail_index;
	temp_count = ring1.count;


	// Test 2
	// First three bytes 'removed' to array3
	// Note that the value doesn't change
	// but the index does change
	for(uint8_t i = 0; i < 3; i++)
	{
		ring_add(&ring3, ring_remove(&ring1));
	}

	temp_head_index = ring1.head_index;
	temp_tail_index = ring1.tail_index;
	temp_count = ring1.count;

	// Test 3
	// Fill ring2 with sequence of 16 bytes
	// 0x01 to 0x10 and then read four bytes
	// beginning at position 8
	for(uint8_t i = 1; i <= 16; i++)
	{
		ring_add(&ring2, i);
	}
	
	uint8_t temp_buf[] = {0,0,0,0};
	
	ring_peek(&ring2, temp_buf, 4);

	
}
























