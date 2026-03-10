#include "globals.h"
#include <LED_patterns.h>
#include "sensor_interface.h"
#include "surface_detection.h"
#include "status.h"
extern SCHEDULER s;
namespace STATUS
{
    bool initializedIMU;
    namespace LED
    {
        int lockState = 0;
        void lock(int pattern)
        {
            lockState = pattern;
        }
        void unlock()
        {
            lockState = 0;
            s.scheduleRT(ledPatternFallback);
        }
        LED_PATTERNS statusLED;
        int speed = 2000; // sensible default, though it should be impossible for the user to not define
        // initialize pattern
        void calibration(int speed_)
        {
            speed = 255 / speed_;
            if (lockState != 2)
            {
                lock(2);
                analogWrite(LED_BUILTIN, statusLED.pulse());
                s.scheduleCH(calibration, speed);
            }
        }
        void calibration()
        {
            if (lockState == 2)
            {
                analogWrite(LED_BUILTIN, statusLED.pulse());
                s.scheduleCH(calibration, speed);
            }
        }
        // initialize pattern
        void blink(int speed_)
        {
            speed = speed_;
            if (lockState != 1)
            {
                lock(1);
                digitalWrite(LED_BUILTIN, statusLED.blink());
                s.scheduleCH(blink, speed);
            }
        }
        void blink()
        {
            if (lockState == 1)
            {
                digitalWrite(LED_BUILTIN, statusLED.blink());
                s.scheduleCH(blink, speed);
            }
        }
    }

    bool ledPatternFallbackActive = false;
    void ledPatternFallbackProc()
    {
        if (LED::lockState == 0)
        {
            ledPatternFallbackActive = true;
            // manually change state to skip lock()
            // digitalWrite(LED_BUILTIN, LED::statusLED.pulse());
            digitalWrite(LED_BUILTIN, LED::statusLED.blink());
            // s.scheduleCH(ledPatternFallbackProc, (255 / LED::fallbackPulseSpeed));
            s.scheduleCH(ledPatternFallbackProc, (LED::fallbackPulseSpeed));
        }
        else
        {
            ledPatternFallbackActive = false;
        }
    }
    void ledPatternFallbackChron()
    {
        if (LED::lockState == 0)
        {
            if (!ledPatternFallbackActive)
            {
                Serial.println("Idling");
                ledPatternFallbackProc();
            }
        }
        s.scheduleCH(ledPatternFallbackChron, 250);
    }
    void ledPatternFallback()
    {
        static bool running;

        if (!running)
        {
            ledPatternFallbackChron();
            running = true;
        }
        else
        {
            if (!ledPatternFallbackActive)
            {
                ledPatternFallbackProc();
            }
        }
    }

    void initSurfaceDetection()
    {
        if (surface_detection::initSurfaceDetection())
        {
            Serial.println("Initialized IMU!");
        }
        else
        {
            Serial.println("Failed to initialize IMU!");
            LED::blink(100);
        }
    }
    void endSurfaceDetection()
    {
        surface_detection::endSurfaceDetection();
        Serial.println("Disabled IMU.");
    }
    void init()
    {
        ledPatternFallback();
        s.schedulePI(initSurfaceDetection, 13);
    }
    bool ready()
    {
        int readyScore = 0;
        readyScore += !surface_detection::inAir;
        readyScore += sensor_interface::isCalibrated();
        return readyScore == 2;
    }
}
