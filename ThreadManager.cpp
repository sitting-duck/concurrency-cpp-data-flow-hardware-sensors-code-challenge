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

    // Implementation for PacketCreate
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





