/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef WHEELCONTROL_H
#define WHEELCONTROL_H
/*
 * class design for Arduino uno & L298 H-bridge controling two DC motor wheels.
 */

class WheelControl
{
public:
#if with_enable_line
    WheelControl(byte pin_a, byte pin_b, byte pin_en): pin_a(pin_a), pin_b(pin_b), pin_en(pin_en) {} // digital, digital, pwm
    void initial(double ratio = 1) { pinMode(pin_a, OUTPUT); pinMode(pin_b, OUTPUT); pinMode(pin_en, OUTPUT); output_ratio = ratio; }
#else
    WheelControl(byte pin_a, byte pin_b): pin_a(pin_a), pin_b(pin_b) {} // pwm, pwm
    void initial(double ratio = 1) { pinMode(pin_a, OUTPUT); pinMode(pin_b, OUTPUT); output_ratio = ratio; }
#endif // with_enable_line
    void set_speed(uint8_t speed, bool backward = false) { forward = !backward; current_speed = speed * output_ratio; }
    void execute() const
    {
#ifndef NDEBUG
        Serial.println(current_speed);
#endif // NDEBUG
#if with_enable_line
        analogWrite(pin_en, current_speed);
        if(forward) { digitalWrite(pin_a, HIGH); digitalWrite(pin_b, LOW ); }
        else        { digitalWrite(pin_a, LOW ); digitalWrite(pin_b, HIGH); }
#else
        if(forward) { analogWrite(pin_a, current_speed); digitalWrite(pin_b, LOW ); }
        else        { digitalWrite(pin_a, LOW ); analogWrite(pin_b, current_speed); }
#endif // with_enable_line
    }
private:
    const byte pin_a, pin_b;
#if with_enable_line
    const byte pin_en;
#endif // with_enable_line
    bool forward;
    uint8_t current_speed;
    double output_ratio;
};

class PairWheelControl
{
public:
#if with_enable_line
    PairWheelControl(byte pin_a_l, byte pin_b_l, byte pin_en_l,     // digital, digital, pwm
                     byte pin_a_r, byte pin_b_r, byte pin_en_r):    // digital, digital, pwm
                     wheel_l(pin_a_l, pin_b_l, pin_en_l),
                     wheel_r(pin_a_r, pin_b_r, pin_en_r) {}
#else
    PairWheelControl(byte pin_a_l, byte pin_b_l,                        // pwm, pwm
                     byte pin_a_r, byte pin_b_r):                       // pwm, pwm
                     wheel_l(pin_a_l, pin_b_l),
                     wheel_r(pin_a_r, pin_b_r) {}
#endif // with_enable_line
    void initial(double speed_ratio = 1)    // speed_ratio = speed_l / speed_r;
    {
        global_ratio = 1;
        if(speed_ratio > 1) { wheel_l.initial(1 / speed_ratio); wheel_r.initial(1);           }
        else                { wheel_l.initial(1);               wheel_r.initial(speed_ratio); }
    }
    void set_speed(uint8_t speed_l, uint8_t speed_r, bool backward_l = false, bool backward_r = false) const
    {
        wheel_l.set_speed(speed_l * global_ratio, backward_l);
        wheel_r.set_speed(speed_r * global_ratio, backward_r);
    }
    PairWheelControl& set_global_ratio(double ratio) { global_ratio = ratio ; return (*this); }
    PairWheelControl& keep(unsigned int time) { delay(time); return (*this); }

    PairWheelControl& go(uint8_t speed_amount, bool backward = false)
    {
        if(!backward) { set_speed(speed_amount, speed_amount); }
        else          { set_speed(speed_amount, speed_amount, true, true); }
        execute(); return (*this);
    }
    PairWheelControl& rotate(uint8_t speed_amount, bool clockwise = false)
    {
        if(clockwise) set_speed(speed_amount, speed_amount, false, true);
        else          set_speed(speed_amount, speed_amount, true, false);
        execute(); return (*this);
    }
    PairWheelControl& turn(int8_t steer_amount)
    {
        if(steer_amount == 0) set_speed(255, 255);
        if(steer_amount >  0) set_speed(255 - (steer_amount * 2), 255);
        if(steer_amount <  0) set_speed(255, 255 + (steer_amount * 2));
        execute(); return (*this);
    }

private:
    WheelControl wheel_l, wheel_r;
    double global_ratio;
    void execute() const
    {
#ifndef NDEBUG
        Serial.print("lleft: ");
#endif // NDEBUG
        wheel_l.execute();
#ifndef NDEBUG
        Serial.print("right: ");
#endif // NDEBUG
        wheel_r.execute();
    }
};
#endif //WHEELCONTROL_H

