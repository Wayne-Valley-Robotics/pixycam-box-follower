#pragma once
#include <Arduino.h>

class LED_PATTERNS
{
private:
    int lastPattern;

public:
    int blink();
    int pulse();
};