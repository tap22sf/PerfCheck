#include "Timer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

TAPLib::Timer::Timer(const std::string& name) : name(name)
{
    startPoint = std::chrono::high_resolution_clock::now();
    lastPoint = startPoint;
}

TAPLib::Timer::~Timer()
{
    Print();
}

// Return duration in ms
double TAPLib::Timer::getDuration()
{
    std::chrono::high_resolution_clock::time_point currentPoint = std::chrono::high_resolution_clock::now();
    duration = currentPoint - startPoint;
    return duration.count();
}

// Return laptime in ms
double TAPLib::Timer::getLap()
{
    std::chrono::high_resolution_clock::time_point currentPoint = std::chrono::high_resolution_clock::now();
    lap = currentPoint - lastPoint;
    lastPoint = currentPoint;
    return lap.count();
}


std::string TAPLib::Timer::Print()
{

    std::ostringstream oss;    
    oss << "Timer ";
    oss << name << "->  Lap: ";
    oss << std::setw(10);
    oss << std::fixed;
    oss << std::setprecision(2);
    oss << getLap();

    oss << " Duration: ";
    oss << std::setw(10);
    oss << std::fixed;
    oss << std::setprecision(2);
    oss << getDuration();

    return oss.str();
}
