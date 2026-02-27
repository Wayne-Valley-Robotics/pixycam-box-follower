#include <Arduino.h>
#include "globals.h"
#include "status.h"
unsigned long SCHEDULER::TIME::timeStamp; // this has to be refactored thats absurd
SCHEDULER s;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  s.scheduleRT(STATUS::init);
}

void loop()
{
  s.cycle();
}