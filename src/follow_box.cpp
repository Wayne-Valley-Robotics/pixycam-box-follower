#include <Arduino.h>
#include <pixy_interface.h>
#include <motor_interface.h>
namespace follow_box
{
    void follow()
    {
        using namespace pixy_interface;  // pixy_interface::poll() becomes poll()
        using namespace motor_interface; // motor_interface::drive() becomes drive()
        // does pixycam see the object?
        if (poll())
        {
            // object is detected

            int speedL = 255;
            int speedR = -255;
            drive(speedL, speedR);
        }
        else
        {
            // no object is detected
            brake();
        }
    }
}