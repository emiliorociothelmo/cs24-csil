CXX=g++
CXXFLAGS=-std=c++17

all: examheap testlist

examheap: examheap.cpp heap.cpp heap.h
	$(CXX) $(CXXFLAGS) -o examheap examheap.cpp heap.cpp

testlist.o: heap.h
	$(CXX) $(CXXFLAGS) -c testlist.cpp

heap.o: heap.cpp heap.h
	$(CXX) $(CXXFLAGS) -c heap.cpp

testlist: testlist.o heap.o
	$(CXX) $(CXXFLAGS) -o testlist testlist.o heap.o

clean:
	rm -f examheap testlist *.o
