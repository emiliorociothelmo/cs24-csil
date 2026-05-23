// intlist.cpp
// Implements class IntList
// YOUR NAME, DATE

#include "intlist.h"
#include <iostream>
using std::cout;

// constructor sets up empty list
IntList::IntList() {
    head = nullptr;
    tail = nullptr;
}

// copy constructor - deep copy
IntList::IntList(const IntList& source) {
    head = nullptr;
    tail = nullptr;
    Node* n = source.head;
    while (n) {
        push_back(n->info);
        n = n->next;
    }
}

// destructor deletes all nodes
IntList::~IntList() {
    Node* n = head;
    while (n) {
        Node* next = n->next;
        delete n;
        n = next;
    }
    head = nullptr;
    tail = nullptr;
}

// assignment operator - deep copy
IntList& IntList::operator=(const IntList& source) {
    if (this == &source) return *this;
    Node* n = head;
    while (n) {
        Node* next = n->next;
        delete n;
        n = next;
    }
    head = nullptr;
    tail = nullptr;
    Node* s = source.head;
    while (s) {
        push_back(s->info);
        s = s->next;
    }
    return *this;
}

// insert value at front of list
void IntList::push_front(int value) {
    Node* newNode = new Node;
    newNode->info = value;
    newNode->next = head;
    head = newNode;
    if (tail == nullptr)
        tail = head;
}

// append value at end of list
void IntList::push_back(int value) {
    Node* newNode = new Node;
    newNode->info = value;
    newNode->next = nullptr;
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// return count of values
int IntList::count() const {
    int cnt = 0;
    Node* n = head;
    while (n) {
        cnt++;
        n = n->next;
    }
    return cnt;
}

// return sum of values in list
int IntList::sum() const {
    int total = 0;
    Node* n = head;
    while (n) {
        total += n->info;
        n = n->next;
    }
    return total;
}

// returns true if value is in the list
bool IntList::contains(int value) const {
    Node* n = head;
    while (n) {
        if (n->info == value) return true;
        n = n->next;
    }
    return false;
}

// returns maximum value in list, or 0 if empty
int IntList::max() const {
    if (head == nullptr) return 0;
    int m = head->info;
    Node* n = head->next;
    while (n) {
        if (n->info > m) m = n->info;
        n = n->next;
    }
    return m;
}

// returns average of all values, or 0 if empty
double IntList::average() const {
    if (head == nullptr) return 0.0;
    return (double)sum() / count();
}

// DO NOT CHANGE ANYTHING BELOW
void IntList::print() const {
    Node* n = head;
    cout << '[';
    while (n) {
        cout << n->info;
        if (n->next) cout << " ";
        n = n->next;
    }
    cout << ']';
}
