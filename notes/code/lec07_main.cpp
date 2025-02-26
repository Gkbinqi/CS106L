#include "lec07_IntVector.cpp"
#include <iostream>

int main() {
    IntVector* v = new IntVector();

    for (int i = 0; i < 129; ++i) {
        v->push_back(i);
    }

    std::cout << v->size() << std::endl;
    for (auto i : *v) {
        std::cout << i << ' ';
    }
}