output: main.o Protocol.o CRC16.o
	g++ main.o Protocol.o CRC16.o -o output -I example/

main.o: example/main.cpp
	g++ -c example/main.cpp

Protocol.o: Protocol/Protocol.h Protocol/Protocol.cpp
	g++ -c Protocol/Protocol.cpp -Iexample

CRC16.o: Protocol/CRC16.h Protocol/CRC16.c
	g++ -c Protocol/CRC16.c -Iexample
clean:
	del *.o *.exe
