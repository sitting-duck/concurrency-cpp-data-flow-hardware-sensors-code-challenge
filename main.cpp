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
        
    }
}

int main() {
    std::cout << "Hello World" << std::endl;

    // the hardware samples will be sent to the algorithm for proceessing. 

    // an algorithm instance will be processing data for ONE individual magnetometer
    // a hardware device with multiple magenetometers will need a corresponding number of algorithm instances. 


    // once all the algorithm instances are done processing the sample packet, 
    // each magnetometer (algorithm instance) will produce one pose

    // the sample packet with its raw data and its associated pose outputs will be sent to any downstream clients
    // that have requested data from this particular device.  

    return 0;
}

