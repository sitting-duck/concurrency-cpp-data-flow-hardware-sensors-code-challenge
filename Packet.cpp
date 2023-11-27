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

void Packet::setUuid(std::string uuid) {
  this->uuid = uuid;
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
  os << "\tPacket UUID: " << packet.uuid << "\n";
    os << "\tTimestamp: " << packet.timestamp << "\n";

    // Print magnetic samples
    os << "\tMagnetic Samples:\n";
    for (const auto& sample : packet.magneticSamples) {
        for (const auto& value : sample) {
            os << value << " ";
        }
        os << "\n";
    }

    // Print accelerometer samples
    os << "\tAccelerometer Samples:\n";
    for (const auto& sample : packet.accelerometerSamples) {
        for (const auto& value : sample) {
            os << value << " ";
        }
        os << "\n";
    }

    // Print gyroscope samples
    os << "\tGyroscope Samples:\n";
    for (const auto& sample : packet.gyroscopeSamples) {
        for (const auto& value : sample) {
            os << value << " ";
        }
        os << "\n";
    }

    return os;
}

