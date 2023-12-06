#ifndef CLIENT_H
#define CLIENT_H

#include "Packet.h"
#include "Pose.h"
#include "Hardware.h"

class Client {
public:

    void consumePoses(const std::vector<Pose*>& poses);

    void subscribeToHardware(Hardware hardware);
    bool isSubscribedTo(std::string uuid);

    friend std::ostream& operator<<(std::ostream& os, const Client& client);

private:
	std::vector<Hardware> devices;
};

#endif // CLIENT_H

