#include <Arduino.h>
#include <Arduino_LSM6DS3.h>
#include "globals.h"
#include "IMU_interface.h"
#include "surface_detection.h"

namespace surface_detection
{
    bool active = false;
    bool inAir = true;

    // check if delta from a to b is greater than maxDeviation
    bool checkDeviation(int a, int b, int maxDeviation)
    {
        return (abs(b) - abs(a)) > abs(maxDeviation);
    }

    bool isLevel()
    {
        static bool level;
        using namespace IMU_interface;
        static float gx1, gy1, gz1;
        float gx2, gy2, gz2;
        if (!IMU.readGyroscope(gx2, gy2, gz2))
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
        gx1 = gx2; // pitch
        gy1 = gy2; // roll
        gz1 = gz2; // yaw
        Serial.print(gx1);
        Serial.print("\t");
        Serial.print(gy1);
        Serial.print("\t");
        Serial.println(gz1);
        return level;
    }

    float maxAccDeviation = maxAccDeviationPickUp;
    bool isAcc()
    {
        static bool acc;
        using namespace IMU_interface;
        // static float ax1, ay1, az1;
        float ax2, ay2, az2;
        // int out = IMU.accelerationAvailable();
        // Serial.println(out);

        if (!IMU.accelerationAvailable())
            return acc;

        // // for all things checkDeviation
        // float currentValues[3] = {ax2, ay2, az2};
        // float cachedValues[3] = {ax1, ay1, az1};
        // float score = 0;
        // for (int i = 0; i < 3; i++)
        // {
        //     if (checkDeviation(currentValues[i], cachedValues[i], maxAccDeviation))
        //         score++;
        // }
        // acc = (score == 0);

        // // cache new values
        // ax1 = ax2; // away from port, the long way
        // ay1 = ay2; // text upside down if looking at the side with pins
        // az1 = az2; // up is up if the pins were facing down
        // Serial.print(ax1);
        // Serial.print("\t");
        // Serial.print(ay1);
        // Serial.print("\t");
        // Serial.println(az1);
        IMU.readAcceleration(ax2, ay2, az2);
        acc = (-az2 < (1 - maxAccDeviation));

        // if (acc)
        //     Serial.println(-az2);

        return acc;
    }
    // bool inAir;
    void surfaceDetection()
    {
        if (isAcc())
        {
            if (!inAir)
            {
                inAir = true;
                STATUS::LED::blink(100);
                Serial.println(F("put me down!"));
                maxAccDeviation = maxAccDeviationSetDown;
            }
        }
        else
        {
            if (inAir)
            {
                inAir = false;
                STATUS::LED::unlock();
                Serial.println(F("yay"));
                maxAccDeviation = maxAccDeviationPickUp;
            }
        }
        if (active)
            s.scheduleCH(surfaceDetection, 250);
    }

    // initialize IMU and surface detection. returns false on failure to initialize IMU.
    bool initSurfaceDetection()
    {
        if (IMU_interface::initIMU())
        {
            // STATUS::LED::unlock(); // why is this here?
            active = true;
            s.schedulePI(surface_detection::surfaceDetection, 200);
            return true;
        }
        return false;
    }
    void endSurfaceDetection()
    {
        IMU_interface::endIMU();
        active = false;
    }

} // namespace surface_detection
