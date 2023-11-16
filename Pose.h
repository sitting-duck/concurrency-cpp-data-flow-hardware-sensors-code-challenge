#ifndef POSE_H
#define POSE_H

#include <array>

class Pose {
public:
    static const int numValues = 7; // Number of values in a pose
    Pose(const std::array<float, numValues>& values);

private:
    std::array<float, numValues> values;
};

#endif // POSE_H

