#include "pixy_interface.h"
#include <SPI.h>
#include <Pixy.h>

namespace pixy_interface
{
    Pixy pixy;
    int blocksDetected = 0;
    int biggestIndex = 0;
    void findBiggestDetection()
    {
        if (blocksDetected == 0)
            return;
        biggestIndex = 0;
        int biggestArea = 0;
        for (int i = 0; i < blocksDetected; i++)
        {
            int area = pixy.blocks[i].width * pixy.blocks[i].height;
            if (area > biggestArea)
            {
                biggestIndex = i;
                biggestArea = area;
            }
        }
        biggestDetection.x = pixy.blocks[biggestIndex].x;
        biggestDetection.y = pixy.blocks[biggestIndex].y;
        biggestDetection.width = pixy.blocks[biggestIndex].width;
        biggestDetection.height = pixy.blocks[biggestIndex].height;
    }

    bool poll()
    {
        // read from camera
        blocksDetected = pixy.getBlocks();
        if (blocksDetected > 0)
        {
            // cache the index of the biggest block
            findBiggestDetection();
            pixy.setLED(0, 255, 0);
            return true;
        }
        else
        {
            pixy.setLED(255, 0, 0);
            return false;
        }
    }

    void test()
    {
        Serial.print(blocksDetected + " blocks detected.");
        for (int i = 0; i < blocksDetected; i++)
        {
            if (i == biggestIndex)
                Serial.print("!");
            pixy.blocks[i].print();
        }
    }
}
