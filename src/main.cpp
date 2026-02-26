#include <Arduino.h>
#include "globals.h"
#include "status.h"
unsigned long SCHEDULER::TIME::timeStamp;  // this has to be refactored thats absurd
SCHEDULER s;

void setup()
{
  Serial.begin(115200);
  s.schedulePI(Status::light, 255);
  s.schedulePI(Status::initSurfaceDetection, 150);
}

void loop()
{
  s.cycle();
}