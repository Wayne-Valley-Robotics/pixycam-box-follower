#pragma once
#include "Arduino.h"
// A2
const uint8_t L_F = 12;
// A1
const uint8_t L_B = 11;
// B1
const uint8_t R_F = 9;
// B2
const uint8_t R_B = 10;
namespace motor_interface
{
    void init();
    void drive(int speedL, int speedR);
    void brake();
    void test();
}