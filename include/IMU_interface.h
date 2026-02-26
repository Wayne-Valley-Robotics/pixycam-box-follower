#pragma once
namespace IMU_interface
{
    bool initIMU();
    bool readAcceleration(float &ax, float &ay, float &az);
    bool readGyroscope(float &gx, float &gy, float &gz);
    bool readTemperature(float &t);
}