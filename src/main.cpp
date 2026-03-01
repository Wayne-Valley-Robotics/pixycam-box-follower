#include <Arduino.h>
#include "globals.h"
#include "status.h"
#include "sensor_interface.h"
#include "motor_interface.h"
SCHEDULER s;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);
  Serial.println("Hello!");
  s.scheduleRT(STATUS::init);
  // s.scheduleCH(sensor_interface::init, 200); // value can be changed
  s.scheduleCH(motor_interface::init, 2000);
}

void loop()
{
  s.cycle();
}