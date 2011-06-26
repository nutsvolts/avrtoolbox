###############################################################################
# Makefile for the project spi_c_tester
###############################################################################

## General Flags
PROJECT = spi_c_tester
MCU = atmega328p
TARGET = spi_tester.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                  -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=spi_tester.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = ring_above_highmark.o ring_add.o ring_below_lowmark.o ring_init.o ring_peek.o ring_remove.o usart0.o usart0_buffer_clear.o usart0_buffer_free_count.o usart0_buffer_insert.o usart0_buffer_inuse_count.o usart0_buffer_peek.o usart0_buffer_remove.o usart0_receive_buffer_clear.o usart0_receive_buffer_free_count.o usart0_receive_buffer_inuse_count.o usart0_receive_buffer_peek.o usart0_receive_buffer_remove.o usart0_transmit_buffer_clear.o usart0_transmit_buffer_free_count.o usart0_transmit_buffer_inuse_count.o usart0_transmit_buffer_peek.o usart0_transmit_buffer_remove.o usart0_uninit.o delay.o ring_clear.o usart0_init_baud.o usart0_get_char.o usart0_put_char.o usart0_available.o usart0_get_byte.o usart0_put_byte.o usart0_put_string.o usart0_put_pgm_string.o usart0_transmit_buffer_insert.o spi_tester.o spi0_init_master.o spi0_master_rw8.o spi0_master_rw16.o spi0_ss.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) spi_tester.hex spi_tester.eep spi_tester.lss size

## Compile
ring_above_highmark.o: ../../../../source/general/ring/ring_above_highmark.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ring_add.o: ../../../../source/general/ring/ring_add.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ring_below_lowmark.o: ../../../../source/general/ring/ring_below_lowmark.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ring_init.o: ../../../../source/general/ring/ring_init.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ring_peek.o: ../../../../source/general/ring/ring_peek.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ring_remove.o: ../../../../source/general/ring/ring_remove.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0.o: ../../../../source/driver/usart/usart0.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_buffer_clear.o: ../../../../source/driver/usart/usart0_buffer_clear.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_buffer_free_count.o: ../../../../source/driver/usart/usart0_buffer_free_count.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_buffer_insert.o: ../../../../source/driver/usart/usart0_buffer_insert.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_buffer_inuse_count.o: ../../../../source/driver/usart/usart0_buffer_inuse_count.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_buffer_peek.o: ../../../../source/driver/usart/usart0_buffer_peek.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_buffer_remove.o: ../../../../source/driver/usart/usart0_buffer_remove.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_receive_buffer_clear.o: ../../../../source/driver/usart/usart0_receive_buffer_clear.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_receive_buffer_free_count.o: ../../../../source/driver/usart/usart0_receive_buffer_free_count.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_receive_buffer_inuse_count.o: ../../../../source/driver/usart/usart0_receive_buffer_inuse_count.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_receive_buffer_peek.o: ../../../../source/driver/usart/usart0_receive_buffer_peek.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_receive_buffer_remove.o: ../../../../source/driver/usart/usart0_receive_buffer_remove.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_transmit_buffer_clear.o: ../../../../source/driver/usart/usart0_transmit_buffer_clear.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_transmit_buffer_free_count.o: ../../../../source/driver/usart/usart0_transmit_buffer_free_count.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_transmit_buffer_inuse_count.o: ../../../../source/driver/usart/usart0_transmit_buffer_inuse_count.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_transmit_buffer_peek.o: ../../../../source/driver/usart/usart0_transmit_buffer_peek.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_transmit_buffer_remove.o: ../../../../source/driver/usart/usart0_transmit_buffer_remove.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_uninit.o: ../../../../source/driver/usart/usart0_uninit.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

delay.o: ../../../../source/general/util/delay.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ring_clear.o: ../../../../source/general/ring/ring_clear.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_init_baud.o: ../../../../source/driver/usart/usart0_init_baud.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_get_char.o: ../../../../source/driver/usart/usart0_get_char.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_put_char.o: ../../../../source/driver/usart/usart0_put_char.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_available.o: ../../../../source/driver/usart/usart0_available.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_get_byte.o: ../../../../source/driver/usart/usart0_get_byte.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_put_byte.o: ../../../../source/driver/usart/usart0_put_byte.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_put_string.o: ../../../../source/driver/usart/usart0_put_string.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_put_pgm_string.o: ../../../../source/driver/usart/usart0_put_pgm_string.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart0_transmit_buffer_insert.o: ../../../../source/driver/usart/usart0_transmit_buffer_insert.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spi_tester.o: ../spi_tester.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spi0_init_master.o: ../../../../source/driver/spi/spi0_init_master.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spi0_master_rw8.o: ../../../../source/driver/spi/spi0_master_rw8.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spi0_master_rw16.o: ../../../../source/driver/spi/spi0_master_rw16.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spi0_ss.o: ../../../../source/driver/spi/spi0_ss.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) spi_tester.elf dep/* spi_tester.hex spi_tester.eep spi_tester.lss spi_tester.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

