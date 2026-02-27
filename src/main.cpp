#include <Arduino.h>
#include "globals.h"
#include "status.h"
#include "sensor_interface.h"
unsigned long SCHEDULER::TIME::timeStamp; // this has to be refactored thats absurd
SCHEDULER s;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  s.scheduleRT(STATUS::init);
  s.scheduleCH(sensor_interface::init, 200); // value can be changed
}

void loop()
{
  s.cycle();
}