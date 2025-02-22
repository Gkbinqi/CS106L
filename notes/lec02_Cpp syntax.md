# Lec02 Types and Structs
> 2025/1/16

`this for code`  
**this for core concept**  

### Namesepace
* Namespaces: MANY things are in the std:: namespace
* e.g. std::cout, std::cin, std::lower_bound
* we may use `using namespace std;` declaration, which automatically adds **std::**, but thats not a good practice.

### STL
> STL = Standard Template Library  

Which contains TONS of functionality (algorithms, containers, functions, iterators) some of which we will explore in this class  
The namespace for the STL is **std** -- **std** is the abbreviation for *standard*  
To access elements from the STL use **std::**

### Types
C++ Fundamental Types(primitive types)  

```
int val = 5; //32 bits
char ch = 'F'; //8 bits (usually)
float decimalVal1 = 5.0;  //32 bits (usually)
double decimalVal2 = 5.0;  //64 bits (usually)
bool bVal = true;  //1 bit
//extended: string  
#include <string>
std::string str = "Sarah";
```

### C++ is a *statically* typed language  
* ***statically*** typed: everything with a name (variables, functions, etc) is given a type before runtime.  
* ***dynamically*** typed: everything with a name (variables, functions, etc) is given a type at runtime based on the thing’s current value. e.g. python

### Compiled vs Interpreted language
**Main Difference: When is source code translated?**   
**Source Code**: Original code, usually typed by a human into a computer in a human-friendly form(like C++ or Python)  
**Translated**: Converting source code into something that computer can understand (i.e. machine code), just like compiling.  
**Runtime**: Period when program is executing commands (after compilation, if compiled)

* Dynamically typed, interpreted:  
Types Checked on the fly, during execution, line by line. Example: Python

* Statically typed, compiled:   
Types before program runs during compilation-Example: C++

Using static typing helps us to prevent errors before our 
code runs.

### static types & function
It can define a mapping, function from some types to other types  
```int add(int a, int b);```  
int, int -> int  
``` string echo(string phrase);```   
string -> string  
```double divide(int a, int b);```  
int, int -> double  
```string hello();```  
void -> string  

### Function Overloading
> Define two functions with the same name but have different types.  

Core: same name but different **function signature**.  

```
int half(int x) {  
	std::cout << “1” << endl;
	return x / 2;
	}
double half(double x) {
	cout << “2” << endl;
	return x / 2;
	}
half(3) // uses version (1), returns 1 
half(3.0) // uses version (2), returns 1.5
```

Another example:

```
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

### Struct
> A group of named variables each with their own type. A way to bundle different types together

```
struct Student {
	string name; // these are called fields
	string state; // separate these by semicolons
	int age;
};
Student s;
s.name = "Sarah"; 
s.state = "CA";
s.age = 21; // use . to access fields
//is the same as ```Student s2= {"Sarah", "CA", 21};```

void printStudentInfo(Student s) {
	cout << s.name << " from " << s.state;
	cout << " (" << s.age ")" << endl;
}

Student randomStudentFrom(std::string state) {
	Student s;
	s.name = "Sarah";//random = always Sarah
	s.state = state;
	s.age = std::randint(0, 100);
	return s;
}

Student foundStudent = randomStudentFrom("CA");
std::cout << foundStudent.name << std::endl; // Sarah
```

### `std::pair`
> https://en.cppreference.com/w/cpp/utility/pair
> An STL built-in struct with two fields of any type  

*Defined in header <utility>*  
`template <class T1, class T2> struct pair;`

* std::pair is a template: You specify the types of the fields inside <> for each pair object you make  
* The fields in std::pairs are named first and second

```
std::pair<int, string> numSuffix = {1,"st"};
std::cout << numSuffix.first << numSuffix.second << std::endl; //print 1st
```
Use `std::pair` to return success + result  
To avoid specifying the types of a pair, use `std::make_pair(field1, field2)` 

```
std::pair<bool, Student> lookupStudent(string name) {
	Student blank;
	if (notFound(name)) return std::make_pair(false, blank);
	Student result = getStudentWithName(name);
	return std::make_pair(true, result);
}
std::pair<bool, Student> output = lookupStudent(“Julie”);
```

### Type Deduction with `auto`
> Keyword used in lieu(替代) of type when declaring a variable, tells the compiler to deduce the type automatically.  
> **`auto` doesn't mean that the variable don’t have a type. It means that the type is deduced by the compiler.**    

```
// What types are these?
auto a = 3; // int
auto b = 4.3; // double
auto c = ‘X’; // char
auto d = “Hello”; // char* (a C string)
auto e = std::make_pair(3, “Hello”); // std::pair<int, char*>
```

