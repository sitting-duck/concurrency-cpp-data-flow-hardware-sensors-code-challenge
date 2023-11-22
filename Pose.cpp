#include "Pose.h"

Pose::Pose() {
    // Initialize pose values here, possibly randomly
}

std::ostream& operator<<(std::ostream& os, const Pose& pose) {
    for (const auto& value : pose.values) {
        os << value << " ";
    }
    return os;
}
