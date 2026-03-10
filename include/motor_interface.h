#pragma once
#include "Arduino.h"
// A1
const uint8_t L_F = 11;
// A2
const uint8_t L_B = 12;
// B2
const uint8_t R_F = 10;
// B1
const uint8_t R_B = 9;
namespace motor_interface
{
    void init();
    void drive(int speedL, int speedR);
    void brake();
    void test();
}