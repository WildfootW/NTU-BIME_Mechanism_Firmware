/*
 * usart.c
 *
 * Distributed under terms of the MIT license.
 */

#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
    CLKPR = 0b10000000;

//    CLKPR = 0b00000100; // 16 MHz / 16
//#define F_CPU  1000000UL

    CLKPR = 0b00000000; // 16 MHz / 1
#define F_CPU 16000000UL

    /*
     * 16 MHz - 9600/103/ 0.2, 115200/  8/ 3.7
     * 1  MHz - 9600/  6/ 7.5, 115200/  0/84.3
     */
    UBRR0 = 103;
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


