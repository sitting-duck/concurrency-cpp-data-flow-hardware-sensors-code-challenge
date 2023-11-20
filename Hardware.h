#ifndef HARDWARE_H
#define HARDWARE_H

#include <string>
#include <vector>
#include <array>
#include "Constant.h"
#include "Packet.h"

class Hardware {
public:
    enum class IntervalTime {
        MS_1 = 1000,      // 1ms = 1000 microseconds
        MS_0_5 = 500,     // 0.5ms = 500 microseconds
        MS_0_33 = 330     // 0.33ms = 330 microseconds
    };

    Hardware(std::string& uuid, int numMagneticSensors, int numAccelerometerSensors, int numGyroscopeSensors, IntervalTime interval);

    Packet generateDataPacket() const; 

    static int intervalToInt(Hardware::IntervalTime& intervalTime);

private:

    std::string uuid;
    int numMagneticSensors;
    int numAccelerometerSensors;
    int numGyroscopeSensors;
    IntervalTime interval;

    std::vector<std::array<float, numValuesPerSample>> generateSensorData(int sensorCount) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Hardware::IntervalTime& intervalTime);
    
};

#endif // HARDWARE_H

