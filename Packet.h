#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <string>
#include <vector>
#include "Constant.h"

class Packet {
public:
    Packet(const std::string& uuid, long long timestamp,
           const std::vector<std::array<float, numValuesPerSample>>& magneticSamples,
           const std::vector<std::array<float, numValuesPerSample>>& accelerometerSamples,
           const std::vector<std::array<float, numValuesPerSample>>& gyroscopeSamples);

    // Getters
    std::string getUUID() const;
    void setUuid(std::string uuid);
    long long getTimestamp() const;
    const std::vector<std::array<float, numValuesPerSample>>& getMagneticSamples() const;
    const std::vector<std::array<float, numValuesPerSample>>& getAccelerometerSamples() const;
    const std::vector<std::array<float, numValuesPerSample>>& getGyroscopeSamples() const;

    friend std::ostream& operator<<(std::ostream& os, const Packet& packet);

private:
    std::string uuid;
    long long timestamp;
    std::vector<std::array<float, numValuesPerSample>> magneticSamples;
    std::vector<std::array<float, numValuesPerSample>> accelerometerSamples;
    std::vector<std::array<float, numValuesPerSample>> gyroscopeSamples;
};

#endif // PACKET_H

