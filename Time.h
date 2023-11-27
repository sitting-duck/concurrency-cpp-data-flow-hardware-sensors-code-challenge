#ifndef TIME_H
#define TIME_H

#include <string>
#include <random>
#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

class Time {
public:
    
    static int calculateProcessingTime(int interval);
    static std::string getTimeStampString();
    static std::chrono::system_clock::duration::rep getTimeStamp();
    static std::string generateUUID();

    

private:
    
};

#endif // TIME_H