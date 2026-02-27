#include <Arduino.h>
#include "QTRSensors.h"
#include "sensor_interface.h"
#include "globals.h"
#include "status.h"
namespace sensor_interface
{

    QTRSensors qtr;

    const uint8_t SensorCount = 8;
    uint16_t sensorValues[SensorCount];
    const uint8_t SensorPins[SensorCount];

    // linePosition result from 0-8000
    uint16_t position = 0;

    uint16_t calibrationIterations = 0;


    void init()
    {
        // configure the sensors
        qtr.setTypeAnalog();
        qtr.setSensorPins(SensorPins, SensorCount);
        qtr.setEmitterPin(2);

        STATUS::LED::blink(100); // blink 5 times on boot
        s.scheduleCH(beginCalibration, 500); // keep this value
    }
    void beginCalibration()
    {
        STATUS::LED::calibration(2000);

        // analogRead() takes about 0.1 ms on an AVR.
        // 0.1 ms per sensor * 4 samples per sensor read (default) * 8 sensors
        // * 10 reads per calibrate() call = ~32 ms per calibrate() call.
        // Call calibrate() 400 times to make calibration take about 12.8 seconds.

        if (calibrationIterations <= 400)
        {
            qtr.calibrate();
            calibrationIterations++;
            s.scheduleRT(beginCalibration);
        } else {
            STATUS::LED::unlock();
        }
    }

    void linePosition()
    {
        // read calibrated sensor values and obtain a measure of the line position
        // from 0 to 5000 (for a white line, use readLineWhite() instead)
        position = qtr.readLineBlack(sensorValues);

        // print the sensor values as numbers from 0 to 1000, where 0 means maximum
        // reflectance and 1000 means minimum reflectance, followed by the line
        // position
        for (uint8_t i = 0; i < SensorCount; i++)
        {
            Serial.print(sensorValues[i]);
            Serial.print('\t');
        }
        Serial.println(position);

        s.scheduleCH(linePosition, 250); // do not change value
    }
}
