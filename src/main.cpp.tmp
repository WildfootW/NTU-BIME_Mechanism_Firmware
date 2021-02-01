/*
 * main.cpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (ɔ) 2020-2021 WildfootW all rights reversed
 */

#include "avr-utils/IOPin.hpp"

#include "avr-utils/USART.hpp"
USART usart(9600);

void initial()
{
    CLKPR = (1 << CLKPCE); // clock prescaler change enable
    CLKPR = 0b00000100; // set clk to 1 Mhz (16 / 16)

    usart.initial();
}

int main(void)
{
    initial();

    while(true)
    {
        char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
        usart.put_str(str);
    }
}

