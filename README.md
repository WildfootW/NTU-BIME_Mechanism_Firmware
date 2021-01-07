# NTU-BEM-Lab Homework-A Firmware

## Programming
* 28.8 Serial Downloading
    * Both the Flash and EEPROM memory arrays can be programmed using the serial SPI bus while RESET is pulled to GND.

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

## XBee
### XCTU
* [XCTU](https://www.digi.com/products/embedded-systems/digi-xbee/digi-xbee-tools/xctu)

## Reference
* [Recovering from a "locked out" AVR](https://www.avrfreaks.net/forum/tutsoft-recovering-locked-out-avr)
