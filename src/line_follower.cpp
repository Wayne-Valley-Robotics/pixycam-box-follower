#include "globals.h"
#include "line_follower.h"
#include "sensor_interface.h"
#include "motor_interface.h"

namespace line_follower
{
    void init()
    {
        if (sensor_interface::isCalibrated())
            s.scheduleCH(followLine, 2000);
        else
            s.schedulePI(init, 253);
    }
    using namespace motor_interface;

    void checkReady()
    {
        if (STATUS::ready())
        {
            followLine();
            s.schedulePI(checkReady, 13);
        }
        else
        {
            brake();
            Serial.println("Paused line following.");
            s.schedulePI(waitReady, 247);
        }
    }
    // ensure 2 seconds have passed
    void waitReady()
    {
        if (STATUS::ready())
        {
            Serial.println("Resuming line following.");
            s.scheduleCH(checkReady, waitReadyDelay);
        }
        else
        {
            s.schedulePI(waitReady, 251);
        }
    }

    void followLine()
    {
        int linePosition = sensor_interface::getLinePosition();
        p(linePosition);
    }

    int p(int linePosition)
    {

        int favor = map(linePosition, 0, 8000, -255, 255);

        int favorL = maxSpeed - (constrain(favor, minSpeed, maxSpeed) * sensitivityMultiplier);
        int favorR = maxSpeed - (abs(constrain(favor, -maxSpeed, -minSpeed)) * sensitivityMultiplier);

        drive(favorL, favorR);
    }
}