###############################################################################
# Makefile for the project avrlib_lcd_test
###############################################################################

## General Flags
PROJECT = avrlib_lcd_test
MCU = atmega328p
TARGET = nav_menu.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99           -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=nav_menu.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Library Directories
LIBDIRS = -L"C:\avrtoolbox\libavr\librarian\atmega328" 

## Libraries
LIBS = -lavr_atmega328_005 

## Objects that must be built in order to link
OBJECTS = lcd.o nav.o nav_menu.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) nav_menu.hex nav_menu.eep nav_menu.lss size

## Compile
lcd.o: ../../../libavr/source/driver/external_hardware/lcd_hd44780/lcd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

nav.o: ../../../libavr/source/driver/external_hardware/nav_button/nav.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

nav_menu.o: ../nav_menu.c
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
	-rm -rf $(OBJECTS) nav_menu.elf dep/* nav_menu.hex nav_menu.eep nav_menu.lss nav_menu.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

