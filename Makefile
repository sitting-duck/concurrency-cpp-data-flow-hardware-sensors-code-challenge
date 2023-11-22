CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread

# Add HardwareFactory.o to the object files list
OBJ = main.o Hardware.o Packet.o HardwareFactory.o ThreadManager.o Pose.o

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

clean:
	rm -f *.o main
