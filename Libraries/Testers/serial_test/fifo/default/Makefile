###############################################################################
# Makefile for the project fifo_lib_169_maker
###############################################################################

## General Flags
PROJECT = fifo_lib_169_maker
MCU = atmega169
TARGET = fifo_lib_169_maker.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=fifo_lib_169_maker.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = fifo_get_byte.o fifo_init.o fifo_put_byte.o fifo_get_byte_at_index.o fifo_not_full.o fifoReleaseAll.o fifoReleaseFromOldest.o fifo_is_empty.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) fifo_lib_169_maker.hex fifo_lib_169_maker.eep fifo_lib_169_maker.lss size

## Compile
fifo_get_byte.o: ../fifo_get_byte.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fifo_init.o: ../fifo_init.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fifo_put_byte.o: ../fifo_put_byte.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fifo_get_byte_at_index.o: ../fifo_get_byte_at_index.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fifo_not_full.o: ../fifo_not_full.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fifoReleaseAll.o: ../fifoReleaseAll.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fifoReleaseFromOldest.o: ../fifoReleaseFromOldest.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

fifo_is_empty.o: ../fifo_is_empty.c
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
	-rm -rf $(OBJECTS) fifo_lib_169_maker.elf dep/* fifo_lib_169_maker.hex fifo_lib_169_maker.eep fifo_lib_169_maker.lss fifo_lib_169_maker.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

