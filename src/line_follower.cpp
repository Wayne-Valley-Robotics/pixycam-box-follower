#include "globals.h"
#include "line_follower.h"
#include "sensor_interface.h"
#include "motor_interface.h"
#include <surface_detection.h>

namespace line_follower
{
    void init()
    {
        if (sensor_interface::isCalibrated())
            s.scheduleCH(veerToLine, 2000);
        else
            s.schedulePI(init, 250);
    }
    using namespace motor_interface;
    void veerToLine()
    {
        if (!surface_detection::inAir)
        {
            int linePosition = sensor_interface::getLinePosition();
            int favor = map(linePosition, 0, 8000, -255, 255);

            int favorR = 255 - constrain(favor, 0, 255);
            int favorL = 255 - abs(constrain(favor, -255, 0));

            drive(favorL, favorR);
            s.schedulePI(veerToLine, 12);
        }
        else
        {
            brake();
            s.scheduleCH(veerToLine, 2000);
        }
    }
}