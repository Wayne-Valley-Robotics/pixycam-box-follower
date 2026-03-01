#pragma once
#include <LED_patterns.h>
namespace STATUS
{
    namespace LED
    {
        const int fallbackPulseSpeed = 3000;

        void lock();
        void unlock();
        void calibration(int speed);
        void calibration();
        void blink(int speed);
        void blink();
    }
    void ledPatternFallback();
    void init();
}