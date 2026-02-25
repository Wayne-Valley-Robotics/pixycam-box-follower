#include <Arduino.h>
#include "blink.h"

Blink::Blink(int pin) : pin_(pin), state_(false)
{
    pinMode(pin_, OUTPUT);
    digitalWrite(pin_, LOW);
}

void Blink::changeState()
{
    state_ = !state_;
    digitalWrite(pin_, state_);
}