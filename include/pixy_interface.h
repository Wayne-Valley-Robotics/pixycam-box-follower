#pragma once
namespace pixy_interface
{
    // void findBiggestDetection();
    struct
    {
        // return center x from 0-319
        int x;
        // return center y from 0-199
        int y;
        // return width from 1-320
        int width;
        // return height from 1-200
        int height;
    } biggestDetection;
    // Poll new data from PixyCam. Returns true if an object is detected.
    bool poll();
    // Print debug data to Serial monitor. The biggest detection is prefixed with '!'
    void test();
}
