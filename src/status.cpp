#include <blink.h>
Blink blink(LED_BUILTIN);
void StatusLight()
{
    blink.changeState();
}
