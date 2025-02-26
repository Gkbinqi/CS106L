# Classes

### Classes 

> Why and What?

##### Why?

* C has no objects
* No way of encapsulating data and the functions that operate on that data
* No ability to have object-oriented programming (OOP) design patterns

##### object-oriented-programming

* Object-oriented-programming is centered around objects 
* Focuses on design and implementation of classes! 
* Classes are the user-defined types that can be declared as an object!

##### struct & class

struct is a class without **access restriction** & member functions

##### public, protected, private

* public: accessible everywhere
* protect: accessible in the class itself and its sub-class
* private: only accessible in the class itself

##### Header File (.h) and Source Files (.cpp)

|          | Header File (.h)                                             | Source File (.cpp)                         |
| -------- | ------------------------------------------------------------ | ------------------------------------------ |
| Purpose  | Defines the **interface**                                    | Implements class functions                 |
| Contains | Function prototypes, class declarations, type definitions, macros, constants | Function implementations, executable code  |
| Access   | This is shared across source files                           | Is compiled into an object file            |
| Example  | `void someFunction();`                                       | `void someFunction() {implementation...};` |

##### class design

* A constructor 
  * The constructor initializes the state of newly created objects
* Private member functions/variables 
* Public member functions (interface for a user) 
* Destructor

```.h file
class StanfordID {
private:
    // An example of type aliasing
	using String = std::string;
	String name;
	String sunet;
	int idNumber;
public:
	// constructor for our StudentID, here The syntax for the constructor is just the name of the class
	StanfordID(std::string name, std::string sunet, int idNumber);
	// method to get name, sunet, and idNumber, respectively
	std::string getName();
	std::string getSunet();
	int getID();
}
```

```.cpp file
#include “StanfordID.h”
#include <string>

// default constructor
StanfordID::StanfordID() {
	name = “John Appleseed”;
	sunet = “jappleseed”;
	idNumber = 00000001;
}
// parameterized constructor
StanfordID::StanfordID(std::string name, std::string sunet, int idNumber) {
	this->name = name;
	this->sunet = sunet;
	this->idNumber = idNumber;
}

// list initialization constructor
// StanfordID::StanfordID(std::string name, std::string sunet, int idNumber): name{name}, sunet{sunet}, idNumber{idNumber} {};

StanfordID::~StanfordID() {
	// free/deallocate any data here
    // delete [] my_array; /// for illustration
}

std::string StanfordID::getName() {
    return this->name;
}

std::string StanfordID::getSunet() {
    return this->sunet;
}

int stanfordID::getID() {
    return this->idNumber;
}
```

* Remember namespaces, like `std::` In our `.cpp` file 
* Use this `this` keyword to disambiguate which `name` you’re referring to.
* We need to use our class as our **namespace** when defining our member functions

> Another code practice can be seen at code: lec07_IntVector.cpp.

### Inheritance

