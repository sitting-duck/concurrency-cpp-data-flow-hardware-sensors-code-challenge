CXX = g++
CXXFLAGS = -Wall -std=c++11

all: main

main: main.o Packet.o Hardware.o
	$(CXX) $(CXXFLAGS) -o main main.o Packet.o Hardware.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Packet.o: Packet.cpp Packet.h
	$(CXX) $(CXXFLAGS) -c Packet.cpp

Hardware.o: Hardware.cpp Hardware.h Packet.h
	$(CXX) $(CXXFLAGS) -c Hardware.cpp

clean:
	rm -f *.o main

