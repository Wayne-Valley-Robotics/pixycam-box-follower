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
        if (speedL > 0)
        {
            analogWrite(L_F, speedL);
            analogWrite(L_B, 0);
        }
        else
        {
            analogWrite(L_F, 0);
            analogWrite(L_B, speedL);
        }

        if (speedR > 0) {
            analogWrite(R_F, speedL);
            analogWrite(R_B, 0);
        }
        else {
            analogWrite(R_F, 0);
            analogWrite(R_B, speedL);
        }
    }

    void brake()
    {
        drive(0, 0);
    }
}