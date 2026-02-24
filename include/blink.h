#pragma once
#include <Arduino.h>

class Blink
{
public:
    Blink(int pin);
    void changeState();
};