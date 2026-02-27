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
        bool lockState = false;
        void lock()
        {
            lockState = true;
        }
        void unlock()
        {
            lockState = false;
            s.scheduleRT(ledPatternFallback);
        }
        LED_PATTERNS statusLED;
        int speed = 2000; // sensible default, though it should be impossible for the user to not define
        // initialize pattern
        void calibration(int speed_)
        {
            analogWrite(LED_BUILTIN, statusLED.pulse());
            lock();
            speed = 255 / speed_;
            s.scheduleCH(calibration, speed);
        }
        void calibration()
        {
            analogWrite(LED_BUILTIN, statusLED.pulse());
            s.scheduleCH(calibration, speed);
        }
        // initialize pattern
        void blink(int speed_)
        {
            analogWrite(LED_BUILTIN, statusLED.blink());
            speed = speed_;
            s.scheduleCH(blink, speed);
        }
        void blink()
        {
            analogWrite(LED_BUILTIN, statusLED.blink());
        }
    }

    int fallbackPulseSpeed;

    void ledPatternFallback()
    {
        if (!LED::lockState)
        {
            // manually define speed to skip locking
            LED::speed = fallbackPulseSpeed;
            LED::calibration();
        }
    }

    void initSurfaceDetection()
    {
        if (surface_detection::initSurfaceDetection())
            s.schedulePI(surface_detection::surfaceDetection, 200);
    }
    bool inAir()
    {
        return surface_detection::inAir();
    }
    void init()
    {
        s.schedulePI(initSurfaceDetection, 150);
    }
}