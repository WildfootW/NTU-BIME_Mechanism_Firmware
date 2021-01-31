# NTU-BEM-Lab Homework-A Sensor-Node-Firmware

## Todo
* UART header
* XBee header
* Add CMake
* Makefile - add burn fuse
* Makefile - add bootloader

## Makefile
* [Using CMake to deploy to avr microcontrollers](https://www.kuon.ch/post/2018-07-11-avr-cmake/)
* [ mkleemann / cmake-avr ](https://github.com/mkleemann/cmake-avr/blob/master/generic-gcc-avr.cmake)

### Arduino Burn Bootloader
* [arduino-flash-tools/tools_linux_64/avrdude/etc/avrdude.conf](https://github.com/arduino/arduino-flash-tools/blob/master/tools_linux_64/avrdude/etc/avrdude.conf)
* First Step
```
avrdude
-C C:\Program Files\WindowsApps\ArduinoLLC.ArduinoIDE_1.8.42.0_x86__mdqgnx93n4wtt\hardware\tools\avr/etc/avrdude.conf
-v -p atmega328p -c stk500v1 -P COM6 -b 19200
-e
-U lock:w:0x3F:m
-U efuse:w:0xFD:m -U hfuse:w:0xDE:m -U lfuse:w:0xFF:m
```

* Second Step
```
avrdude
-C C:\Program Files\WindowsApps\ArduinoLLC.ArduinoIDE_1.8.42.0_x86__mdqgnx93n4wtt\hardware\tools\avr/etc/avrdude.conf
-v -p atmega328p -c stk500v1 -P COM6 -b 19200
-U flash:w:C:\Arduino\../avr/bootloaders/optiboot/optiboot_atmega328.hex:i
-U lock:w:0x0F:m
```

## Programming
* 28.8 Serial Downloading
    * Both the Flash and EEPROM memory arrays can be programmed using the serial SPI bus while RESET is pulled to GND.

[EEPROM vs flash ROM](https://www.avrfreaks.net/forum/eeprom-versus-flash)
> The AVR's flash memory is designed to hold the program data, and so can be clumsy for storing application data. It also has a write endurance of only 10,000 cycles (on newer AVRs) and so will no longer hold valid data once it has been written to that many times.
> EEPROM is slow to write and read, but has an endurance of 100,000 cycles. That means you can write data to it 100,000 times before it will wear out and no longer support the correct charge.
> 1) EEPROM is byte eraseable, Flash is page eraseable (often about 128/256 bytes at a time)
> 2) the 100,000 or 10,000 write/erase life means exactly what it says. You can READ it as often as you like but to change flash/EEPROM you can only change bits that are 1 to 0. So to write 0xF5 bits 2 and 4 are changed from 1 to 0. If you write again you can change other bits from 1 to 0 so 0xF5 could be rewritten 0x85 where bits 4, 5 and 6 are changed from 1 to 0. But you can't change individual bits from 0 to 1. The only way to do that is to erase the entire byte (EEPROM) or page in which the byte is located (flash) to get all the bits back to 0xFF and then change some from 1 to 0 again. That erase counts as one out of the 10,000 cycle available. When you have erased 10,000 times you may find that you can no longer reliably get all the bits back from 0 to 1 any more.


* [Program AVR Using Arduino Simplest Way!!](https://riktronics.wordpress.com/2016/07/26/program-avr-using-arduino-simplest-way/)
### ArduinoISP / stk500v1 / WSL
* [Arduino as ISP and Arduino Bootloaders](https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP)
* [WSL2: Ubuntu 18.04 Serial devices are no longer mounted properly #4322](https://github.com/microsoft/WSL/issues/4322)

### USBasp / Windows / avrdudess
* USBasp - [10 Pin Cable USB ATMEGA8 ATMEGA128 USBASP USBISP AVR Programmer Adapter Arduino](https://www.ebay.com/itm/10-Pin-Cable-USB-ATMEGA8-ATMEGA128-USBASP-USBISP-AVR-Programmer-Adapter-Arduino-/112034500084?hash=item1a15c6cdf4:g:xEYAAOSwPCVX2Ot-)
* Install USBasp driver [Zadig](https://zadig.akeo.ie/)
* [AVRDUDESS – A GUI for AVRDUDE](https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/)
* [AVRDUDE does not recognize USBasp device](https://electronics.stackexchange.com/questions/416714/avrdude-does-not-recognize-usbasp-device)
    > on most places on the internet you will be instructed to install the libusbK driver, which doesn't work, use the **libusb-win32** variant instead
* [Usbasp programming - Cannot set sck period error](https://www.avrfreaks.net/forum/usbasp-programming-cannot-set-sck-period-error)
    > It look like a regular Chinese USBASP.   Hence it will set SCK automatically.   Ignore the SCK warning.

## Bootloader
* [Arduino Nano ATmega328P bootloader difference](https://arduino.stackexchange.com/questions/51866/arduino-nano-atmega328p-bootloader-difference)

## XBee
* Note - XBee PRO S2C
* [ liberza / atmega-xbee-digimesh ](https://github.com/liberza/atmega-xbee-digimesh)
### XCTU
* [XCTU](https://www.digi.com/products/embedded-systems/digi-xbee/digi-xbee-tools/xctu)

## Reference
* [Recovering from a "locked out" AVR](https://www.avrfreaks.net/forum/tutsoft-recovering-locked-out-avr)
* [External Clock for the Atmega328P | AVR Freaks](https://www.avrfreaks.net/forum/external-clock-atmega328p)
* [All you need to know about AVR fuses](https://embedds.com/all-you-need-to-know-about-avr-fuses/)
