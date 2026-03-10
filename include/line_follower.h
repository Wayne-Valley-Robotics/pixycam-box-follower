#pragma once

namespace line_follower
{
    // 0-255
    const int maxSpeed = 255;
    // the speed of the inside tire once outside the line
    const int minSpeed = 0;
    const int sensitivityMultiplier = 1;
    const int waitReadyDelay = 2000;
    void init();
    void checkReady();
    void waitReady();
    void followLine();
    int p();
}