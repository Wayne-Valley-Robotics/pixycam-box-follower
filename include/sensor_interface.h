#pragma once
#include "Arduino.h"
namespace sensor_interface
{
    const uint8_t SensorCount = 8;
    const uint8_t EmitterPin = 7;
    const uint8_t SensorPins[SensorCount] = {A0, A1, A2, A3, A4, A5, A7};

    extern uint16_t position;
    void init();
    void beginCalibration();
    void calibrationProc();
    void linePosition();
    // print values from each sensor
    void printValues();
}