// heap.cpp
// Emilio Thelmo
#include "heap.h"
#include <iostream>
using std::cout;

Heap::Heap(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    vdata.assign(start, end);
    int n = vdata.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        int cur = i;
        while (true) {
            int left  = 2 * cur + 1;
            int right = 2 * cur + 2;
            int smallest = cur;
            if (left  < n && vdata[left]  < vdata[smallest]) smallest = left;
            if (right < n && vdata[right] < vdata[smallest]) smallest = right;
            if (smallest == cur) break;
            std::swap(vdata[cur], vdata[smallest]);
            cur = smallest;
        }
    }
}

void Heap::push(int value) {
    vdata.push_back(value);
    int i = vdata.size() - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (vdata[i] < vdata[parent]) {
            std::swap(vdata[i], vdata[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

void Heap::pop() {
    vdata[0] = vdata.back();
    vdata.pop_back();
    int i = 0;
    int n = vdata.size();
    while (true) {
        int left  = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left  < n && vdata[left]  < vdata[smallest]) smallest = left;
        if (right < n && vdata[right] < vdata[smallest]) smallest = right;
        if (smallest == i) break;
        std::swap(vdata[i], vdata[smallest]);
        i = smallest;
    }
}

int Heap::top() {
    return vdata[0];
}

bool Heap::empty() {
    return vdata.empty();
}
