/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */

#include "USART.hpp"
#include <avr/io.h>

void USART::initial()
{
    uint16_t ubrr = (F_CPU / (baud_rate * 16)) - 1;
    UBRR0 = ubrr;
    UCSR0B |= (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}
void USART::put_str(char* str_ptr)
{
    while(*str_ptr != '\0')
    {
        while(!(UCSR0A & (1 << UDRE0)));
        UDR0 = *str_ptr;
        ++str_ptr;
    }
}

