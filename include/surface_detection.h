#pragma once
namespace surface_detection
{
    const int maxRadDeviation = 10;

    bool inAir();
    void surfaceDetection();
    bool initSurfaceDetection();
}