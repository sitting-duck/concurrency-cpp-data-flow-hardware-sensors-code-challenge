#ifndef HARDWAREFACTORY_H
#define HARDWAREFACTORY_H

#include <vector>
#include "Hardware.h"

class HardwareFactory {
public:
    static std::vector<Hardware> createRandomHardwareDevices(int numDevices);
};

#endif // HARDWAREFACTORY_H
