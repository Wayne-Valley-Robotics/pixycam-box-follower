#pragma once
#include "Arduino.h"
namespace sensor_interface
{
    const int calibrationMotorSpeed = 150;
    const uint8_t SensorCount = 8;
    const uint8_t EmitterPin = 7;
    const uint8_t SensorPins[SensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7};

    constexpr int waitReadyDelay = 2000;

    extern uint16_t position;
    void init();
    void waitReady();
    bool isCalibrated();
    void beginCalibration();
    void calibrationProc();
    // retrieve latest stored line position from 0 to 8000
    uint16_t getLinePosition();
    // do not call
    void findLinePosition();
    // print values from each sensor
    void printValues();
}