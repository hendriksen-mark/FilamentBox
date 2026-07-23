#include "mock_data.h"

void mock()
{
    w1 = random(0, 1000) / 100.0; // Random weight between 0.00 and 10.00
    w2 = random(0, 1000) / 100.0; // Random weight between 0.00 and 10.00
    w3 = random(0, 1000) / 100.0; // Random weight between 0.00 and 10.00
    w4 = random(0, 1000) / 100.0; // Random weight between 0.00 and 10.00

    l1 = random(0, 200) / 10.0; // Random length between 0.0 and 20.0
    l2 = random(0, 200) / 10.0; // Random length between 0.0 and 20.0
    l3 = random(0, 200) / 10.0; // Random length between 0.0 and 20.0
    l4 = random(0, 200) / 10.0; // Random length between 0.0 and 20.0

    pot1 = random(0, 1024); // Random potentiometer value between 0 and 1023
    pot2 = random(0, 1024); // Random potentiometer value between 0 and 1023
    pot3 = random(0, 1024); // Random potentiometer value between 0 and 1023
    pot4 = random(0, 1024); // Random potentiometer value between 0 and 1023

    currentHumidity = random(0, 10000) / 100.0; // Random humidity between 0.00% and 100.00%
    currentTemp = random(1500, 3000) / 100.0;   // Random temperature between 15.00°C and 30.00°C
}
