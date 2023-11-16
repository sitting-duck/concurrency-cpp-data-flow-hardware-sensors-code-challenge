#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <chrono>

class Algorithm {
public:
    Algorithm();
    std::vector<float> process(const std::vector<float>& magnetometerData);

private:
    std::chrono::milliseconds processingTime;
};

#endif // ALGORITHM_H

