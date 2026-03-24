#pragma once
#include <Arduino.h>
namespace motor_interface
{
    // A1
    const uint8_t L_F = 11;
    // A2
    const uint8_t L_B = 12;
    // B2
    const uint8_t R_F = 10;
    // B1
    const uint8_t R_B = 9;
    void init();
    void drive(int speedL, int speedR);
    void brake();
}