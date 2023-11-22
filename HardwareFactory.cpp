#include "HardwareFactory.h"
#include <random>

std::vector<Hardware> HardwareFactory::createRandomHardwareDevices(int numDevices) {
    std::vector<Hardware> devices;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sensorDis(1, 5);   // create 1 to 5 sensors of each type
    std::uniform_int_distribution<> intervalDis(0, 2); // For three interval types

    for (int i = 0; i < numDevices; ++i) {
        std::string uuid = "Hardware_" + std::to_string(i);
        int magSensors = sensorDis(gen);
        int accelSensors = sensorDis(gen);
        int gyroSensors = sensorDis(gen);

        Hardware::IntervalTime interval;
        switch (intervalDis(gen)) {
            case 0: interval = Hardware::IntervalTime::MS_1; break;
            case 1: interval = Hardware::IntervalTime::MS_0_5; break;
            case 2: interval = Hardware::IntervalTime::MS_0_33; break;
        }
        Hardware hardware(uuid, magSensors, accelSensors, gyroSensors, interval);
        devices.push_back(hardware);
    }
    return devices;
}
