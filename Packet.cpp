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

std::ostream& operator<<(std::ostream& os, const Packet& packet) {
  os << "Packet UUID: " << packet.uuid << "\n";
    os << "Timestamp: " << packet.timestamp << "\n";

    // Print magnetic samples
    os << "Magnetic Samples:\n";
    for (const auto& sample : packet.magneticSamples) {
        for (const auto& value : sample) {
            os << value << " ";
        }
        os << "\n";
    }

    // Print accelerometer samples
    os << "Accelerometer Samples:\n";
    for (const auto& sample : packet.accelerometerSamples) {
        for (const auto& value : sample) {
            os << value << " ";
        }
        os << "\n";
    }

    // Print gyroscope samples
    os << "Gyroscope Samples:\n";
    for (const auto& sample : packet.gyroscopeSamples) {
        for (const auto& value : sample) {
            os << value << " ";
        }
        os << "\n";
    }

    return os;
}

