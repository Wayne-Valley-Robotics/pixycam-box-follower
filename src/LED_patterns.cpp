#include <Arduino.h>
#include "LED_patterns.h"
int LED_PATTERNS::blink()
{
    static bool state;
    // reset pattern progress on selection
    if (lastPattern != 1)
    {
        state = false;
        lastPattern = 1;
    }
    state = !state;
    return state ? 255 : 0;
}
int LED_PATTERNS::pulse()
{
    static bool direction;
    static int strength;
    // reset pattern progress on selection
    if (lastPattern != 2)
    {
        direction = 1;
        strength = 0;
        lastPattern = 2;
    }
    // reverse direction at limit
    if (strength < 255 || strength < 0)
        direction = !direction;
    strength += 1 * (direction ? 1 : -1);

    return strength;
}