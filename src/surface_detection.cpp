#include <Arduino.h>
#include <Arduino_LSM6DS3.h>
#include "globals.h"
#include "IMU_interface.h"

namespace surface_detection
{
    // check if delta from a to b is greater than maxDeviation
    bool checkDeviation(int a, int b, int maxDeviation)
    {
        return (abs(b) - abs(a)) > abs(maxDeviation);
    }

    int maxRadDeviation;
    bool isLevel()
    {
        static bool level;
        using namespace IMU_interface;
        static float gx1, gy1, gz1;
        float gx2, gy2, gz2;
        if (!readGyroscope(gx2, gy2, gz2))
            return level;

        // for all things checkDeviation
        float currentValues[3] = {gx2, gy2, gz2};
        float cachedValues[3] = {gx1, gy1, gz1};
        float score = 0;
        for (int i = 0; i < 3; i++)
        {
            if (checkDeviation(currentValues[i], cachedValues[i], maxRadDeviation))
                score++;
        }
        level = (score == 0);

        // cache new values
        gx1 = gx2;
        gy1 = gy2;
        gz1 = gz2;
        Serial.println(gx1 + gy1 + gz1);
        return level;
    }

    bool inAir()
    {
        // there are more factors that should be
        // evaluated, but this is enough for now
        return isLevel();
    }

    void surfaceDetection()
    {
        if (inAir())
        {
            STATUS::LED::blink(500);
            Serial.println(F("put me down!"));
        }
        else
        {
            STATUS::LED::unlock();
            Serial.println(F("yay"));
        }
        // s.scheduleCH(surfaceDetection, 250);
    }

    // initialize IMU and surface detection. returns false on failure to initialize IMU.
    bool initSurfaceDetection()
    {
        if (IMU_interface::initIMU())
        {
            STATUS::LED::unlock();
            return true;
        }
        return false;
    }

} // namespace surface_detection
