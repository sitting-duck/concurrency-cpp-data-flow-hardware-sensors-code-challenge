#ifndef POSE_H
#define POSE_H

#include <array>
#include <ostream>

class Pose {
public:
    Pose(); // Implement constructor to initialize pose values

    friend std::ostream& operator<<(std::ostream& os, const Pose& pose);

private:
    std::array<float, 7> values; // Array to hold 7 floating-point values
};

#endif // POSE_H
