#pragma once
#include <vector>
#include "Frame.h"

class RandomData
{
public:
    RandomData(float startTime, float stopTime, float mean, float stdDev);
    ~RandomData();

    // ease of use make it public
    std::vector<Frame> data;

private:
    void genData(float startTime, float stopTime, float average, float var);

};

