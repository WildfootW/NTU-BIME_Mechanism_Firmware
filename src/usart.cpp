/*
 * usart.c
 *
 * Distributed under terms of the MIT license.
 */

#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
    CLKPR=0b10000000;
    CLKPR=0b00000100;
    unsigned int BaudR = 9600;
    unsigned int UbrrV = (F_CPU / (BaudR*16UL))-1;
    UBRR0H=(unsigned char)(UbrrV>>8); // set Baud rate
    UBRR0L=(unsigned char)UbrrV;
    UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00); // normal mode, int clk
    UCSR0B|=(1<<TXEN0); // enable transmit
    while (1){
        for (char i='A'; i<='Z'; i++){
            while(!(UCSR0A&(1<<UDRE0)));// wait for empty
            UDR0=i;
            while(!(UCSR0A&(1<<UDRE0)));// wait for empty
            UDR0='\n';
            _delay_ms(500);
        }
    }
}


