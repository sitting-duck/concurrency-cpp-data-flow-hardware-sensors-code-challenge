#include "ThreadManager.h"
#include <pthread.h>
#include <unistd.h>

// Forward declaration of functions
void* PacketCreate(void* arg);
void* PacketProcess(void* arg);

ThreadManager::ThreadManager(std::vector<Hardware>& devices) : devices(devices) {}

void ThreadManager::run() {
    std::vector<pthread_t> threads;
    for (auto device : devices) {
        pthread_t thread;
        pthread_create(&thread, nullptr, PacketCreate, &device);
        std::cout << "creating thread for device" << device.getUuid() << std::endl;
        threads.push_back(thread);
    }

    // Join threads
    for (auto& thread : threads) {
        pthread_join(thread, nullptr);
    }
}

void* ThreadManager::PacketCreate(void* arg) {
    // Implementation for PacketCreate
    // Create a thread for each sensor in the device
    Hardware* device = static_cast<Hardware*>(arg);
    Packet packet = device->generateDataPacket();
    PacketProcessArgs* args = new PacketProcessArgs(packet, device->getIntervalAsInt());
    //args.packet = packet;
    //args.interval = device.getIntervalAsInt();

    std::vector<pthread_t> threads;
    for(int i = 0; i < device->getNumSensors(); i++) {
        pthread_t thread;
        pthread_create(&thread, nullptr, PacketProcess, &args);
        std::cout << "\tcreating child thread for sensor" << i << std::endl;
        threads.push_back(thread);
    }

    // Join threads
    for (auto& thread : threads) {
        pthread_join(thread, nullptr);
    }

    // std::cout << "before delet" << std::endl;
    if(args) {
        delete args;    
    }
    
    // std::cout << "after delet" << std::endl;

    std::cout << "\tgonna create the Pose here" << std::endl;
    return 0;

}

void* ThreadManager::PacketProcess(void* args) {
    PacketProcessArgs* arg = static_cast<PacketProcessArgs*>(args);

    usleep(arg->interval);
    std::cout << "\t\tPacket: " << arg->packet.getUUID() << "finished processing." << std::endl;
    return 0;

}
