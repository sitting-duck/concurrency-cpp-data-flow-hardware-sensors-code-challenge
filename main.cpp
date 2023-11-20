#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include "Hardware.h"

void simulateHardwareDevice(std::string& uuid, int magSensors, int accelSensors, int gyroSensors, Hardware::IntervalTime interval) {
    Hardware hardware(uuid, magSensors, accelSensors, gyroSensors, interval);

    while(true) {
        auto packet = hardware.generateDataPacket();
        std::cout << "got packet: " << packet << std::endl;
    }
}

void test(std::string& uuid) {
    std::cout << "doing a test" << std::endl;
}

// void test(std::string &) {}
// void test2(std::string &&) {}
// void test3(std::string const&) {}
// void test4(std::string) {}

int main() {
    std::cout << "Hello World" << std::endl;

    std::string s;
    //test(std::move(s)); // fail
    //test2(std::move(s)); // ok
    //test3(std::move(s)); // ok
    //test4(std::move(s)); // ok

    const int numDevices = 10;
    std::vector<std::thread> threads;

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
        int interval_as_ms = Hardware::intervalToInt(interval);

         std::cout << "mah interval: " << interval << std::endl;

        //threads.emplace_back(simulateHardwareDevice, uuid, magSensors, accelSensors, gyroSensors, interval);
        //threads.emplace_back(simulateHardwareDevice, uuid, magSensors, accelSensors, gyroSensors, interval_as_ms);
        threads.emplace_back(test, uuid);
    }

  //   //for (auto& thread : threads) {
  //   //    thread.join();
  //   //}   

    return 0;
}
