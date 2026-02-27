#pragma once
#include <LED_patterns.h>
namespace STATUS
{
    namespace LED
    {
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