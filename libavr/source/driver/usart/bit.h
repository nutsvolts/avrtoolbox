/********<File Header>*****************************************
<Notice> Copyright (c) 2004 UMG, Inc.
<Project>
<File> bit.h
<Desc> Bit macros
<Author> Eric B. Weddington
<Notes>
**************************************************************/

#ifndef BIT_H
#define BIT_H

#include <inttypes.h>

#define BIT(x)	        (1 << (x))
#define BIT_32(x)    ((uint32_t)1 << (x))

#define bit_set_8(var, mask)                 ((var) |= (uint8_t)(mask))
#define bit_clear_8(var, mask)               ((var) &= (uint8_t)~(mask))
#define bit_toggle_8(var, mask)              ((var) ^= (uint8_t)(mask))
#define bit_read_8(var, mask)                ((var) & (uint8_t)(mask))
#define bit_write_8(cond, var, mask)         ((cond) ? bit_set_8(var, mask) : bit_clear_8(var, mask))
#define bit_is_set_8(var, bit)               bit_read_8(var, BIT(bit))
#define bit_is_clear_8(var, bit)             (!bit_read_8(var, BIT(bit)))
#define loop_until_bit_is_set_8(var, bit)    do{}while(bit_is_clear_8(var, bit))
#define loop_until_bit_is_clear_8(var, bit)  do{}while(bit_is_set_8(var, bit))


#define bit_set_16(var, mask)                 ((var) |= (uint16_t)(mask))
#define bit_clear_16(var, mask)               ((var) &= (uint16_t)~(mask))
#define bit_toggle_16(var, mask)              ((var) ^= (uint16_t)(mask))
#define bit_read_16(var, mask)                ((var) & (uint16_t)(mask))
#define bit_write_16(cond, var, mask)         ((cond) ? bit_set_16(var, mask) : bit_clear_16(var, mask))
#define bit_is_set_16(var, bit)               ((var) & (uint16_t)BIT(bit))
#define bit_is_clear_16(var, bit)             (!bit_is_set_16(var, bit))
#define loop_until_bit_is_set_16(var, bit)    do{}while(bit_is_clear_16(var, bit))
#define loop_until_bit_is_clear_16(var, bit)  do{}while(bit_is_set_16(var, bit))


#define bit_set_32(var, mask)                ((var) |= (uint32_t)(mask))
#define bit_clear_32(var, mask)              ((var) &= (uint32_t)~(mask))
#define bit_toggle_32(var, mask)             ((var) ^= (uint32_t)(mask))
#define bit_read_32(var, mask)               ((var) & (uint32_t)(mask))
#define bit_write_32(cond, var, mask)        ((cond) ? bit_set_32(var, mask) : bit_clear_32(var, mask))
#define bit_is_set_32(var, bit)              ((var) & (uint32_t)BIT_32(bit))
#define bit_is_clear_32(var, bit)            (!bit_is_set_32(var, bit))
#define loop_until_bit_is_set_32(var, bit)   do{}while(bit_is_clear_32(var, bit))
#define loop_until_bit_is_clear_32(var, bit) do{}while(bit_is_set_32(var, bit))


#define bit_set(var, mask)                      bit_set_8(var, mask)
#define bit_clear(var, mask)                    bit_clear_8(var, mask)
#define bit_toggle(var, mask)                   bit_toggle_8(var, mask)
#define bit_read(var, mask)                     bit_read_8(var, mask)
#define bit_write(cond, var, mask)              bit_write_8(cond, var, mask)
#ifdef bit_is_set
    #undef bit_is_set
    #define bit_is_set(var, bit)                bit_is_set_8(var, bit)
#endif
#ifdef bit_is_clear
    #undef bit_is_clear
    #define bit_is_clear(var, bit)              bit_is_clear_8(var, bit)
#endif
#ifdef loop_until_bit_is_set
    #undef loop_until_bit_is_set
    #define loop_until_bit_is_set(var, bit)     loop_until_bit_is_set_8(var, bit)
#endif
#ifdef loop_until_bit_is_clear
    #undef loop_until_bit_is_clear
    #define loop_until_bit_is_clear(var, bit)   loop_until_bit_is_clear_8(var, bit)
#endif


#endif

