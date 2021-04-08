#include "Parsers.h"
#include <iostream>
#include <QtCore/QVector>

bool FrapsParser::sigMatch(const Row& r)
{
    return ((r.size() == 2) && (r[0] == "Frame") && (r[1] == " Time (ms)"));
}

bool FrapsParser::parseRows(const std::string& fileName, const std::vector<Row>& rows, std::vector<std::shared_ptr<Frame>>& frames)
{
    // Iterate through all rows
    for (auto& r : rows) {
        std::shared_ptr<Frame> frame = nullptr;

        // Save good frames
        if (FrapsParser::parseLine(r, frame)) {
            frames.push_back(frame);
        }
        else {
            //std::cout << "Invalid line file: " << fileName << std::endl;
        }
    }

    return true;
}

// Allocates and returns a new Frame
bool FrapsParser::parseLine(const Row& r, std::shared_ptr<Frame>& frame) {

    // Should always have to elements
    if (r.size() != 2)
        return false;

    // Get frame number and current time.
    int frameNum = atoi(r[0].c_str())-1;
    qreal thisTime = atof(r[1].c_str());

    // Calc delta to get frametime
    qreal delta = thisTime - parserLastTime;
    parserLastTime = thisTime;

    // First entry just grabs original time
    if (firstPass) {
        firstPass = false;
        return false;
    }

    // Create a new frame if needed
    if (frame == nullptr)
        frame = std::make_shared<Frame>();

    frame->startTime = thisTime;
    frame->frameNum = frameNum;
    frame->frameDuration = delta;

    return true;
}


bool PresentMonParser::sigMatch(const Row& r)
{
    return (r[0] == "Application");
}

bool PresentMonParser::parseRows(const std::string& fileName, const std::vector<Row>& rows, std::vector<std::shared_ptr<Frame>>& frames)
{
    {
        // Iterate through all rows
        for (auto& r : rows) {
            std::shared_ptr<Frame> frame = nullptr;

            // Save good frames
            if (PresentMonParser::parseLine(r, frame)) {
                frames.push_back(frame);
            }
            else {
                //std::cout << "Invalid line file: " << fileName << std::endl;
            }
        }
        return true;
    }
}

// Allocates and returns a new Frame
bool PresentMonParser::parseLine(const Row& r, std::shared_ptr<Frame>& frame) {

    // Get frame number and current time.
    static int frameNum = 0;

    // First entry Find correct field indexes
    if (firstPass) {
        int i = 0;
        for (auto& row : r) {
            fieldIndex[row] = i;
            i++;
        }
        
        firstPass = false;
        return false;
    }

    // Create a new frame if needed
    if (frame == nullptr)
        frame = std::make_shared<Frame>();

    frame->startTime = std::stof(r[fieldIndex["TimeInSeconds"]]) * 1000.0;
    frame->frameNum = frameNum++;
    frame->frameDuration = std::stof(r[fieldIndex["MsBetweenPresents"]]);
    return true;
}
