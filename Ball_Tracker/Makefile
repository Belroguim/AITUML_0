CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)

all: BT_CVM

BT_CVM: BT_CVM.o; $(CXX) $< -o $@ $(LDFLAGS) -lwiringPi 

%.o: %.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f BT_CVM.o BT_CVM
