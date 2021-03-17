# Source Code
###### tags: `readme`

## Timer
Crystal 16MHz

## Design
### Architecture
#### I/O Port
* Serial
    * PD1 (TXD)

### Workflow
* main
    * initial
    * loop

* input
    * trigger interrupt while complete reading from ADC
    * pass value to sensor
    * change input channel to next channel
    * start next ADC

### Framework
#### Files
* main.cpp
* Registers.hpp
* IOPin.hpp
* ADConverter.hpp
    * Provide interface to interactive with Analog-to-Digital Converter
* Millis.hpp
    * Using **Timer1**
    * Provide millis (& delay) function
* ObstacleDetector.hpp
    * Using 2 IR sensor
    * Determine robots' state
* RouteDetector.hpp
    * Using 3 IR sensor
    * Determine robots' state
* Sensors.hpp
    * Using **ADC0-5** (in main/ISR)
    * Basic sensor function
* Usart.hpp
    * Using **PD1**

## Reference
### Document
* Atmel ATmega328P DATASHEET
* Real-Time C++

### Other
* NTU BIME Principles and Applications of Microcontrollers Y.-F. Kuo
* [avr/iom328p.h](https://github.com/vancegroup-mirrors/avr-libc/blob/master/avr-libc/include/avr/iom328p.h)
* [TTU Robotiklubi - ATmega88 avr/cpp/IO.h](http://avr-cpp-lib.sourceforge.net/ATmega88/_i_o_8h-source.html)
* [libpololu-avr](https://github.com/pololu/libpololu-avr)
* jypma
    * [AvrLib](https://github.com/jypma/AvrLib)
    * [AvrLibDemo](https://github.com/jypma/AvrLibDemo)

### Fuse
* [Engbedded Atmel AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/)
* [ATmega328p fuse bits tutorial (an external 16MHz crystal oscillator)](https://www.allaboutcircuits.com/projects/atmega328p-fuse-bits-and-an-external-crystal-oscillator/)

* CKDIV8
    > The CKDIV8 fuse determines the initial value of the CLKPS bits. If CKDIV8 is unprogrammed, the CLKPS bits will be reset to “0000”. If CKDIV8 is programmed, CLKPS bits are reset to “0011”, giving a division factor of 8 at start up. This feature should be used if the selected clock source has a higher frequency than the maximum frequency of the device at the present operating conditions. Note that any value can be written to the CLKPS bits regardless of the CKDIV8 fuse setting.
* CKOUT
    > The device can output the system clock on the CLKO pin. To enable the output, the CKOUT fuse has to be programmed. This mode is suitable when the chip clock is used to drive other circuits on the system. The clock also will be output during reset, and the normal operation of I/O pin will be overridden when the fuse is programmed.

## Note / Problemshooting
### Object Oriented
* [Electronics - C++ classes for I/O pin abstraction](https://electronics.stackexchange.com/questions/19057/c-classes-for-i-o-pin-abstraction)
* [Objects? No, thanks! (Using C++ effectively on small systems)](https://www.embedded.com/objects-no-thanks-using-c-effectively-on-small-systems/)

### Register Data Type
```c
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _SFR_MEM8(mem_addr) _MMIO_BYTE(mem_addr)
#define PINB _SFR_IO8(0x03)
```

### constexpr reference to avr port address
```
In file included from /usr/lib/avr/include/avr/io.h:99:0,
                 from AVRUtils.hpp:14,
                 from main.cpp:8:
AVRUtils.hpp:70:41: error: expression ‘*37u’ has side-effects
 using pin_PB0 = AVRIOPin<AVRRegisterBit<PORTB, PORTB0>, AVRRegisterBit<DDRB, DDB0>, AVRRegisterBit<PINB, PINB0>>;
                                         ^
In file included from main.cpp:8:0:
AVRUtils.hpp:70:54: error: ‘*37u’ is not a constant expression
 using pin_PB0 = AVRIOPin<AVRRegisterBit<PORTB, PORTB0>, AVRRegisterBit<DDRB, DDB0>, AVRRegisterBit<PINB, PINB0>>;
                                                      ^
```
I need to use struct `AVR_REGISTER_DDRD` packing `DDRD` while as template argument.
* [stackoverflow - constexpr reference to avr port address](https://stackoverflow.com/questions/41077173/constexpr-reference-to-avr-port-address)
* [What exactly is a 'side-effect' in C++?](https://stackoverflow.com/questions/9563600/what-exactly-is-a-side-effect-in-c)

### Member functions of class templates
```
template<class T> class X {
   public:
      T operator+(T);
};

template<class T> T X<T>::operator+(T arg1) {
   return arg1;
};
```
* [Member functions of class templates (C++ only)](https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/member_function_templates.htm)

### enum class
* [Why is enum class preferred over plain enum?](https://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum)
* [Declaring an enum within a class](https://stackoverflow.com/questions/2503807/declaring-an-enum-within-a-class)
* [How to cast int to enum in C++?](https://stackoverflow.com/questions/11452920/how-to-cast-int-to-enum-in-c)
* [Enum Class Default Initialization](https://stackoverflow.com/questions/53897991/enum-class-default-initialization)
* [How to use enums as flags in C++?](https://stackoverflow.com/questions/1448396/how-to-use-enums-as-flags-in-c)
```
enum class SevenSegmentGraph
{
    //PGFEDCBA
    number_0 = 0b00111111, // 0
    number_1 = 0b00000110, // 1
    number_2 = 0b01011011, // 2
    ...
    number_7 = 0b00000111, // 7
};
```
```
PORTB = ~static_cast<uint8_t>(graph);
```

### Data Type
* Mind Data Type Size: [ <stdint.h>: Standard Integer Types ](https://www.nongnu.org/avr-libc/user-manual/group__avr__stdint.html)
```
typedef unsigned int    uint16_t
typedef unsigned long int     uint32_t
```

### Usart Baud
* [AVR Baud Rate Tables](https://cache.amobbs.com/bbs_upload782111/files_22/ourdev_508497.html)
* [ UART Not working with ATMEGA328P ](https://www.avrfreaks.net/forum/uart-not-working-atmega328p)
> change the AVR code to send nothing but 'U' (because 'U' with 8-N-1 is a constant 0101010101010.. pattern) and then measure the TXD pulse width. is that 104us. If it isn't then either your UBRR code is wrong or your assumption about `F_CPU` is.
My experience: 1 MHz 9600 garbled, but 16 MHz 115200 Successed.

### Power
* [Feeding power to Arduino: the ultimate guide](https://www.open-electronics.org/the-power-of-arduino-this-unknown/)
> Vin socket: as said before, this one can be useful as input if an external voltage is needed and you only have 6 V available, in fact the Vin socket bypasses the protection diode and the regulator may operate properly; or it may be useful to draw the voltage coming from the JACK socket;

## AVR Debug
* [AVR Debugging on Linux (with debugWire)](http://luniks.net/avr-debug.jsp)

