#include "Hardware.h"
#include <chrono>
#include <random>

Hardware::Hardware(std::string& uuid, int numMagneticSensors, int numAccelerometerSensors, int numGyroscopeSensors, IntervalTime interval) {
    this->uuid = uuid;
    this->numMagneticSensors = numMagneticSensors;
    this->numAccelerometerSensors = numAccelerometerSensors;
    this->numGyroscopeSensors = numGyroscopeSensors;
    this->interval = interval;
}

Packet Hardware::generateDataPacket() const {

    // Generating a timestamp for the packet
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();

    // generating sensor data
    auto magneticSamples = generateSensorData(this->numMagneticSensors);
    auto accelerometerSamples = generateSensorData(this->numAccelerometerSensors);
    auto gyroscopeSamples = generateSensorData(this->numGyroscopeSensors);

    // Create a Packet with the generated data
    Packet packet(uuid, timestamp, magneticSamples, accelerometerSamples, gyroscopeSamples);
    return packet;
}

std::vector<std::array<float, numValuesPerSample>> Hardware::generateSensorData(int sensorCount) const {
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

