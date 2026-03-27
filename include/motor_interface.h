#pragma once
#include <Arduino.h>
namespace motor_interface
{
    // A1
    const uint8_t L_F = 11;
    // A2
    const uint8_t L_B = 10;
    // B2
    const uint8_t R_F = 6;
    // B1
    const uint8_t R_B = 5;
    // Configure pinModes
    void init();
    // Drive motors in either direction from -255 to 255
    void drive(int speedL, int speedR);
    // Stop all motors immediately
    void brake();
}