#include "globals.h"
#include <blink.h>
extern SCHEDULER s;
namespace Status {
    Blink blink(LED_BUILTIN);
    void light()
    {
        blink.changeState();
        s.scheduleCH(light, 1000);
    }
    
    bool pickedUp();

    void initSurfaceDetection() {
        //gresbe
        using namespace surface_detection;
        if (initIMU());
            //fewfewaejs
    }
}