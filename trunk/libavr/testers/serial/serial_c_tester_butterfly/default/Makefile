###############################################################################
# Makefile for the project serial_c_tester
###############################################################################

## General Flags
PROJECT = serial_c_tester
MCU = atmega169
TARGET = serial_tester.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                     -DF_CPU=2000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=serial_tester.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = serial_tester.o serial_available.o serial_begin.o serial_end.o serial_flush.o ring_above_highmark.o ring_add.o ring_below_lowmark.o ring_init.o ring_peek.o ring_remove.o usart0.o usart0_buffer_clear.o usart0_buffer_free_count.o usart0_buffer_insert.o usart0_buffer_inuse_count.o usart0_buffer_peek.o usart0_buffer_remove.o usart0_receive_buffer_clear.o usart0_receive_buffer_free_count.o usart0_receive_buffer_inuse_count.o usart0_receive_buffer_peek.o usart0_receive_buffer_remove.o usart0_transmit_buffer_clear.o usart0_transmit_buffer_free_count.o usart0_transmit_buffer_insert.o usart0_transmit_buffer_inuse_count.o usart0_transmit_buffer_peek.o usart0_transmit_buffer_remove.o usart0_uninit.o delay.o ring_clear.o serial_in.o serial_out.o serial_write.o butterfly.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) serial_tester.hex serial_tester.eep serial_tester.lss size

## Compile
serial_tester.o: ../serial_tester.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_available.o: ../../../../source/elementary/serial/serial_available.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_begin.o: ../../../../source/elementary/serial/serial_begin.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_end.o: ../../../../source/elementary/serial/serial_end.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_flush.o: ../../../../source/elementary/serial/serial_flush.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

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

usart0_transmit_buffer_insert.o: ../../../../source/driver/usart/usart0_transmit_buffer_insert.c
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

serial_in.o: ../../../../source/elementary/serial/serial_in.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_out.o: ../../../../source/elementary/serial/serial_out.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_write.o: ../../../../source/elementary/serial/serial_write.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

butterfly.o: ../../../../source/board/butterfly/butterfly.c
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
	-rm -rf $(OBJECTS) serial_tester.elf dep/* serial_tester.hex serial_tester.eep serial_tester.lss serial_tester.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

