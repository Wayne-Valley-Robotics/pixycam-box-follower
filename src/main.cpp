#include <Arduino.h>
#include "scheduler.h"

SCHEDULER s;

void setup()
{
  Serial.begin(115200);
  s.scheduleCH(Status_Light, 1000);
}

void loop()
{
  s.cycle();
  delay(1000);
}