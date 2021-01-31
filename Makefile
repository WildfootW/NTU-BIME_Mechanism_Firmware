#   Makefile
#   Version 1.4
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyleft (ɔ) 2019-2021 WildfootW All rights reversed.

MCU                 := atmega328p
DUDE_USB_PORT       := /dev/ttyS8 # Your Serial Port
PROGRAMMER          := stk500v1 # ArduinoISP
PROGRAMMER_BAUD     := 19200 # 19200 for ArduinoISP stk500v1

AVRSIZE             := avr-size
AVRDUDE             := avrdude
DUDE_OPTIONS        := -p ${MCU} -c ${PROGRAMMER} -b ${PROGRAMMER_BAUD} -P ${DUDE_USB_PORT} 

E_FUSE              := 0xFD
H_FUSE              := 0xDE
L_FUSE              := 0xFF

# cmake output file
OUTPUT_FILE         := src/output

.PHONY: all
all: compile upload_flash

.PHONY: configure
configure:
	cd ./src && \
	cmake .

.PHONY: compile
compile: ./src/Makefile
	cd ./src && \
	make
	${AVRSIZE} -C --mcu=${MCU} ${OUTPUT_FILE}.elf

.PHONY: upload_flash
upload_flash:
	${AVRDUDE} ${DUDE_OPTIONS} -U flash:w:${OUTPUT_FILE}.ihex:i

.PHONY: upload_eeprom
upload_eeprom:
	${AVRDUDE} ${DUDE_OPTIONS} -U eeprom:w:${OUTPUT_FILE}.ihex:i

.PHONY: write_fuse
fuse_write:
	${AVRDUDE} ${DUDE_OPTIONS} -U efuse:w:${E_FUSE}:m -U hfuse:w:${H_FUSE}:m -U lfuse:w:${L_FUSE}:m

.PHONY: test_chip
test_chip:
	${AVRDUDE} ${DUDE_OPTIONS}

.PHONY: clean
clean: ./src/Makefile
	cd ./src && \
	make clean

