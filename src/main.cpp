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
  pixy_interface::tick();
  pixy_interface::test();

  int maxSpeed = 255;

  int xBias = map(pixy_interface::biggestDetection.x, 0, 319, -maxSpeed, maxSpeed);
  int speedL = maxSpeed - (abs(xBias) * xBias > 0);
  int speedR = maxSpeed - (abs(xBias) * xBias < 0);
  // motor_interface::drive(speedL,speedR);
}