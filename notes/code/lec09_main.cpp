#include "lec09_find.h"
#include <string>
#include <vector>
#include <iostream>

struct lec09_main
{
    char* test;
};

// if these overloading exist, the compiler won't report error
bool operator < (const lec09_main& m1, const lec09_main& m2) {
    return true;
}

std::ostream& operator<< (std::ostream& os, lec09_main& m) {
    os << "output lec09_main into ostream" << '\n';
    return os;
}

std::ostream& operator<< (std::ostream& os, lec09_main&& m) {
    os << "output lec09_main into ostream" << '\n';
    return os;
}

int main() {
    std::vector<int> v{1,2,3,4,5};
    auto it = find(v.begin(), v.end(), 3);
    std::cout << *it << '\n';

    double a = 12.3;
    double b = 15.2;
    std::cout << min(a, b) << '\n';

    lec09_main m1{nullptr};
    lec09_main m2{nullptr};
    
    // call std::ostream& operator<< (std::ostream& os, lec09_main& m)
    std::cout << m1 << m2 << '\n';
    // call std::ostream& operator<< (std::ostream& os, lec09_main&& m)
    // if not defined "&&". report: 
    // error: cannot bind non-const lvalue reference of type 'lec09_main&' 
    // clear to an rvalue of type 'lec09_main'
    std::cout << min(m1, m2) << '\n';
    
    /* error message of this line
    $ g++ -static-libstdc++ -std=c++20 lec09_main.cpp -o main
    lec09_main.cpp: In function 'int main()':
    lec09_main.cpp:23:21: error: no matching function for call to 'min(lec09_main&, lec09_main&)'
    23 |     std::cout << min(m1, m2) << '\n';
       |                  ~~~^~~~~~~~
    In file included from lec09_find.h:16,
                    from lec09_main.cpp:1:
    lec09_find.cpp:14:3: note: candidate: 'template<class T>  requires  Comparable<T> T min(const T&, const T&)'
    14 | T min(const T& a, const T& b) {
        |   ^~~
    lec09_find.cpp:14:3: note: template argument deduction/substitution failed:
    lec09_find.cpp:14:3: note: constraints not satisfied
    lec09_find.h: In substitution of 'template<class T>  requires  Comparable<T> T min(const T&, const T&) [with T = lec09_main]':      
    lec09_main.cpp:23:21:   required from here
    23 |     std::cout << min(m1, m2) << '\n';
        |                  ~~~^~~~~~~~
    lec09_find.h:9:9:   required for the satisfaction of 'Comparable<T>' [with T = lec09_main]
    lec09_find.h:9:22:   in requirements with 'const T a', 'const T b' [with T = lec09_main]
    lec09_find.h:10:13: note: the required expression '(a < b)' is invalid
    10 |         { a < b } -> std::convertible_to<bool>;
        |           ~~^~~
    cc1plus.exe: note: set '-fconcepts-diagnostics-depth=' to at least 2 for more detail
    */
}