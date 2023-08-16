CXX = g++
ODIR = dist
SDIR = src
SOURCES = $(wildcard $(SDIR)/*.cpp)
OBJECTS = $(patsubst $(SDIR)/%.cpp, $(SDIR)/%.o, $(SOURCES))
CFLAGS = -Wno-c++11-extensions -I/src

all: lsmtree

lsmtree: $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o ./dist/lsmtree

$(SDIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) ./dist/lsmtree
	rm -f ./dist/lsmtree
