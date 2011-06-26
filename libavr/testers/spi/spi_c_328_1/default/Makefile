###############################################################################
# Makefile for the project spi_c_328
###############################################################################

## General Flags
PROJECT = spi_c_328
MCU = atmega328
TARGET = spi_c_328.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                   -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=spi_c_328.map


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
OBJECTS = spi_c_328.o spi0_init_master.o spi0_master_rw8.o spi0_master_rw16.o spi0_ss.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) spi_c_328.hex spi_c_328.eep spi_c_328.lss size

## Compile
spi_c_328.o: ../spi_c_328.c
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
	-rm -rf $(OBJECTS) spi_c_328.elf dep/* spi_c_328.hex spi_c_328.eep spi_c_328.lss spi_c_328.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

