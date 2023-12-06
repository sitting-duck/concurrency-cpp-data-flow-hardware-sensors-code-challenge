#include "Client.h"
#include <iostream>

void Client::consumePoses(const std::vector<Pose*>& poses) {
    for (const auto* pose : poses) {
        std::cout << "Client consuming pose: " << *pose << std::endl;
        // Additional processing as needed
    }
}

void Client::subscribeToHardware(Hardware hardware) {
    // Add the hardware to the client's list of devices
    devices.push_back(hardware);
}

bool Client::isSubscribedTo(std::string uuid) {
    // Check if a hardware device with the given UUID is in the devices vector
    for (auto& device : devices) {
        if (device.getUuid() == uuid) {
            return true; // Found a device with the matching UUID
        }
    }
    return false; // No device with the matching UUID found
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Client Subscriptions: [";
    for (const auto& device : client.devices) {
        os << device.getUuid() << " ";
    }
    os << "]";
    return os;
}