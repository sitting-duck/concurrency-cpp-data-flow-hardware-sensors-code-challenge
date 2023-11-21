CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread

# Add HardwareFactory.o to the object files list
OBJ = main.o Hardware.o Packet.o HardwareFactory.o

all: main

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Hardware.o: Hardware.cpp Hardware.h
	$(CXX) $(CXXFLAGS) -c Hardware.cpp

Packet.o: Packet.cpp Packet.h
	$(CXX) $(CXXFLAGS) -c Packet.cpp

# New target for compiling HardwareFactory
HardwareFactory.o: HardwareFactory.cpp HardwareFactory.h
	$(CXX) $(CXXFLAGS) -c HardwareFactory.cpp

clean:
	rm -f *.o main
