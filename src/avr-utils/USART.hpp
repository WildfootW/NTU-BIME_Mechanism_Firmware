/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 *
 */


#ifndef USART_HPP
#define USART_HPP

class USART
{
public:
    USART(const unsigned long int& baud_rate = 9600): baud_rate(baud_rate){}
    void initial();
    void put_str(char* str_ptr);
private:
    const unsigned long int baud_rate; // Note: unsigned int: uint16_t
};

#endif //USART_HPP

