#   Makefile
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2019-2020 WildfootW All rights reserved.

MCU                 := atmega328p
# Your Serial Port
DUDE_USB_PORT       := /dev/ttyS8
# ArduinoISP
PROGRAMMER          := stk500v1
PROGRAMMER_BAUD     := 19200

TARGET              := main
SRCS                := USART
SRCOBJS             := $(addsuffix .o, $(SRCS))

CXX                 := avr-g++
AR                  := avr-ar
OBJCOPY             := avr-objcopy
OBJDUMP             := avr-objdump
AVRSIZE             := avr-size
AVRDUDE             := avrdude

CXXFLAGS_COMPILE    := -c -std=c++11 -Wall -Os -ffunction-sections -fdata-sections -mmcu=${MCU} -DNDEBUG
CXXFLAGS_LINK       := -Os -mmcu=${MCU} -ffunction-sections -fdata-sections -Wl,--gc-sections

.PHONY: all
all: link size flash

.PHONY: link
link: $(SRCOBJS)
	$(CXX) ${CXXFLAGS_LINK} $^ -o ${TARGET}.elf

$(SRCOBJS): %.o: %.c
	${CXX} ${CXXFLAGS_COMPILE} $< -o $@

.PHONY: flash
flash:
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.elf ${TARGET}.ihex
	${AVRDUDE} -p ${MCU} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${DUDE_USB_PORT} -U flash:w:${TARGET}.ihex:i

.PHONY: size
size: ${TARGET}.elf
	${AVRSIZE} -C --mcu=${MCU} ${TARGET}.elf

.PHONY: clean
clean:
	rm -f *.o *.ihex *.elf

