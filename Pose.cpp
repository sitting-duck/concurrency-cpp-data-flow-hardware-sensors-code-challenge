#include "Pose.h"
#include <iostream>

Pose::Pose() {
    
}

Pose::Pose(float v1, float v2, float v3, float v4, float v5, float v6, float v7, std::string _packetUuid)
    : values{{v1, v2, v3, v4, v5, v6, v7}} {
        this->packetUuid = _packetUuid;
        std::cout << "Pose ctor for packet " << packetUuid << std::endl;
    }

std::ostream& operator<<(std::ostream& os, const Pose& pose) {
    std::cout << "Pose for packet: " << pose.packetUuid << " : values : "; 
    for (const auto& value : pose.values) {
        os << value << " ";
    }
    std::cout << std::endl;
    return os;
}
