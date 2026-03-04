#include <Arduino.h>
#include "QTRSensors.h"
#include "sensor_interface.h"
#include "globals.h"
#include "status.h"
#include <surface_detection.h>
#include <motor_interface.h>
namespace sensor_interface
{

    QTRSensors qtr;

    extern const uint8_t SensorCount;
    extern const uint8_t EmitterPin;
    extern const uint8_t SensorPins[SensorCount];
    uint16_t sensorValues[SensorCount];

    // linePosition result from 0-8000
    uint16_t position = 0;

    uint16_t calibrationIterations = 0;
    bool calibrated = false;

    void init()
    {
        // configure the sensors
        qtr.setTypeAnalog();
        qtr.setSensorPins(SensorPins, SensorCount);
        qtr.setEmitterPin(EmitterPin);

        STATUS::LED::blink(100);             // blink 5 times on boot
        s.scheduleCH(beginCalibration, 500); // keep this value
    }
    bool isCalibrated()
    {
        return calibrated;
    }
    void beginCalibration()
    {
        if (!surface_detection::inAir)
        {
            Serial.println("Beginning Sensor Calibration...");
            STATUS::endSurfaceDetection();
            STATUS::LED::blink(500);
            motor_interface::drive(-calibrationMotorSpeed, calibrationMotorSpeed);
            s.scheduleRT(calibrationProc);
        }
        else
        {
            s.schedulePI(beginCalibration, 251);
        }
    }
    void calibrationProc()
    {
        // analogRead() takes about 0.1 ms on an AVR.
        // 0.1 ms per sensor * 4 samples per sensor read (default) * 8 sensors
        // * 10 reads per calibrate() call = ~32 ms per calibrate() call.
        // Call calibrate() 400 times to make calibration take about 12.8 seconds.

        if (surface_detection::inAir)
        {
            Serial.println(F("Calibration interrupted!"));
            // STATUS::LED::unlock();
            calibrationIterations = 0;
            s.schedulePI(beginCalibration, 250);
        }
        else
        {
            if (calibrationIterations <= 400)
            {
                if (calibrationIterations % 4 == 0)
                    Serial.print(F("#"));

                qtr.calibrate();
                calibrationIterations++;
                s.scheduleRT(calibrationProc);
            }
            else
            {
                calibrated = true;
                Serial.println(F("\nCalibrated Sensor Array."));
                STATUS::LED::unlock();
                STATUS::initSurfaceDetection();
                s.scheduleRT(findLinePosition);
            }
        }
    }

    uint16_t getLinePosition()
    {
        if (!calibrated)
        {
            return 0;
        }
        return position;
    }

    void findLinePosition()
    {
        if (!calibrated)
        {
            return;
        }
        // read calibrated sensor values and obtain a measure of the line position
        // from 0 to 8000 (for a white line, use readLineWhite() instead)
        position = qtr.readLineBlack(sensorValues);

        // print the sensor values as numbers from 0 to 1000, where 0 means maximum
        // reflectance and 1000 means minimum reflectance, followed by the line
        // position
        // for (uint8_t i = 0; i < SensorCount; i++)
        // {
        //     Serial.print(sensorValues[i]);
        //     Serial.print('\t');
        // }
        // Serial.println(position);

        s.scheduleCH(findLinePosition, 250); // do not change value
    }
    void printValues()
    {
        if (!calibrated)
        {
            return;
        }
        // Read from each sensor
        qtr.read(sensorValues);
        for (uint8_t i = 0; i < SensorCount; i++)
        {
            Serial.print(sensorValues[i]);
            Serial.print(",");
        }
    }
}
