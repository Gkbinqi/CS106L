# Lec01 Intro

### Course Goals:

* Learn what features are out there in C++ and why they exist.
* Become comfortable reading C++ documentation (回过头来看, 这一点很赞, 以前翻文档和天书一样)
  * C++ documentation is “expert-friendly”
  * We will "be expert" to read the documentation in this class

* Become familiar with the design philosophy of **modern C++**

### Why Cpp?

* C++ is an extremely ubiquitous and important language
  * The invisible foundation of everything

* Fast & Low-level control
  * C++ is all about efficiency and transparency of intent

### C++ Design Philosophy

* Give programmers more choice (at the cost of more responsibility, like managing memory by yourself).
* Catch errors at compile-time (at the cost of being slightly more verbose).
* Compartmentalize messy constructs.(Example: smart pointers)

Example Code

```c++
#include <iostream>
#include <string> // templates
int main() {
	auto str = std::make_unique<std::string>("Hello World!"); // auto, unique_ptr and move
	std::cout << *str << std::endl; // stream and Operator Overloading <<
	return 0;
}
```

### C++ helps develop good coding hygiene

* Am I using objects the way they’re meant to be used?
  * Type checking, type safety
* Am I using memory efficiently?
  * Reference/copy semantics, move semantics
* Am I modifying something I’m not supposed to?
  * `const` and const correctness
* While other languages relax these restrictions



