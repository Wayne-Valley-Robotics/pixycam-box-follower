#include <Arduino.h>
#include "globals.h"
#include "status.h"
#include "sensor_interface.h"
#include "motor_interface.h"
#include "line_follower.h"
SCHEDULER s;

void printValues();

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);
  Serial.println("Hello!");
  s.scheduleRT(STATUS::init);
  s.scheduleRT(motor_interface::init);       // simple
  s.scheduleCH(sensor_interface::init, 200); // value can be changed
  s.scheduleCH(line_follower::init, 15000);  // sensor takes forever anyway
}

void loop()
{
  s.cycle();
}

void printValues()
{
  sensor_interface::printValues();
}