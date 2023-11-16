#include "Packet.h"

Packet::Packet(const std::string& uuid, long long timestamp,
               const std::vector<std::array<float, numValuesPerSample>>& magneticSamples,
               const std::vector<std::array<float, numValuesPerSample>>& accelerometerSamples,
               const std::vector<std::array<float, numValuesPerSample>>& gyroscopeSamples)
    : uuid(uuid), timestamp(timestamp), magneticSamples(magneticSamples),
      accelerometerSamples(accelerometerSamples), gyroscopeSamples(gyroscopeSamples) {}

std::string Packet::getUUID() const {
    return uuid;
}

long long Packet::getTimestamp() const {
    return timestamp;
}

const std::vector<std::array<float, numValuesPerSample>>& Packet::getMagneticSamples() const {
    return magneticSamples;
}

const std::vector<std::array<float, numValuesPerSample>>& Packet::getAccelerometerSamples() const {
    return accelerometerSamples;
}

const std::vector<std::array<float, numValuesPerSample>>& Packet::getGyroscopeSamples() const {
    return gyroscopeSamples;
}

