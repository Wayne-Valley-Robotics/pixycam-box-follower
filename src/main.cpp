#include <Arduino.h>
#include "blink.h"

// put function declarations here:

Blink blink(LED_BUILTIN);

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  blink.changeState();
  delay(1000);
}

// put function definitions here:
