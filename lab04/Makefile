CXX=g++
CXXFLAGS=-std=c++17

all: examheap testlist

examheap: examheap.cpp heap.cpp heap.h
	$(CXX) $(CXXFLAGS) -o examheap examheap.cpp heap.cpp

testlist: testlist.cpp heap.cpp heap.h
	$(CXX) $(CXXFLAGS) -o testlist testlist.cpp heap.cpp

clean:
	rm -f examheap testlist
