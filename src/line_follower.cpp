#include "globals.h"
#include "line_follower.h"
#include "sensor_interface.h"
#include "motor_interface.h"

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

    void checkReady()
    {
        if (STATUS::ready())
        {
            veerToLine();
            s.schedulePI(checkReady, 12);
        }
        else
        {
            brake();
            s.scheduleCH(checkReady, 2000);
        }
    }
    void veerToLine()
    {
        int linePosition = sensor_interface::getLinePosition();
        int favor = map(linePosition, 0, 8000, -255, 255);

        int favorL = maxSpeed - constrain(favor, minSpeed, maxSpeed);
        int favorR = maxSpeed - abs(constrain(favor, -maxSpeed, minSpeed));

        drive(favorL, favorR);
    }
}