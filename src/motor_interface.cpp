#include "motor_interface.h"
namespace motor_interface
{
    void init()
    {
        pinMode(L_F, OUTPUT);
        pinMode(L_B, OUTPUT);
        pinMode(R_F, OUTPUT);
        pinMode(R_B, OUTPUT);
    }

    void drive(int speedL, int speedR)
    {
        // TODO: analogWrite pwm pins based on inputs
    }

    void brake()
    {
        drive(0, 0);
    }
}