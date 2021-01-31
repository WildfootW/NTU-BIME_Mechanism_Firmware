/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2021 WildfootW all rights reversed
 *
 */

#ifndef BASICSENSOR_HPP
#define BASICSENSOR_HPP

#include <stdint.h>

class BasicSensor
{
public:
    BasicSensor(){}
    void value_update(uint8_t input_value);
protected:
    uint16_t mix_value;
};

#endif //BASICSENSOR_HPP
