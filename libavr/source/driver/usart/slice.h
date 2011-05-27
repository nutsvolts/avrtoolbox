/********<File Header>*****************************************
<Notice> Copyright (c) 2002-2004 UMG, Inc.
<Project> DAS-6003
<File> slice.h
<Desc> Slicing macros.
<Author> Eric B. Weddington
<Notes>
**************************************************************/

#ifndef SLICE_H
#define SLICE_H

#include <inttypes.h>


#define hi_nybble(x)    ((uint8_t)(x) >> 4)
#define lo_nybble(x)    ((uint8_t)(x) & (uint8_t)0x0F)


#define hi_byte(x)	((uint8_t)(((uint16_t)(x)) >> 8))
#define lo_byte(x)	((uint8_t)((uint16_t)(x)))


#define hi_word(x)	((uint16_t)(((uint32_t)(x)) >> 16))
#define lo_word(x)	((uint16_t)((uint32_t)(x)))

#define byte_0(x)   (*(((uint8_t *)&((uint32_t)x)) + 0))
#define byte_1(x)   (*(((uint8_t *)&((uint32_t)x)) + 1))
#define byte_2(x)   (*(((uint8_t *)&((uint32_t)x)) + 2))
#define byte_3(x)   (*(((uint8_t *)&((uint32_t)x)) + 3))


#define reverse_32(x) \
({ \
    uint8_t __temp; \
    __temp = byte_0(x); \
    byte_0(x) = byte_3(x); \
    byte_3(x) = __temp; \
    __temp = byte_1(x); \
    byte_1(x) = byte_2(x); \
    byte_2(x) = __temp; \
    x; \
})

#endif



