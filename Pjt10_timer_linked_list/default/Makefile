###############################################################################
# Makefile for the project Pjt10_timer_linker_list
###############################################################################

## General Flags
PROJECT = Pjt10_timer_linker_list
MCU = atmega2560
TARGET = Pjt10_timer_linker_list.elf
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
LDFLAGS +=  -Wl,-Map=Pjt10_timer_linker_list.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = io.o time.o main.o uart.o linked.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Pjt10_timer_linker_list.hex Pjt10_timer_linker_list.eep Pjt10_timer_linker_list.lss size

## Compile
io.o: ../io.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

time.o: ../time.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

linked.o: ../linked.c
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
	-rm -rf $(OBJECTS) Pjt10_timer_linker_list.elf dep/* Pjt10_timer_linker_list.hex Pjt10_timer_linker_list.eep Pjt10_timer_linker_list.lss Pjt10_timer_linker_list.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

