/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 * UCSR0C - Asynchronous/synchronous, parity, stop bit, and data size
 * UCSR0B - Mode Control
 * UCSR0A - Status
 * UBRR0H/L - Baud Rate
 * UDR0 - Shift (data) Register
 */

#ifndef USART_CPP
#define USART_CPP

#include "USART.hpp"
#include <avr/io.h>

constexpr uint16_t _calc_ubrr(const unsigned long int& baud_rate)
{
    uint16_t tmp = (((double)F_CPU / (baud_rate * 16)) - 1) * 10;
    if(tmp % 10 >= 5)
        return tmp / 10 + 1;
    else
        return tmp / 10;
}

template <uint32_t baud_rate>
void USART<baud_rate>::initial()
{
    // UBRR0
//    switch(baud_rate)
//    {
//        case 9600:   UBRR0 = 103 break;
//        case 115200: UBRR0 = 8;  break;
//    }
//    uint16_t ubrr = (F_CPU / (baud_rate * 16)) - 1;
//    UBRR0 = ubrr;
// [TODO]: Decide during compile time

    constexpr uint16_t ubrr = _calc_ubrr(baud_rate);
    UBRR0 = ubrr;

    // UCSR0C
    UCSR0C &= ~(1 << UMSEL01) & ~(1 << UMSEL00); // Asynchronous USART
    UCSR0C &= ~(1 << UPM01) & ~(1 << UPM00); // Parity Disabled
    UCSR0C &= ~(1 << USBS0); // Stop Bit 1-bit
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Data Bits 8-bit

    // UCSR0B
    UCSR0B |= (1 << TXEN0); // TX Enabled
//    UCSR0B |= (1 << RXEN0); // RX Enabled
}

template <uint32_t baud_rate>
void USART<baud_rate>::put_str(char* str_ptr)
{
    while(*str_ptr != '\0')
    {
        while(!(UCSR0A & (1 << UDRE0)));
        UDR0 = *str_ptr;
        ++str_ptr;
    }
}

#endif //USART_CPP
