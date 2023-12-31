CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread

# Add HardwareFactory.o to the object files list
OBJ = main.o Hardware.o Packet.o HardwareFactory.o ThreadManager.o Pose.o PoseFactory.o Time.o Client.o ClientManager.o

all: main

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Hardware.o: Hardware.cpp Hardware.h
	$(CXX) $(CXXFLAGS) -c Hardware.cpp

Packet.o: Packet.cpp Packet.h
	$(CXX) $(CXXFLAGS) -c Packet.cpp

HardwareFactory.o: HardwareFactory.cpp HardwareFactory.h
	$(CXX) $(CXXFLAGS) -c HardwareFactory.cpp

ThreadManager.o: ThreadManager.cpp ThreadManager.h
	$(CXX) $(CXXFLAGS) -c ThreadManager.cpp

Pose.o: Pose.cpp Pose.h
	$(CXX) $(CXXFLAGS) -c Pose.cpp	

PoseFactory.o: PoseFactory.cpp PoseFactory.h
	$(CXX) $(CXXFLAGS) -c PoseFactory.cpp	

Time.o: Time.cpp Time.h
	$(CXX) $(CXXFLAGS) -c Time.cpp

Client.o: Client.cpp Client.h
	$(CXX) $(CXXFLAGS) -c Client.cpp

ClientManager.o: ClientManager.cpp ClientManager.h
	$(CXX) $(CXXFLAGS) -c ClientManager.cpp	

clean:
	rm -f *.o main
