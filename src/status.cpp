#include "globals.h"
#include <LED_patterns.h>
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
            lock(2);
            analogWrite(LED_BUILTIN, statusLED.pulse());
            speed = 255 / speed_;
            s.scheduleCH(calibration, speed);
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
            lock(1);
            digitalWrite(LED_BUILTIN, statusLED.blink());
            speed = speed_;
            s.scheduleCH(blink, speed);
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
            s.schedulePI(surface_detection::surfaceDetection, 200);
        }
        else
        {
            Serial.println("Failed to initialize IMU!");
            LED::blink(800);
        }
    }
    bool inAir()
    {
        return surface_detection::inAir();
    }
    void init()
    {
        ledPatternFallback();
        // s.schedulePI(initSurfaceDetection, 150);
    }
}
