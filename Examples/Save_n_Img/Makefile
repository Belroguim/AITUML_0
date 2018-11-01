CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)

all: opencv_example

opencv_example: opencv_example.o; $(CXX) $< -o $@ $(LDFLAGS) -lwiringPi 

%.o: %.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f opencv_example.o opencv_example
