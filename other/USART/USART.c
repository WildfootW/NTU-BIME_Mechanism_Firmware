/*
 * usart.c
 *
 * Distributed under terms of the MIT license.
 */

//#define F_CPU  1000000UL
//#define F_CPU  2000000UL
//#define F_CPU  4000000UL
#define F_CPU  8000000UL
//#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
    CLKPR = 0b10000000;

//    CLKPR = 0b00000100; //  1 MHz
//    CLKPR = 0b00000011; //  2 MHz
//    CLKPR = 0b00000010; //  4 MHz
    CLKPR = 0b00000001; //  8 MHz
//    CLKPR = 0b00000000; // 16 MHz

    /*
     *  1 MHz - 9600/  6/ 7.5, 115200/  0/84.3
     *  2 MHz - 9600/ 12/ 0.2, 115200/  0/ 7.8
     *  4 MHz - 9600/ 25/ 0.2, 115200/  1/ 7.8
     *  8 MHz - 9600/ 51/ 0.2, 115200/  3/ 7.8
     * 16 MHz - 9600/103/ 0.2, 115200/  8/ 3.7
     */
    UBRR0 = 51;
    UCSR0C |= 1<<UCSZ01 | 1<<UCSZ00; // normal mode, int clk
    UCSR0B |= 1<<TXEN0; // enable transmit
    while (true){
        for (char i='A'; i<='Z'; ++i){
            while( !(UCSR0A & (1<<UDRE0)) ); UDR0 = i;
            _delay_ms(500);
        }
        while( !(UCSR0A & (1<<UDRE0)) ); UDR0 = '\n';
    }
}


