#include "Hardware.h"
#include <chrono>
#include <random>

// ...

std::vector<std::array<float, Hardware::numValuesPerSample>> Hardware::generateSensorData(int sensorCount) const {
    std::vector<std::array<float, numValuesPerSample>> sensorData;
    sensorData.reserve(sensorCount);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);

    for (int i = 0; i < sensorCount; ++i) {
        std::array<float, numValuesPerSample> singleSensorData = {
            static_cast<float>(dis(gen)), 
            static_cast<float>(dis(gen)), 
            static_cast<float>(dis(gen))
        };
        sensorData.push_back(singleSensorData);
    }

    return sensorData;
}

