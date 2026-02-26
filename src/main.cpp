#include <Arduino.h>
#include "globals.h"
#include "status.h"

void setup()
{
  Serial.begin(115200);
  s.schedulePI(Status::Light, 400);
}

void loop()
{
  s.cycle();
}