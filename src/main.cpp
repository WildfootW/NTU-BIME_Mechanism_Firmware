/*
 * main.cpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (ɔ) 2020-2021 WildfootW all rights reversed
 */

extern "C"
{
    #include <avr/interrupt.h>
}

#include "IOPin.hpp"

#include "Millis.hpp"
Millis millis; // Timer1

void initial()
{
    CLKPR = (1 << CLKPCE);
    CLKPR = 0b00000100; // set clk to 1 Mhz (16 / 16)

    millis.initial();

    pin_PD5::configure_pin_mode(AVRIOPinMode::Output);

    sei();
}

int main(void)
{
    initial();

    while(true)
    {
        if((millis.get() / 1000 / 5) % 2) // 5 seconds
            pin_PD5::set_output(true);
        else
            pin_PD5::set_output(false);

    }
}

ISR(TIMER1_COMPA_vect)
{
    millis.increase_millis();
}
