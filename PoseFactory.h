#ifndef POSEFACTORY_H
#define POSEFACTORY_H

#include "Pose.h"

class PoseFactory {
public:
    static Pose createRandomPose(std::string packetUuid);
};

#endif // POSEFACTORY_H
