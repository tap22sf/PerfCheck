#include "RandomData.h"
#include <random>

RandomData::RandomData(float startTime, float stopTime, float mean, float stdDev) {
    genData(startTime, stopTime, mean, stdDev);
}

RandomData::~RandomData() {
}

void RandomData::genData(float startTime, float stopTime, float mean, float stdDev) {

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean, stdDev);

    int p[10] = {};
    int nrolls = 100;
    float t = 0.0;

    for (int i = 0; i < nrolls; ++i) {
        Frame f;
        f.frameNum = i;
        f.startTime = t;
        f.frameDuration = distribution(generator);
        t += f.frameDuration;

        data.emplace_back(f);
    }
}
