#include "globals.h"
#include <blink.h>
#include "surface_detection.h"
extern SCHEDULER s;
namespace Status
{
    bool initializedIMU;
    Blink blink(LED_BUILTIN);
    void light()
    {
        blink.changeState();
        s.scheduleCH(light, 400);
    }

    void initSurfaceDetection()
    {
        if (surface_detection::initSurfaceDetection())
            s.schedulePI(surface_detection::surfaceDetection, 200);
    }
}