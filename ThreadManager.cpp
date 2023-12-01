#include "ThreadManager.h"
#include "PoseFactory.h"
#include <pthread.h>
#include <unistd.h>

#include "Pose.h"
#include "Time.h"
#include "Packet.h"

// Forward declaration of functions
void* PacketCreate(void* arg);
void* PacketProcess(void* arg);

ThreadManager::ThreadManager(std::vector<Hardware>& devices) : devices(devices) {}

void ThreadManager::run() {
    std::cout << "run()" << std::endl;

    std::vector<pthread_t> threads;
    std::vector<std::vector<Pose*>*> allPoses; 

    for (auto device : devices) {
        pthread_t thread;
        pthread_create(&thread, nullptr, PacketCreate, &device);
        std::cout << "creating thread for device" << device.getUuid() << std::endl;
        threads.push_back(thread);
    }

    // Join threads & collect array of Poses from each thread and push them all into a master list
    for (auto& thread : threads) {
        void* retval;
        pthread_join(thread, &retval);
        
        allPoses.push_back(static_cast<std::vector<Pose*>*>(retval));
    }

    // Probably here I would have the clients consume the packets and associated poses. 

    // Clean up
    std::cout << "run(): clean up" << std::endl;
    for (auto* poseVector : allPoses) {
        for (auto* pose : *poseVector) {
            if(pose) {
                delete pose;  // Delete individual Poses    
            }
            
        }
        if(poseVector) {
            delete poseVector;  // Delete the vector itself    
        }
        
    }
}

void* ThreadManager::PacketCreate(void* arg) {
    std::cout << "PacketCreate()" << std::endl;

    // Create a thread for each sensor in the device
    Hardware* device = static_cast<Hardware*>(arg);
    Packet packet = device->generateDataPacket();

    PacketProcessArgs* args = new PacketProcessArgs(packet, device->getIntervalAsInt());

    std::vector<pthread_t> threads;
    std::vector<Pose*> poses(device->getNumSensors());

    for(int i = 0; i < device->getNumSensors(); i++) {
        pthread_t thread;
        pthread_create(&thread, nullptr, PacketProcess, args);
        std::cout << "\tcreating child thread for sensor" << i << std::endl;
        threads.push_back(thread);
    }

    // Join threads and collect Poses
    for (int i = 0; i < device->getNumSensors(); i++) {
        void* retval;
        pthread_join(threads[i], &retval);
        poses[i] = static_cast<Pose*>(retval);  // Collect Pose pointers
    }

    // Clean up
    std::cout << "PacketCreate(): Clean up" << std::endl;
    if(args) {
        delete args;    
    }

    // Instead of cleaning up Pose pointers here, return the vector of poses to be collected upstream
    std::vector<Pose*>* posesPtr = new std::vector<Pose*>(std::move(poses));
    return posesPtr;
}

void* ThreadManager::PacketProcess(void* args) {
    std::cout << "PacketProcess()" << std::endl;

    PacketProcessArgs* arg = static_cast<PacketProcessArgs*>(args);

    int sleepDuration = Time::calculateProcessingTime(arg->interval);
    usleep(sleepDuration);
    std::cout << "\t\tPacket: " << arg->packet.getUUID() << " finished processing." << std::endl;

    Pose* pose = new Pose(PoseFactory::createRandomPose());

    return pose;
}

void ThreadManager::subscribeClients() {
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






