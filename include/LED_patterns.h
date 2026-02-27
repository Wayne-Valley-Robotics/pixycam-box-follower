#pragma once
#include <Arduino.h>

class LED_PATTERNS
{
private:
    int lastPattern = 0;

public:
    int blink();
    int pulse();
};