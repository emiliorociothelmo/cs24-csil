#include "intlist.h"
#include <iostream>
using std::cout;

// Name: Milo Thelmo
// Date: 2026-01-16

#include "intlist.h"
#include <iostream>
using std::cout;

// Name...
// Date...

// default constructor
IntList::IntList() {
    head = nullptr;
    tail = nullptr;
}

// copy constructor (deep copy)
IntList::IntList(const IntList& source) {
    head = nullptr;
    tail = nullptr;

    Node* curr = source.head;
    while (curr != nullptr) {
        push_back(curr->info);   // uses your working push_back
        curr = curr->next;
    }
}

// destructor (delete all nodes)
IntList::~IntList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
}

// assignment operator (deep copy, handles self-assignment)
IntList& IntList::operator=(const IntList& source) {
    if (this == &source) return *this;   // self-assignment guard

    // 1) delete current list
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;

    // 2) deep copy from source
    curr = source.head;
    while (curr != nullptr) {
        push_back(curr->info);
        curr = curr->next;
    }

    return *this;
}



// return sum of values in list
int IntList::sum() const {
    int total = 0;
    Node* curr = head;
    while (curr != nullptr) {
        total += curr->info;
        curr = curr->next;
    }
    return total;
}

// returns true if value is in the list; false if not
bool IntList::contains(int value) const {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->info == value) return true;
        curr = curr->next;
    }
    return false;
}

// returns maximum value in list, or 0 if empty list
int IntList::max() const {
    if (head == nullptr) return 0;

    int best = head->info;
    Node* curr = head->next;
    while (curr != nullptr) {
        if (curr->info > best) best = curr->info;
        curr = curr->next;
    }
    return best;
}

// returns average (arithmetic mean) of all values, or 0 if empty
double IntList::average() const {
    int n = count();
    if (n == 0) return 0.0;
    return static_cast<double>(sum()) / n;
}

// inserts value as new node at beginning of list
void IntList::push_front(int value) {
    Node* n = new Node();
    n->info = value;
    n->next = head;

    head = n;
    if (tail == nullptr) {
        tail = n;
    }
}

// append value at end of list
void IntList::push_back(int value) {
    Node* n = new Node();
    n->info = value;
    n->next = nullptr;

    if (head == nullptr) {
        head = tail = n;
        return;
    }

    tail->next = n;
    tail = n;
}

// return count of values
int IntList::count() const {
    int n = 0;
    Node* curr = head;
    while (curr != nullptr) {
        n++;
        curr = curr->next;
    }
    return n;
}

// DO NOT CHANGE ANYTHING BELOW (READ IT THOUGH)

// print values enclose in [], separated by spaces
void IntList::print() const {
    Node *n = head;
    cout << '[';
    while (n) {
        cout << n->info;
        if (n->next)
            cout << " ";
        n = n->next;
    }
    cout << ']';
}

