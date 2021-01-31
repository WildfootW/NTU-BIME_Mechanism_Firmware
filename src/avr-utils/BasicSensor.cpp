/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#include "BasicSensor.hpp"

/* BasicSensor */
void BasicSensor::value_update(uint8_t input_value)
{
    unsigned int new_value = (mix_value * 9) + input_value;
    mix_value = new_value / 10;
}

