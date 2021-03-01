#pragma once
#include <vector>
#include <memory>

struct PassData {
    float firstSubmit;
    float lastSubmoipresentTime;
    float presentReturnTime;

    // GPU times
    float renderStartTime;
    float renderFinishedTime;
};

struct Frame {

    // Per frame stats
    int frameNum;
    float startTime;
    
    float frameDuration;
    float animationTime;

    // Dont worry about multi-pass right now.
    std::vector<std::shared_ptr<PassData>> commandBuffer;

    // Display flip time
    float flipTime;
};