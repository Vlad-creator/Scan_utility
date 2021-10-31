CXX = g++-9
CXXFLAGS = -c -Wall -O0 -std=c++2a -MD -lstdc++fs

.PHONY: clean

all: main

main: suspicious.o scan.o main.o
	 $(CXX) suspicious.o scan.o main.o -o $@

scan.o: src/scan.cpp
	 $(CXX) src/scan.cpp $(CXXFLAGS)

suspicious.o: src/suspicious.cpp
	 $(CXX) src/suspicious.cpp $(CXXFLAGS)

main.o: main.cpp
	 $(CXX) main.cpp $(CXXFLAGS)

clean:
	rm -rf *.o *.d main scan suspicious

-include *.d