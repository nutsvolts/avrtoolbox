###############################################################################
# Makefile for the project serial_lib_169_maker
###############################################################################

## General Flags
PROJECT = serial_lib_169_maker
MCU = atmega169
TARGET = serial_lib_169_maker.elf
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
LDFLAGS +=  -Wl,-Map=serial_lib_169_maker.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Library Directories
LIBDIRS = -L"C:\serial_test" 

## Libraries
LIBS = -lavrtools 

## Objects that must be built in order to link
OBJECTS = serial_lib_169_maker.o serial_available.o serial_begin.o serial_end.o serial_flush.o serial_read.o serial_read_at_index.o serial_write.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) serial_lib_169_maker.hex serial_lib_169_maker.eep serial_lib_169_maker.lss size

## Compile
serial_lib_169_maker.o: ../serial_lib_169_maker.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_available.o: ../serial_available.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_begin.o: ../serial_begin.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_end.o: ../serial_end.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_flush.o: ../serial_flush.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_read.o: ../serial_read.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_read_at_index.o: ../serial_read_at_index.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial_write.o: ../serial_write.c
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
	-rm -rf $(OBJECTS) serial_lib_169_maker.elf dep/* serial_lib_169_maker.hex serial_lib_169_maker.eep serial_lib_169_maker.lss serial_lib_169_maker.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

