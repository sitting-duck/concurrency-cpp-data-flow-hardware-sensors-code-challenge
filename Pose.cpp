#include "Pose.h"

Pose::Pose() {
    
}

Pose::Pose(float v1, float v2, float v3, float v4, float v5, float v6, float v7)
    : values{{v1, v2, v3, v4, v5, v6, v7}} {}

std::ostream& operator<<(std::ostream& os, const Pose& pose) {
    for (const auto& value : pose.values) {
        os << value << " ";
    }
    return os;
}
