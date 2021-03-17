/*
 * main.cpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (ɔ) 2020-2021 WildfootW all rights reversed
 */

#include "avr-utils/IOPin.hpp"

#include "avr-utils/USART.hpp"
USART<115200> usart;

void initial()
{
    CLKPR = (1 << CLKPCE); // clock prescaler change enable
  //CLKPR = 0b00000100; // set clk to 1 Mhz (16 / 16)
    CLKPR = 0b00000000; // set clk to 16 Mhz (16 / 1)

    usart.initial();
}

int main(void)
{
    initial();

    while(true)
    {
        char str[] = "WildfootW\n";
        usart.put_str(str);
    }
}

