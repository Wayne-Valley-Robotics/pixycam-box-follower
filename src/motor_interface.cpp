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
        struct
        {
            uint8_t L_F;
            uint8_t L_B;
            uint8_t R_F;
            uint8_t R_B;
        } speeds;

        speedL = constrain(speedL, -255, 255);
        speedR = constrain(speedR, -255, 255);

        // logic should still cover them both being 0
        if (speedL > 0)
        {
            speeds.L_F = abs(speedL);
            speeds.L_B = 0;
        }
        else
        {
            speeds.L_F = 0;
            speeds.L_B = abs(speedL);
        }

        if (speedR > 0)
        {
            speeds.R_F = abs(speedR);
            speeds.R_B = 0;
        }
        else
        {
            speeds.R_F = 0;
            speeds.R_B = abs(speedR);
        }

        analogWrite(L_F, speeds.L_F);
        analogWrite(L_B, speeds.L_B);
        analogWrite(R_F, speeds.R_F);
        analogWrite(R_B, speeds.R_B);
    }

    void brake()
    {
        drive(0, 0);
    }
}