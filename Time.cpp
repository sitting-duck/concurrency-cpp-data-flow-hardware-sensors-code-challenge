#include "Time.h"
#include <iostream>
#include <sstream>
#include <random>
#include <string>


int Time::calculateProcessingTime(int interval) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dis(interval, interval / 4.0f); // Adjust the standard deviation as needed

    float generatedValue = dis(gen);
    float minValue = interval / 2.0f;
    float maxValue = interval * 2.0f;

    // Manually clamping the value
    int sleepDuration = static_cast<int>(generatedValue < minValue ? minValue : (generatedValue > maxValue ? maxValue : generatedValue));
    return sleepDuration;
}

std::string Time::getTimeStampString() {

	auto timePoint = std::chrono::system_clock::now();

    // Convert time_point to std::time_t
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);

    // Convert std::time_t to tm struct
    std::tm* timeStruct = std::localtime(&time);

    // Create a string stream for formatted output
    std::stringstream ss;

    // Format the time - example format: YYYY-MM-DD-HH-MM-SS
    ss << std::put_time(timeStruct, "%Y-%m-%d-%H-%M-%S");

    return ss.str();
}

std::chrono::system_clock::duration::rep Time::getTimeStamp() {
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    //std::string timestampStr = std::to_string(timestamp);
    return timestamp;
}

std::string Time::generateUUID() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 15);
    std::uniform_int_distribution<int> dis2(8, 11);

    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";  // The 4 in this segment is a version number.
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);  // The 8, 9, A, or B in this segment is the UUID variant.
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    }
    return ss.str();
}
