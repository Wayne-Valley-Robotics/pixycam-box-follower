#include <Arduino.h>
#include <Arduino_LSM6DS3.h>
#include "IMU_interface.h"

namespace surface_detection
{

    bool onSurface;
    bool level()
    {
        int maxRadDeviation = 10;
        using namespace IMU_interface;
        static float gx1, gy1, gz1;
        float gx2, gy2, gz2;
        if (readGyroscope(gx2, gy2, gz2))
        {
            onSurface = ((gx2 + gy2 + gz2) > 10);
        }

        // for all things checkDeviation
        float dimensions[3] = {gx2, gy2, gz2};
        int cachedDimensions[3] = {gx1, gy1, gz1};
        for(int i = 0; i <= 3, )
        checkDeviation(gx1, gx2, maxRadDeviation);

        // cache new values
        gx1 = gx2;
        gy1 = gy2;
        gz1 = gz2;
        return onSurface;
    }

    // check if delta from a to b is greater than maxDeviation
    bool checkDeviation(int a, int b, int maxDeviation)
    {
        return (abs(b) - abs(a)) > abs(maxDeviation);
    }

    bool inAir()
    {
        // there are more factors that should be
        // evaluated, but this is enough for now
        return level();
    }

    bool initSurfaceDetection()
    {
        return IMU_interface::initIMU();
    }

    void surfaceDetection()
    {
        if (inAir())
        {
            Serial.println("put me down!");
        }
        else
        {
            Serial.println("yay");
        }
    }

} // namespace surface_detection
