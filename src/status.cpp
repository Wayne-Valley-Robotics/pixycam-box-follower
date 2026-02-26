#include "globals.h"
#include <blink.h>

namespace Status {
    Blink blink(LED_BUILTIN);
    void Light()
    {
        blink.changeState();
        s.scheduleCH(Light, 1000);
    }
    
    void PickedUp() {
        //gresbe
    }
}