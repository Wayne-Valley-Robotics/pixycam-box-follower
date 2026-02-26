#include <Arduino.h>
#include <Arduino_LSM6DS3.h>

namespace surface_detection {

// Initialize the onboard IMU
bool initIMU()
{
    if (!IMU.begin()) {
        return false;
    }

    // Optionally enable the built-in sampling (not required here).
    // Leave default ranges and data rates as configured by the library.
    return true;
}

// Read acceleration in m/s^2. Returns true if data was read.
bool readAcceleration(float &ax, float &ay, float &az)
{
    if (!IMU.accelerationAvailable()) return false;
    return IMU.readAcceleration(ax, ay, az);
}

// Read gyroscope in rad/s. Returns true if data was read.
bool readGyroscope(float &gx, float &gy, float &gz)
{
    if (!IMU.gyroscopeAvailable()) return false;
    return IMU.readGyroscope(gx, gy, gz);
}

// Read temperature in degrees Celsius. Returns true if data was read.
bool readTemperature(float &t)
{
    if (!IMU.temperatureAvailable()) return false;
    return IMU.readTemperature(t);
}

} // namespace surface_detection
