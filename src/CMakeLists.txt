cmake_minimum_required(VERSION 3.10)

# Project name
project("NTU-BEM_Homework-A_Node-Firmware")

# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

set(MAIN_FILE_NAME main)

## AVR Chip Configuration
set(F_CPU 1000000UL)
# CPU, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU atmega328p)
## Default Baudrate for UART, read avr include/util/setbaud.h for usage
#set(BAUD 9600)

## The programmer to use, read avrdude manual for list
#set(PROGRAMMER stk500v1)
#set(PROGRAMMER_BAUD 19200)

## AVR Fuses, must be in concordance with your hardware and F_CPU
## http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p
#set(E_FUSE 0xFD)
#set(H_FUSE 0xDE)
#set(L_FUSE 0xFF)
#
#set(LOCK_BIT 0xFF)

## Pass parameter to compiler & linker
# Pass defines to compiler
add_definitions(
    -DF_CPU=${F_CPU}
    -DBAUD=${BAUD}
)
# mmcu MUST be passed to bot the compiler and linker, this handle the linker
add_compile_options(
    -mmcu=${MCU} # MCU
    -std=c++11
    -Os # optimize
    -Wall # enable warnings
    #    -Wno-main
    #    -Wundef
    #    -pedantic
    #    -Wstrict-prototypes
    #    -Werror
    #    -Wfatal-errors
    #    -Wl,--relax,--gc-sections
    #    -g
    #    -gdwarf-2
    #    -funsigned-char # a few optimizations
    #    -funsigned-bitfields
    #    -fpack-struct
    #    -fshort-enums
    -ffunction-sections
    -fdata-sections
    #    -fno-split-wide-types
    #    -fno-tree-scev-cprop
)

set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

file(GLOB UTILS_FILES "avr-utils/*.cpp") # Load all files in avr-utils folder
file(GLOB SRC_FILES "./*.cpp") # Load all files in avr-utils folder

# Create one target
add_executable(${MAIN_FILE_NAME} ${UTILS_FILES} ${SRC_FILES})

# Rename the output to .elf as we will create multiple files
set_target_properties(${MAIN_FILE_NAME} PROPERTIES OUTPUT_NAME output.elf)

# Strip binary for upload
add_custom_target(strip avr-strip output.elf DEPENDS ${MAIN_FILE_NAME})

# Transform binary into ihex file, we ignore the eeprom segments in the step
add_custom_target(ihex ALL avr-objcopy -R .eeprom -O ihex output.elf output.ihex DEPENDS strip)
# Transform binary into ihex file, this is the eeprom part (empty if you don't use eeprom static variables)
add_custom_target(eeprom avr-objcopy -j .eeprom  --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 -O ihex output.elf output.eep DEPENDS strip)

## Upload the firmware with avrdude
#add_custom_target(upload avrdude  -c ${PROGRAMMER} -p ${MCU} -U flash:w:output.ihex DEPENDS ihex)
#
## Upload the eeprom with avrdude
#add_custom_target(upload_eeprom avrdude -c ${PROGRAMMER} -p ${MCU}  -U eeprom:w:output.eep DEPENDS eeprom)
#
## Burn fuses
#add_custom_target(fuses avrdude -c ${PROGRAMMER} -p ${MCU}  -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m )

# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "output.ihex;output.eeprom;output.lst")
