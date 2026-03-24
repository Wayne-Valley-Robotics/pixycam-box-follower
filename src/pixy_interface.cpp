#include <SPI.h>
#include <Pixy.h>

namespace pixy_interface
{
    Pixy pixy;

    // make it easier
    void test()
    {
        int blocksDetected = pixy.getBlocks();
        Serial.print(pixy.getBlocks() + " blocks detected.");
        for (int i = 0; i <= blocksDetected; i++)
        {
            Serial.print("Block " + String(i) + ": ");
            // return center of box. x: 0-319 y: 0-199
            Serial.print("center: " + String(pixy.blocks[i].x) + ", " + String(pixy.blocks[i].y));
            // return width and height, 1-320 and 1-200
            Serial.print("dimensions: " + String(pixy.blocks[i].width) + ", " + String(pixy.blocks[i].height));
            // bruh
            // pixy.blocks[i].print();

        }
    }
}
