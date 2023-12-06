#ifndef POSE_H
#define POSE_H

#include <array>
#include <ostream>

class Pose {
public:
    Pose();
    Pose(float v1, float v2, float v3, float v4, float v5, float v6, float v7, std::string packetUuid);

    friend std::ostream& operator<<(std::ostream& os, const Pose& pose);

private:
    std::array<float, 7> values; // Array to hold 7 floating-point values
    std::string packetUuid;
};

#endif // POSE_H
