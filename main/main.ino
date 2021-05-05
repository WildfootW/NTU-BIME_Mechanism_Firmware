/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#include "Setting.h"
#include "WheelControl.h"
#include "RouteDetector.h"

// with enable line:
// pin_a_l, pin_b_l, pin_en_l, pin_a_r, pin_b_r, pin_en_r
PairWheelControl pair_wheel(2, 4, 3, 7, 8, 9);
// without enable line
//PairWheelControl pair_wheel(5, 6, 10, 11);

// pin_l, pin_c, pin_r
RouteDetector route_detector(A1, A2, A3);

void setup()
{
    Serial.begin(115200);
    pair_wheel.initial(1);
    route_detector.initial(100, 100, 100);
    pair_wheel.set_global_ratio(1);
}

void loop()
{
    route_detector.sensor_value_update();
    RouteStatusType route_status = route_detector.get_current_status();
    switch(route_status)
    {
        case nnnone_on_line:
        {
            pair_wheel.go(255);
            break;
        }
        case center_on_line:
        {
            pair_wheel.go(255);
            break;
        }
        case llleft_on_line:
        {
            pair_wheel.turn(125);
            break;
        }
        case rright_on_line:
        {
            pair_wheel.turn(-125);
            break;
        }
        case aaaall_on_line:
        {
            pair_wheel.go(255);
            break;
        }
    }
}
