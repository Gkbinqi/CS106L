![image-20250331144909608](C:\Users\47949\Desktop\CS106L\notes\pic\lec15.png)

# Lecture 15: RAII, Smart Pointers, Building Projects

### RAII (Resource Acquisition Is Initialization)

##### Exception

Exceptions are **thrown**

```.cpp file
try {
// code that we check for exceptions
}
catch([exception type] e1) { // "if"
// behavior when we encounter an error
}
catch([other exception type] e2) { // "else if"
// ...
}
catch { // the "else" statement
// catch-all (haha)
}
```

##### The problem

* It turns out that there are many resources that you need to release after acquiring
* if there are exception thrown between the gain and release of some resource, this resource may **leaked!**
  * Which means we can't use it again in the rest of this running. Like memory.
* How to we ensure that we **properly release resources in the case that we have an exception?**
  * example in PPT, like memory, mutex, socket and file

##### RAII: Resource Acquisition is Initialization

what is RAII? 

● All resources used by a class should be **acquired in the constructor**

● All resources used by a class should be **released in the destructor**

Benefit:

* By abiding by the RAII policy we avoid “half-valid” states.
* No matter what, **the destructor is called whenever the resource goes out of scope**.
* One more thing: the resource/object is usable immediately after it is created(calling the constructor will gain all the resource we need). 

e.g.:

```.cpp file
void cleanDatabase(mutex& databaseLock, map<int, int>& db) {
	lock_guard<mutex> lg(databaseLock);
	// now no other thread of machine can change db or modify the db
	...somecode
    // if exception is thrown here

	// no explicit unlock necessary here, lg will handle all the stuff!
}
```

* A lock guard is a RAII-compliant wrapper that attempts to acquire the passed in lock. It releases the the lock once it goes out of scope. 
  * The `lock_guard` class is non-copyable.
  * Read more here https://en.cppreference.com/w/cpp/thread/lock_guard

### Smart Pointer

**Avoiding `new` and `delete` explicitly**

* RAII for locks → `lock_guard`
  * Created a new object that **acquires the resource in the constructor and releases in the destructor**
* RAII for memory -> smart pointer
  * Do the same as above. These “wrapper” pointers are called “smart pointers”

![image-20250401094113320](C:\Users\47949\Desktop\CS106L\notes\pic\lec15_Smart Pointer.png)

There are three types of RAII-compliant pointers:

* `std::unique_ptr`
  * Uniquely owns its resource
  * Can’t be copied
* `std::shared_ptr`
  * Can make copies
  * **destructed when the <u>underlying memory</u> goes out of scope**
* `std::weak_ptr`
  * A class of pointers designed to **mitigate circular dependencies**

```.cpp file
void rawPtr() {
	Node* n = new Node();
	// do sth with n, may leak memory
	delete n;
}

void smartPtr() {
	std::unique_ptr<Node> n(new Node);
	// do sth with n
	// n is automatically freed with out manaual delete
}
```

##### `std::unique_ptr`

can't be copied

* imaging once we create a copy of a u_ptr and the u_ptr's destructor is called before the copy one's
  * it will cause delete a deallocated memory!

##### `std::shared_ptr`

Shared pointers get around our issue of trying to copy

* Deallocating the underlying memory until all shared pointers go out of scope!

![image-20250401094924241](C:\Users\47949\Desktop\CS106L\notes\pic\lec15_shared ptr.png)

##### `std::weak_ptr`

Weak pointers are a way to avoid circular dependencies in our code so that we don’t leak any memory.



##### Initializing smart pointers

```.cpp file
// avoid calling new and delete explicitly!

// std::unique_ptr<T> uniquePtr{new T}
std::unique_ptr<T> uniquePtr = std::make_unique<T>();

// std::shared_ptr<T> sharedPtr{new T}
std::shared_ptr<T> sharedPtr = std::make_shared<T>();

std::weak_ptr<T> wPtr = sharedPtr;
```

**Always use `std::make_unique` and `std::make_shared`**

* The most important reason
  * if we don’t, then we’re going to allocate memory twice, once for the pointer itself, and once for the new T
* We should also be consistent — if you use `make_unique` also use `make_shared`!

### Build C++ Project

##### Makefiles and make

* make is a “build system” program that helps you compile!
  * You can specify what compiler you want to use
  * In order to use make you need to have a Makefile
* Makefile

```makefile
# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++20
# Source files and target
SRCS = $(wildcard *.cpp)
TARGET = main
# Default target
all:
 $(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)
# Clean up
clean:
 rm -f $(TARGET)
```

##### CMake

* CMake is a build system generator. 
  * So you can use CMake to generate Makefiles 
  * Is like a higher level abstraction for Makefiles
  * CmakeList.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(cs106l_classes)
set(CMAKE_CXX_STANDARD 20)
file(GLOB SRC_FILES "*.cpp")
add_executable(main ${SRC_FILES})
```

* To use CMAKE
  * You need to have a CMakeLists.txt file in your project’s root directory
  * Make a build folder (mkdir build) within your project!
  * Go into the build folder (cd build)
  * Run cmake ..
    * This command runs cmake using the CMakeLists.txt in your project’s root folder!
    * This generates a Makefile
  * Run make
  * Execute your program using ./main as usual

### Recap

* RAII says that dynamically allocated resources should be acquired inside of the constructor and released inside the destructor. 
  * This is what smart pointers to for example
* For compiling our projects we can and should use Makefiles
* For making our Makefiles we can and should use CMAKE