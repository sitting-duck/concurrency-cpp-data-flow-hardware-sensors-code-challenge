#include "Packet.h"

Packet::Packet(const std::string& uuid, long long timestamp,
               const std::vector<std::vector<float>>& magneticSamples,
               const std::vector<std::vector<float>>& accelerometerSamples,
               const std::vector<std::vector<float>>& gyroscopeSamples)
    : uuid(uuid), timestamp(timestamp), magneticSamples(magneticSamples),
      accelerometerSamples(accelerometerSamples), gyroscopeSamples(gyroscopeSamples) {}

std::string Packet::getUUID() const {
    return uuid;
}

long long Packet::getTimestamp() const {
    return timestamp;
}

const std::vector<std::vector<float>>& Packet::getMagneticSamples() const {
    return magneticSamples;
}

const std::vector<std::vector<float>>& Packet::getAccelerometerSamples() const {
    return accelerometerSamples;
}

const std::vector<std::vector<float>>& Packet::getGyroscopeSamples() const {
    return gyroscopeSamples;
}

