#ifndef HARDWARE_H
#define HARDWARE_H

#include "Packet.h"
#include <string>
#include <vector>
#include <array>

class Hardware {
public:
    Hardware(const std::string& uuid, int numMagneticSensors, int numAccelerometerSensors, int numGyroscopeSensors);

    Packet generateDataPacket() const;

private:
    static const int numValuesPerSample = 3; // Each sensor has 3 values: x, y, z
    std::string uuid;
    const int numMagneticSensors;
    const int numAccelerometerSensors;
    const int numGyroscopeSensors;

    std::vector<std::array<float, numValuesPerSample>> generateSensorData(int sensorCount) const;
};

#endif // HARDWARE_H

