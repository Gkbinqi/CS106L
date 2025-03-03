#include "lec08_Vector.h"
#include <iostream>
#include <set>

void printVector_const(const Vector<size_t>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v.at(i) << " ";
    }
    std::cout << std::endl;
}

void printVector_notconst(Vector<size_t>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v.at(i) << " ";
        v.at(i) = v.at(0);
    }
    std::cout << std::endl;
}

std::ostream& operator<< (std::ostream& os, const std::set<size_t>& s) {
    os << s.size() << " ";
    return os;
}

int main() {
    Vector<size_t> v;
    for (size_t i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    printVector_const(v);
    printVector_notconst(v);
    printVector_const(v);
    for(auto& i : v) { // iterator
        std::cout<< i;
    }
    std::cout << '\n';
    std::cout << "size: " << v.size() << ' ' << "capacity: " << v.capacity() << '\n';

    Vector<std::set<size_t>> v2;
    for (size_t i = 0; i < 100; ++i) {
        std::set<size_t> s {i};
        v2.push_back(s);
    }
    for(auto& i : v2) { // iterator
        std::cout << i;
    }
    std::cout << '\n';
    std::cout << "size: " << v2.size() << ' ' << "capacity: " << v2.capacity() << '\n';
    return 0;
}