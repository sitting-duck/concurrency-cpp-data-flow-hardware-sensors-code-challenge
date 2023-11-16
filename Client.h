#ifndef CLIENT_H
#define CLIENT_H

#include "Packet.h"
#include "Pose.h"

class Client {
public:
    virtual void receiveData(const Packet& packet, const std::vector<Pose>& poses) = 0;
};

#endif // CLIENT_H

