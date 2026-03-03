#pragma once
namespace surface_detection
{
    const int maxRadDeviation = 10;
    const float maxAccDeviationPickUp = 0.2;
    const float maxAccDeviationSetDown = 0.08;

    extern bool inAir;
    void surfaceDetection();
    bool initSurfaceDetection();
    void endSurfaceDetection();
}