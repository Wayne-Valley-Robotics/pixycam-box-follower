#pragma once
#include "Arduino.h"
namespace sensor_interface
{
    const uint8_t SensorPins[SensorCount] = {A0, A1, A2, A3, A4, A5, A7, 1};

    extern uint16_t position;
    void init();
    void beginCalibration();
    void linePosition();
}