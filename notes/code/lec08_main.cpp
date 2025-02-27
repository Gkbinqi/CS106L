#include "lec08_Vector.h"
#include <iostream>

void printVec(const Vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v.at(i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    Vector<int> v;
    for (size_t i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    printVec(v);
    return 0;
}