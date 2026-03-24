#include "pixy_interface.h"
#include <SPI.h>
#include <Pixy.h>

namespace pixy_interface
{
    Pixy pixy;
    int blocksDetected;
    int biggestIndex = 0;
    void findBiggestDetection()
    {
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

    void tick()
    {
        // read from camera
        blocksDetected = pixy.getBlocks();
        // cache the index of the biggest block
        findBiggestDetection();
    }

    void test()
    {
        Serial.print(blocksDetected + " blocks detected.");
        for (int i = 0; i <= blocksDetected; i++)
        {
            if (i == biggestIndex)
                Serial.print("!");
            pixy.blocks[i].print();
        }
    }
}
