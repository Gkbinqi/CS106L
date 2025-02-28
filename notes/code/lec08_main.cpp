#include "lec08_Vector.h"
#include <iostream>

void printVector_const(const Vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v.at(i) << " ";
    }
    std::cout << std::endl;
}

void printVector_notconst(Vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v.at(i) << " ";
        v.at(i) = v.at(0);
    }
    std::cout << std::endl;
}

int main() {
    Vector<int> v;
    for (size_t i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    printVector_const(v);
    printVector_notconst(v);
    printVector_const(v);
    for(auto i : v) { // iterator
        std::cout<< i;
    }
    std::cout << '\n';
    std::cout << "size: " << v.size() << ' ' << "capacity: " << v.capacity() << '\n';
    return 0;
}