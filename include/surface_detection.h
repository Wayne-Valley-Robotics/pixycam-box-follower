#pragma once
namespace surface_detection
{
    int maxRadDeviation = 10;

    bool inAir();
    void surfaceDetection();
    bool initSurfaceDetection();
}