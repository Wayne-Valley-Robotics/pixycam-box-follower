#include <Arduino.h>
#include "motor_interface.h"
#include "follow_box.h"

const int maxSpeed = 255;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Hello!");
  delay(5000);

  // IMU_interface::init();
  motor_interface::init();
}

void loop()
{
  follow_box::tick();
}
