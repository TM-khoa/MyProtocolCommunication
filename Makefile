CXX = g++
OBJ = main.o Protocol.o CRC16.o
CXXFLAGS = -Wall
PROTOCOL_HEADER = Protocol/Protocol.h
CRC16_HEADER = Protocol/CRC16.h
PROTOCOL_DIR = Protocol
PROTOCOL_SOURCE = $(wildcard $(PROTOCOL_DIR)/*.cpp)


MyProtocol: $(OBJ)
	$(CXX) $(OBJ) -o $@

main.o: example/main.cpp
	$(CXX) -c $(CXXFLAGS) example/main.cpp

Protocol.o: $(PROTOCOL_HEADER)/ Protocol/Protocol.cpp
	$(CXX) -c $(CXXFLAGS) -Iexample Protocol/Protocol.cpp -o $@

CRC16.o: $(CRC16_HEADER) Protocol/CRC16.c
	$(CXX) -c $(CXXFLAGS) -Iexample Protocol/CRC16.c -o $@ 
clean:
	del *.o *.exe
print-%:
	@echo $($(subst print-,,@))
