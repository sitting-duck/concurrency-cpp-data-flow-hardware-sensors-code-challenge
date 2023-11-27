#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <vector>
#include "Hardware.h"

struct PacketProcessArgs {
    Packet packet;
    int interval;

    PacketProcessArgs(Packet _packet, int _interval): packet(_packet), interval(_interval) {}
};

class ThreadManager {
public:
    ThreadManager(std::vector<Hardware>& devices);
    void run();

    // Static member functions
    static void* PacketCreate(void* arg);
    static void* PacketProcess(void* arg);
    

private:
    std::vector<Hardware> devices;

};

#endif // THREADMANAGER_H
