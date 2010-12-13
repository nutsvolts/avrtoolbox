###############################################################################
# Makefile for the project usart_lib_maker
###############################################################################

## General Flags
PROJECT = usart_lib_maker
MCU = atmega169
TARGET = usart_lib_maker.elf
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
LDFLAGS +=  -Wl,-Map=usart_lib_maker.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Library Directories
LIBDIRS = -L"C:\serial_test" 

## Libraries
LIBS = -lfifo 

## Objects that must be built in order to link
OBJECTS = usart_lib_maker.o usart_error.o usart_init.o usart_put_char.o usart_receive_byte.o usart_send_byte.o usart_send_pmstring.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) usart_lib_maker.hex usart_lib_maker.eep usart_lib_maker.lss size

## Compile
usart_lib_maker.o: ../usart_lib_maker.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart_error.o: ../usart_error.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart_init.o: ../usart_init.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart_put_char.o: ../usart_put_char.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart_receive_byte.o: ../usart_receive_byte.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart_send_byte.o: ../usart_send_byte.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart_send_pmstring.o: ../usart_send_pmstring.c
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
	-rm -rf $(OBJECTS) usart_lib_maker.elf dep/* usart_lib_maker.hex usart_lib_maker.eep usart_lib_maker.lss usart_lib_maker.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

