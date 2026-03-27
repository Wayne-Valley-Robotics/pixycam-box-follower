#include <Arduino.h>
#include "follow_box.h"
#include "pixy_interface.h"
#include "motor_interface.h"
namespace follow_box
{
    using namespace pixy_interface;  // pixy_interface::poll() becomes poll()
    using namespace motor_interface; // motor_interface::drive() becomes drive()

    void tick()
    {
        // does pixycam see the object?
        if (poll())
            follow();
        else
            // no object is detected
            brake();
    }
    void follow()
    {
        // object is detected

        int speedL = 255;
        int speedR = -255;
        drive(speedL, speedR);
    }
}