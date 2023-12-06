#include "ClientManager.h"

void ClientManager::subscribeClients(std::vector<Hardware>& devices, std::vector<Client>& clients) {
	std::cout << "ClientManager::subscribeClients()" << std::endl;
    // Ensure there are enough clients
    while (clients.size() < minClients) {
        clients.push_back(Client());
    }

    // Basic subscription: Each client subscribes to at least one hardware device
    for (size_t i = 0; i < clients.size(); ++i) {
        clients[i].subscribeToHardware(devices[i % devices.size()]);
    }

    // Advanced subscription: Ensuring some clients subscribe to at least three devices
    for (size_t i = 0; i < std::min(clients.size(), size_t(3)); ++i) {
        for (size_t j = 0; j < 3; ++j) { // Subscribing to three devices
            clients[i].subscribeToHardware(devices[j]);
        }
    }

    // Ensure the same three devices have at least two other clients each
    for (size_t j = 0; j < 3; ++j) {
        size_t additionalSubscriptions = 0;
        for (size_t i = 3; i < clients.size() && additionalSubscriptions < 2; ++i) {
            //if (!clients[i].isSubscribedTo(devices[j].getUuid())) {
            if (!clients[i].isSubscribedTo("boop")) {
                clients[i].subscribeToHardware(devices[j]);
                additionalSubscriptions++;
            }
        }
    }
}