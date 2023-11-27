#include "Hardware.h"
#include "Time.h"
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

    auto timestamp = Time::getTimeStamp();
    auto timeStampStr = Time::getTimeStampString();

    // generating sensor data
    auto magneticSamples = generateSensorData(this->numMagneticSensors);
    auto accelerometerSamples = generateSensorData(this->numAccelerometerSensors);
    auto gyroscopeSamples = generateSensorData(this->numGyroscopeSensors);

    std::string packetUuid = "p" + this->uuid + Time::generateUUID();

    // Create a Packet with the generated data
    Packet packet(packetUuid, timestamp, magneticSamples, accelerometerSamples, gyroscopeSamples);
    packet.setUuid(packetUuid);
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

std::ostream& operator<<(std::ostream& os, const Hardware::IntervalTime& intervalTime) {
    switch (intervalTime) {
        case Hardware::IntervalTime::MS_1:
            os << "1 ms";
            break;
        case Hardware::IntervalTime::MS_0_5:
            os << "0.5 ms";
            break;
        case Hardware::IntervalTime::MS_0_33:
            os << "0.33 ms";
            break;
        default:
            os << "Unknown Interval";
    }
    return os;
}

std::string Hardware::getUuid() const {
    return uuid;
}

void Hardware::setUuid(const std::string& newUuid) {
    uuid = newUuid;
}

int Hardware::getNumMagneticSensors() const {
    return numMagneticSensors;
}

void Hardware::setNumMagneticSensors(int numSensors) {
    numMagneticSensors = numSensors;
}

int Hardware::getNumAccelerometerSensors() const {
    return numAccelerometerSensors;
}

void Hardware::setNumAccelerometerSensors(int numSensors) {
    numAccelerometerSensors = numSensors;
}

int Hardware::getNumGyroscopeSensors() const {
    return numGyroscopeSensors;
}

void Hardware::setNumGyroscopeSensors(int numSensors) {
    numGyroscopeSensors = numSensors;
}

int Hardware::getNumSensors() const {
    return numMagneticSensors + numAccelerometerSensors + numGyroscopeSensors;
}

Hardware::IntervalTime Hardware::getInterval() const {
    return interval;
}

int Hardware::getIntervalAsInt() const {
    switch (this->interval) {
        case Hardware::IntervalTime::MS_1: return 1000;
        case Hardware::IntervalTime::MS_0_5: return 500;
        case Hardware::IntervalTime::MS_0_33: return 330;
        default: return -1;
    }
}

void Hardware::setInterval(Hardware::IntervalTime interval) {
    this->interval = interval;
}
