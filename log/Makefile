CXX = g++
OBJECTS = set.cpp

all: set get reader_writer

reader_writer: ./src/reader_writer.cpp
	$(CXX) -o ./dist/reader_writer ./src/reader_writer.cpp

set: ./src/set.cpp
	$(CXX) -o ./dist/set ./src/set.cpp

get: ./src/get.cpp
	$(CXX) -o ./dist/get ./src/get.cpp

clean:
	rm -f ./dist/set
	rm -f ./dist/get
	rm -f ./dist/reader_writer
