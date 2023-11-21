#include <iostream>
#include <vector>
#include <pthread.h>
#include <random>
#include "Hardware.h"

#include <iostream>
#include <random>
#include <unistd.h>  // For usleep

#include <queue>
#include <mutex>



void ProcessPacket(int interval) {
    // Create a random engine and distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(interval / 2, interval * 2); // Range from half to twice the interval

    // Calculate random sleep duration within the specified range
    int sleepDuration = dis(gen);

    // Sleep for the calculated duration
    usleep(sleepDuration);

    std::cout << "Processed packet in " << sleepDuration << " microseconds." << std::endl;
}

struct SensorThreadData {
    std::string uuid;
    int intervalInMs;
    int sensorType;
};

void* simulateSensor(void* arg) {
    SensorThreadData* data = static_cast<SensorThreadData*>(arg);
    
    // Generate packets at the interval rate
    auto startTime = std::chrono::steady_clock::now();
    int packetCount = 0;

    // generate packet was here

    std::cout << data->uuid << " finished processing sensor type " << data->sensorType << std::endl;

    delete data; // Clean up
    return nullptr;
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


std::queue<Packet> packets;
std::mutex packetsMutex;

int main() {
    std::cout << "Main thread starting." << std::endl;

    const int numDevices = 10;
    int simulationDuration;
    auto startTime = std::chrono::steady_clock::now();
    std::cout << "enter simulation time: ";
    std::cin >> simulationDuration;

    std::vector<pthread_t> sensorThreads;
    std::vector<Hardware> devices = createRandomHardwareDevices(numDevices);

    // begin Packet creation
    while (true) {
        int packetCount = 0;
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        if (elapsedTime >= simulationDuration) {
            break; // Stop simulation after specified duration
        }

        // Simulate packet generation
        for(auto device : devices) {
            std::string packetUuid = "p" + std::to_string(packetCount) + "_" + device.getUuid() + "_" + std::to_string(elapsedTime);
            Packet packet = device.generateDataPacket();  

            // Lock mutex and add packet to the global queue
            {
                std::lock_guard<std::mutex> lock(packetsMutex);
                packets.push(packet);
            }
            packetCount++;
        }

    }
    // end Packet creation

    // begin Packet processing
    for(auto device : devices) {
        std::string uuid = device.getUuid();
        int interval_in_ms = device.getIntervalAsInt();

        // Create threads for each sensor in the device
        for (int i = 0; i < device.getNumMagneticSensors(); ++i) {
            pthread_t thread;
            SensorThreadData* data = new SensorThreadData{device.getUuid(), interval_in_ms, 0}; // 0 for magnetometer
            pthread_create(&thread, nullptr, simulateSensor, data);
            sensorThreads.push_back(thread);
        }
        for (int i = 0; i < device.getNumAccelerometerSensors(); ++i) {
            pthread_t thread;
            SensorThreadData* data = new SensorThreadData{device.getUuid(), interval_in_ms, 1}; // 1 for accelerometer
            pthread_create(&thread, nullptr, simulateSensor, data);
            sensorThreads.push_back(thread); 
        }
        for (int i = 0; i < device.getNumGyroscopeSensors(); ++i) {
            pthread_t thread;
            SensorThreadData* data = new SensorThreadData{device.getUuid(), interval_in_ms, 2}; // 2 for gyroscope
            pthread_create(&thread, nullptr, simulateSensor, data);
            sensorThreads.push_back(thread);  
        }
    }

    // Join pthreads
    for (auto& thread : sensorThreads) {
        pthread_join(thread, nullptr);
    }

    // end Packet processing

    std::cout << "Main thread finishing." << std::endl;
    return 0;
}
