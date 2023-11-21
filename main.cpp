#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include "Hardware.h"

void simulateSensor(const std::string& uuid, Hardware::IntervalTime interval, int sensorType) {
    // Simulate sensor processing here
    // 'sensorType' can be used to distinguish between different sensor types (magnetometer, accelerometer, gyroscope)
    // ...

    // while (true) {
        // Simulate sensor data generation and processing
        // ...

        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(interval)));
        std::cout << uuid << " finished sleep" << std::endl;
    // }
}

void mahfunc() {
    std::cout << "derp" << std::endl;
}

std::vector<Hardware> createRandomHardwareDevices(int numDevices) {
    std::vector<Hardware> devices;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sensorDis(1, 5);
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

int main() {
    std::cout << "Main thread starting." << std::endl;

    const int numDevices = 10;
    std::vector<std::thread> sensorThreads;

    std::vector<Hardware> devices = createRandomHardwareDevices(numDevices);

    for(auto device : devices) {
        std::string uuid = device.getUuid();
        int interval_in_ms = device.getIntervalAsInt();

        // Create threads for each sensor in the device
        for (int i = 0; i < device.getNumMagneticSensors(); ++i) {
            //sensorThreads.emplace_back(simulateSensor, uuid, interval_in_ms, 0); // 0 for magnetometer
            sensorThreads.emplace_back(mahfunc); // 0 for magnetometer
        }
        // for (int i = 0; i < device.getNumAccelerometerSensors(); ++i) {
        //     sensorThreads.emplace_back(simulateSensor, uuid, interval_in_ms, 1); // 1 for accelerometer
        // }
        // for (int i = 0; i < device.getNumGyroscopeSensors(); ++i) {
        //     sensorThreads.emplace_back(simulateSensor, uuid, interval_in_ms, 2); // 2 for gyroscope
        // }
    }


        

    for (auto& thread : sensorThreads) {
        thread.join();
    }

    std::cout << "Main thread finishing." << std::endl;
    return 0;
}
