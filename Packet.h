#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>

class Packet {
public:
    Packet(const std::string& uuid, long long timestamp,
           const std::vector<std::vector<float>>& magneticSamples,
           const std::vector<std::vector<float>>& accelerometerSamples,
           const std::vector<std::vector<float>>& gyroscopeSamples);

    // Getters
    std::string getUUID() const;
    long long getTimestamp() const;
    const std::vector<std::vector<float>>& getMagneticSamples() const;
    const std::vector<std::vector<float>>& getAccelerometerSamples() const;
    const std::vector<std::vector<float>>& getGyroscopeSamples() const;

private:
    std::string uuid;
    long long timestamp;
    std::vector<std::vector<float>> magneticSamples;
    std::vector<std::vector<float>> accelerometerSamples;
    std::vector<std::vector<float>> gyroscopeSamples;
};

#endif // PACKET_H

