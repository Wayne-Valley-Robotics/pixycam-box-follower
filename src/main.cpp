#include <Arduino.h>
#include "blink.h"

// put function declarations here:

Blink blink(LED_BUILTIN);

void setup() {
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  blink.changeState();
  delay(1000);
}