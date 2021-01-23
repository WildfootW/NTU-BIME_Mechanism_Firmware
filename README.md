# NTU-BEM-Lab Homework-A Sensor-Node-Firmware

## Todo
* UART header
* XBee header
* Add CMake
* Makefile - add burn fuse
* Makefile - add bootloader

## Makefile
* [arduino-flash-tools/tools_linux_64/avrdude/etc/avrdude.conf](https://github.com/arduino/arduino-flash-tools/blob/master/tools_linux_64/avrdude/etc/avrdude.conf)
```
C:\Program Files\WindowsApps\ArduinoLLC.ArduinoIDE_1.8.42.0_x86__mdqgnx93n4wtt\hardware\tools\avr/bin/avrdude -CC:\Program Files\WindowsApps\ArduinoLLC.ArduinoIDE_1.8.42.0_x86__mdqgnx93n4wtt\hardware\tools\avr/etc/avrdude.conf -v -patmega328p -cstk500v1 -PCOM6 -b19200 -e -Ulock:w:0x3F:m -Uefuse:w:0xFD:m -Uhfuse:w:0xDE:m -Ulfuse:w:0xFF:m
C:\Program Files\WindowsApps\ArduinoLLC.ArduinoIDE_1.8.42.0_x86__mdqgnx93n4wtt\hardware\tools\avr/bin/avrdude -CC:\Program Files\WindowsApps\ArduinoLLC.ArduinoIDE_1.8.42.0_x86__mdqgnx93n4wtt\hardware\tools\avr/etc/avrdude.conf -v -patmega328p -cstk500v1 -PCOM6 -b19200 -Uflash:w:C:\Program Files\WindowsApps\ArduinoLLC.ArduinoIDE_1.8.42.0_x86__mdqgnx93n4wtt\hardware\arduino\avr/bootloaders/optiboot/optiboot_atmega328.hex:i -Ulock:w:0x0F:m
```

## Programming
* 28.8 Serial Downloading
    * Both the Flash and EEPROM memory arrays can be programmed using the serial SPI bus while RESET is pulled to GND.

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
