###############################################################################
# Makefile for the project digitalio
###############################################################################

## General Flags
PROJECT = digitalio
MCU = atmega328
TARGET = digitalio.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=digitalio.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Library Directories
LIBDIRS = -L"C:\avrtoolbox\libavr\librarian\atmega328" 

## Libraries
LIBS = -lavr_atmega328_002 

## Objects that must be built in order to link
OBJECTS = digitalio.o digital_read.o digital_write.o port_pin_mode.o port_pin_read.o port_pin_set.o port_pin_clear.o port_pin_activate_pullup.o port_pin_deactivate_pullup.o port_pin_write.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) digitalio.hex digitalio.eep digitalio.lss size

## Compile
digitalio.o: ../digitalio.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

digital_read.o: ../digital_read.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

digital_write.o: ../digital_write.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port_pin_mode.o: ../port_pin_mode.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port_pin_read.o: ../port_pin_read.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port_pin_set.o: ../port_pin_set.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port_pin_clear.o: ../port_pin_clear.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port_pin_activate_pullup.o: ../port_pin_activate_pullup.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port_pin_deactivate_pullup.o: ../port_pin_deactivate_pullup.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port_pin_write.o: ../port_pin_write.c
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
	-rm -rf $(OBJECTS) digitalio.elf dep/* digitalio.hex digitalio.eep digitalio.lss digitalio.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

