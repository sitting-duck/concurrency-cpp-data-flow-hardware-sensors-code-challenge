#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <vector>
#include "Hardware.h"
#include "Client.h"

class ClientManager {
public: 
	static void subscribeClients(std::vector<Hardware>& devices, std::vector<Client>& clients);

	static const int minClients = 5;
};

#endif