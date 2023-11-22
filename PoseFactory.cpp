#include "PoseFactory.h"
#include <random>

Pose PoseFactory::createRandomPose() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    return Pose(dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen));
}
