# Lec 02 Types and Structs
`this for code`  
**this for core concept**  

### Basic

##### Namespace

* Namespaces: MANY things are in the std:: namespace
* e.g. `std::cout`, `std::cin`, `std::lower_bound`
* we may use `using namespace std;` declaration, which automatically adds `std::`, but that's not a good practice.
  * What if we declare some customer types that share the same name with STL?


##### STL

> STL = Standard Template Library  

`std` ― The C++ Standard Library

* Built-in types, functions, and more provided by C++
  * Which contains TONS of functionality 
  * Mainly four parts: **algorithms, containers, functions, iterators**
  * Some of which we will explore in this class  
* You need to `#include` the relevant file
  * `#include <string>`  → `std::string`
  * `#include <utility>`  → `std::pair`
  * `#include <iostream>` → `std::cout`, `std::endl`
  * What dose #include do?
    * In short, Link the file with cur file
* We prefix standard library names with `std::`

* The namespace for the STL is **std** -- **std** is the abbreviation for *standard* 
* Official standard at <u>cppreference.com</u>

##### Types

* A type refers to the “category” of a variable

C++ Fundamental Types(primitive types)  

```.cpp file
int val = 5; //32 bits
char ch = 'F'; //8 bits (usually)
float decimalVal1 = 5.0;  //32 bits (usually)
double decimalVal2 = 5.0;  //64 bits (usually)
bool bVal = true;  //1 bit
//extended: string  
#include <string>
std::string str = "Sarah";
size_t size = 12 // non-negative value
```

### C++ is a compiled and *statically* typed language  
* ***statically*** typed: everything with a name (variables, functions, etc.) is given a type before runtime.  
* ***dynamically*** typed: everything with a name (variables, functions, etc.) is given a type at runtime based on the thing’s current value. 
  * e.g. python

* Runtime: Period when program is executing commands (after compilation, if compiled)

##### Compiled vs Interpreted language

Main Difference: When is source code translated(compiled)?

* Dynamically typed, interpreted:  
  * translated at the runtime
  * Types Checked on the fly, during execution, line by line. 
  * Example: Python

* Statically typed, compiled: 
  * translated at the compile time, get the actual machine code, then run.  
  * Types Checked before program runs during compilation


Using static typing has: More efficient, Prevent errors before our code runs & Better error checking.

##### static types & function

It can define a mapping, function from some types to other types  
```int add(int a, int b);```  
int, int -> int  
``` string echo(string phrase);```   
string -> string  
```double divide(int a, int b);```  
int, int -> double  
```string hello();```  
void -> string  

##### Function Overloading

> Define two functions with the same name but have different types.  

Core: same name but different **function signature**(name, parameter type and return value type).  

```.cpp file
int half(int x) {  // int -> int
	std::cout << “1” << endl;
	return x / 2;
	}
double half(double x) { // double -> double
	cout << “2” << endl;
	return x / 2;
	}
half(3) // uses version (1), returns 1 
half(3.0) // uses version (2), returns 1.5
```

Another example:

```.cpp file
int half(int x, int divisor = 2) {
	return x / divisor;
}
double half(double x) {
	return x / 2;
}
half(4) // uses version (1), returns 2 
half(3, 3) // uses version (1), returns 1 
half(3.0) // uses version (2), returns 1.5
```

### Basic Again

##### Struct

> A group of named variables each with their own type. A way to bundle different types together

A **struct** bundles named variables into a new type

```.cpp file
struct Student {
	string name; // these are called fields
	string state; // separate these by semicolons
	int age; // Each has a name and type
};
Student s; // initialize a struct
s.name = "Sarah"; 
s.state = "CA";
s.age = 21; // use . to access fields

// List Initialization
// Order depends on field order in struct. ‘=‘ is optional
struct StanfordID {
	string name; 
	string sunet; 
	int idNumber;
};
StanfordID jrb = { "Jacob Roberts-Baca", "jtrb", 6504417 }; //  ‘=‘ is optional
StanfordID fi { ”Fabio Ibanez", ”fibanez", 6504418 };
StanfordID issueNewID() {
	return { "Jacob Roberts-Baca", "jtrb", 6504417 };
}

```

##### `std::pair` template

> https://en.cppreference.com/w/cpp/utility/pair
> An STL built-in struct with two fields of any type  

*Defined in header <utility>*  
`template <class T1, class T2> struct pair;`

```c++
template <typename T1, typename T2>
struct pair {
	T1 first;
	T2 second;
};
std::pair<std::string, int>
```

* `std::pair` is a **template**: You specify the types of the fields inside` <>` for each pair object you make  
* The fields in `std::pairs` are named first and second

```c++
#include <utility>
std::pair<int, std::string> numSuffix {1,"st"};
std::cout << numSuffix.first << numSuffix.second << std::endl; //print 1st
```
Use `std::pair` to return success + result  
To avoid specifying the types of a pair, use `std::make_pair(field1, field2)` 

```.cpp file
std::pair<bool, Student> lookupStudent(string name) {
	Student blank;
	if (notFound(name)) return std::make_pair(false, blank);
	Student result = getStudentWithName(name);
	return std::make_pair(true, result);
}
std::pair<bool, Student> output = lookupStudent(“Julie”);
```

##### `using` keyword

We can create **type aliases** with the `using` keyword

* using is kind of like a variable for types!

```c++
// before
std::pair<bool, std::pair<double, double>> solveQuadratic(double a, double b, double c);

// after
using Zeros = std::pair<double, double>;
using Solution = std::pair<bool, Zeros>;
Solution solveQuadratic(double a, double b, double c);
```

##### `auto` keyword

> Keyword used in lieu(替代) of type when declaring a variable, tells the compiler to deduce the type automatically.  

`auto` doesn't mean that the variable don’t have a type. It means that **the type is deduced by the compiler**.    

```.cpp file
// What types are these?
auto a = 3; // int
auto b = 4.3; // double
auto c = ‘X’; // char
auto d = “Hello”; // char* (a C string)
auto e = std::make_pair(3, “Hello”); // std::pair<int, char*>
```

* We should use it to reduce long type name while it doesn't make the code less straightforward.

e.g. Quadratic  

```c++
int main() {
   int a, b, c;
   std::cin >> a >> b >> c;
   // std::pair<bool, std::pair<double, double>> result = quadratic(a, b, c);
   auto result = quadratic(a, b, c); // using auto
   bool found = result.first;
   if (found) {
      // std::pair<double, double> solutions = result.second;
      auto solutions = result.second; // using auto
      std::cout << solutions.first << solutions.second << endl;
   } else {
      std::cout << “No solutions found!” << endl;
   }
 }
```

* Using `auto` we can make the code easier.

  * Meanwhile, do not overuse `auto`  

    ```c++
    int main() {
       auto a, b, c; // compiler error!
       std::cin >> a >> b >> c;
       ...
    ```

    

