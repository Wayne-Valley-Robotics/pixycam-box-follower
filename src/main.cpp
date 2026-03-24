#include <Arduino.h>
#include <motor_interface.h>
#include <pixy_interface.h>

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Hello!");
  delay(5000);

  // IMU_interface::init();
  motor_interface::init();
  // pixy_interface::init();
}

void loop()
{
  pixy_interface::test();
}