#include "Logger.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <string>
#include <fstream>

#include <chrono>

//#include <libgen.h>

std::string PiName(void)
{
    // Open the cpuinfo stream
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;

    while (std::getline(cpuinfo, line)) {

        if (!line.size())
            continue;

        //LogMessage(line);

        std::string re = "(Model.*: )(.*)";
        std::regex str_expr(re);
        std::smatch sm;

        if (std::regex_match(line, sm, str_expr)) {
            //LogMessage("RPi name detected :" + sm[2].str());
            return sm[2].str();
        }
    }

    return ("unknown");
}


// Write the string to the log
void TAPLib::Logger::LogImpl(const char* file, const int line, const std::string& msg) {

#ifdef WIN32
    char drive[10], dir[100], fname[100], ext[10];;
    _splitpath_s(file,
        drive,
        dir,
        fname,
        ext);
#else
    char* fname = basename((char*)file);

#endif
   
    time_t rawtime;
    struct tm * current_time;
    time (&rawtime);
    current_time = localtime (&rawtime);

    std::stringstream st;
    st << "Time : ";
    st << std::setfill('0') << std::setw(2);
    st << current_time->tm_hour << ":";
    st << std::setw(2);
    st << current_time->tm_min << ":";
    st << std::setw(2) << current_time->tm_sec;

    std::stringstream oss;
    oss << st.str() << "    ";
    oss << "[File] ";
    oss << std::left << std::setw(20);
    oss << fname;
    oss << "[Line] ";
    oss << std::right << std::setw(8);
    oss << line;
    oss << "  [Msg] " << msg;

    //logFile << "Logger : ";
    logFile << oss.str() << std::endl;

    std::cout << "Logger : ";
    std::cout << oss.str() << std::endl;
}
