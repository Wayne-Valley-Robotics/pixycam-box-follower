#pragma once

namespace line_follower
{
    // 0-255
    const int maxSpeed = 255;
    // the speed of the inside tire once outside the line
    const int minSpeed = 0;
    void init();
    void veerToLine();
}