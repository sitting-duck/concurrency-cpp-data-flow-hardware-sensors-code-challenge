#include "HardwareFactory.h"
#include "ThreadManager.h"
#include <iostream>

int main() {
    std::cout << "Main thread starting." << std::endl;
    const int numDevices = 10;
    std::vector<Hardware> devices = HardwareFactory::createRandomHardwareDevices(numDevices);

    ThreadManager threadManager(devices);
    threadManager.run();

    std::cout << "Main thread finishing." << std::endl;
    return 0;
}
