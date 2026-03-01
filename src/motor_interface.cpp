#include "globals.h"
#include "motor_interface.h"
#include "sensor_interface.h"
#include "LED_patterns.h"
namespace motor_interface
{
    LED_PATTERNS motorPattern;
    void init()
    {
        pinMode(L_F, OUTPUT);
        pinMode(L_B, OUTPUT);
        pinMode(R_F, OUTPUT);
        pinMode(R_B, OUTPUT);
        s.schedulePI(test, 80);
    }
    void test()
    {
        static int i;
        if (i != 2)
        {
            int speed = motorPattern.pulse();
            analogWrite(L_F, 0);
            analogWrite(L_B, speed);
            analogWrite(R_F, 0);
            analogWrite(R_B, speed);
            Serial.println(speed);
            s.scheduleCH(test, 2000 / 255);
            if (speed == 0)
                i++; 
        }
    }
}