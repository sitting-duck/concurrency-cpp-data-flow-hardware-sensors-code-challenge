#include "Algorithm.h"
#include <thread>
#include <random>

Algorithm::Algorithm() {
    // Initialize processingTime with a random value between half and twice the interval
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(250, 2000); // Assuming 0.5ms to 2ms as an example
    processingTime = std::chrono::milliseconds(dis(gen));
}

std::vector<float> Algorithm::process(const std::vector<float>& magnetometerData) {
    // Simulate processing delay
    std::this_thread::sleep_for(processingTime);

    // Simulated output (replace with real processing logic)
    return std::vector<float>(7, 0.0f); // 7 float values representing a pose
}

