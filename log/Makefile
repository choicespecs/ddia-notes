CXX = g++
OBJECTS = set.cpp

all: set get

set: ./src/set.cpp
	$(CXX) -o ./dist/set ./src/set.cpp

get: ./src/get.cpp
	$(CXX) -o ./dist/get ./src/get.cpp

clean:
	rm -f ./dist/set
	rm -f ./dist/get
