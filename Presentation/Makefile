# Improved Makefile by Brett Huffman v1.1
# (c)2021 Brett Huffman
# To use, just change the next line to the name of
# the application

# App 1 - builds the gifting program
appname1 := gifting
srcfiles := $(shell find . -name "gift*.cpp")
objects1  := $(patsubst %.cpp, %.o, $(srcfiles))
CXXFLAGS := -g -std=c++11 -Wall -pedantic -Wno-sign-compare

all: $(appname1)

$(appname1): $(objects1)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname1) $(objects1) $(LDLIBS)

clean:
	rm -f $(objects1)
	rm -f $(appname1)
