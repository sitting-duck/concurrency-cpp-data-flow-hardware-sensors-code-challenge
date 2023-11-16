CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread

all: main

main: main.o Packet.o Hardware.o Algorithm.o Pose.o
	$(CXX) $(CXXFLAGS) -o main main.o Packet.o Hardware.o Algorithm.o Pose.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Packet.o: Packet.cpp Packet.h
	$(CXX) $(CXXFLAGS) -c Packet.cpp

Hardware.o: Hardware.cpp Hardware.h Packet.h
	$(CXX) $(CXXFLAGS) -c Hardware.cpp

Algorithm.o: Algorithm.cpp Algorithm.h
	$(CXX) $(CXXFLAGS) -c Algorithm.cpp

Pose.o: Pose.cpp Pose.h
	$(CXX) $(CXXFLAGS) -c Pose.cpp

clean:
	rm -f *.o main

