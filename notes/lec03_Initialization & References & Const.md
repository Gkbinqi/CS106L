# Lec 03 Initialization & References & Const

### Recap

* `auto`: a keyword that tells the compiler to deduce the type of an object or variable
  * Use at your discretion, typically when the type is annoyingly verbose to write out
* **Structs** are a way to bundle many variables into one type

### Initialization & Uniform initialization
> *Initialization of a variable provides its initial value at the time of construction.*
>
> https://en.cppreference.com/w/cpp/language/initialization

Three ways to initialize a variable:  

Use uniform initialization — it works for all types and objects!

##### Direct initialization

* No type check, not recommended.
  * C++ doesn’t do type checking with direct initialization

```c++
#include <iostream>
int main() {
 // Direct initialization with a floating-point value
 int criticalSystemValue(42.5); // narrowing conversion happens here, we cut off floating number and only save the integer part as 42
 // or int criticalSystemValue = 42.5;

 // Critical system operations...
 // ...
 std::cout << "Critical system value: " << criticalSystemValue << std::endl; //problem: output 42
 return 0;
}
```

##### Recommended: Uniform initialization

* Curly bracket initialization `{}`

  ```c++
  std::vector<int> vec{1,3,5};
  int numOne{12.0}; // compile error here
  std::pair<int, string> numSuffix1{1,"st"};
  Student s{"Sarah", "CA", 21};
  ```

* Benefits:

  * Safe. With uniform initialization C++ does care about types! 

  * Ubiquitous. it works for all types like vectors, maps, and custom classes, among other things!

    ```c++
    std::map<std::string, int> ages{ {"Alice" , 25}, {"Bob" , 30}, {"Charlie" , 35} };
    std::vector<int> numbers{1, 2, 3, 4, 5};
    
    // these two guys are different
    std::vector<int> vector_paren(3, 5); // {5, 5, 5}
    std::vector<int> vector_curly{3, 5}; // {3, 5}
    // https://www.onlinegdb.com/8uxNBkJBx
    ```

##### Structured Binding

* A useful way to initialize some variables from data structures with fixed sizes at compile time
* Ability to access multiple values returned by a function
* Can use on objects where the size is known at compile-time
* Works for regular structs, too.  
  * What's more, **no** nested structured binding.  

```c++
std::tuple<std::string, std::string, std::string> getClassInfo() {
 std::string className = "CS106L";
 std::string buildingName = "Turing Auditorium";
 std::string language = "C++";
 return {className, buildingName, language}; 
 // Notice - uniform initialization to initialize the return tuple
}
int main() {
 // auto classInfo = getClassInfo();
 // std::string className = std::get<0>(classInfo);
 // std::string buildingName = std::get<1>(classInfo);
 // std::string language = std::get<2>(classInfo);

 auto [className, buildingName, language] = getClassInfo(); // structure binding
 std::cout << "Come to " << buildingName << " and join us for " << className
 << " to learn " << language << "!" << std::endl;
 return 0;
}
```

Here is the code of quadratic using structured binding:  

```c++
 int main() {
   int a, b, c;
   std::cin >> a >> b >> c;
   auto [found, solutions] = quadratic(a, b, c);
   if (found) {
   auto [x1, x2] = solutions;
      std::cout << x1 << “ ” << x2 << endl;
   } else {
      std::cout << “No solutions found!” << endl;
   }
 }
```

### References `&` 
> *Declares a named variable as a reference, that is, an alias(别名) to an already-existing object or function.*
>
> https://en.cppreference.com/w/cpp/language/reference

##### References to variables

* Key: A reference refers to the **same memory** as its associated variable!  **PPT: page 53**
  * C++, by default, **makes copies** when we do `=` variable assignment
    * If not overloaded, `=` will **simply copy the right side's variable's memory value to the left side**
  * We need to use `&` if we need references instead.

```c++
vector<int> original{1, 2};
vector<int> copy = original; // '=' is overloaded so it will actually make a deep copy which creates a new vector. The copy and the original points to different address
// If we don't want it we must use `&` to avoid this. It's all about using `&` to create a alias
// copy construction

vector<int>& ref = original; // using & we got ref as a reference to original, they have the same address
original.push_back(3);
copy.push_back(4);
ref.push_back(5);
std::cout << original << std::endl; // {1, 2, 3, 5}
std::cout << copy << std::endl;     // {1, 2, 4}
std::cout << ref << std::endl;      // {1, 2, 3, 5}
```
##### Pass by reference

* Passing in parameter

  ```c++
  #include <iostream>
  #include <math.h>
  void squareN(int& n) { // note the ampersand!
   n = std::pow(n, 2);  // calculates n to the power of 2
  }
  
  void squareM(int m) { // passing by value, make a copy, no effect on the original m
      m = std::pow(m, 2);
  }
  int main() {
   int num = 2;
   int m = 3;
   squareN(num); // here the num in the main block are actually modified by the function squareN.
   squareM(m);
   std::cout << num << std::endl; // output: 4
   std::cout << m << std::endl; // output: 3
   return 0;
  }
  ```

  * Passing in a variable **by reference** 
    * Do not make a copy
    * Access the memory of variable passed by reference
  * Passing in a variable **by value** 
    * Make a copy in the function scope
    * Access a new chunk of memory, won't affect the original variable since they are using two independent chunks of memory

* We can also **return a reference** which won't make a copy

  ```c++
  // https://www.onlinegdb.com/o8luVxGpf
  // Note that the parameter must be a non-const reference to return a non-const reference to one of its elements!
  int& front(std::vector<int>& vec) {
  	// assuming vec.size() > 0
  	return vec[0];
  }
  
  // it can also return a const reference
  const int& c_front_right(const std::vector<int>& vec) {
      return vec[0];
  }
  
  int& c_front_false(const std::vector<int>& vec) {
      return vec[0]; // compile error here
  }
  /*
  main.cpp: In function ‘int& c_front_false(const std::vector<int>&)’:
  main.cpp:28:17: error: binding reference of type ‘int&’ to ‘const __gnu_cxx::__alloc_traits, int>::value_type’ {aka ‘const int’} discards qualifiers
     28 |     return vec[0];
  */
  
  int main() {
      std::vector<int> numbers{1, 2, 3};
      front(numbers) = 4; // now, vec == {4, 2, 3}
      
      c_front_right(numbers) = 3;
      /*
      main.cpp: In function ‘int main()’:
  	main.cpp:35:28: error: assignment of read-only location ‘c_front_right(numbers)’
     35 |     c_front_right(numbers) = 3;
        |     ~~~~~~~~~~~~~~~~~~~~~~~^~~
      */
      
      return 0;
  }
  ```

  ```c++
  std::ostream& operator<<(std::ostream& os, const MyClass& myclass) {
      os << myclass.a_string_member_variable << '\n';
      return os; // return by reference
  }
  ```

##### code demo

```c++
#include <iostream>
#include <math.h>
#include <vector>
void shift(std::vector<std::pair<int, int>> &nums) { // here we get nums by reference
 for (auto [num1, num2] : nums) { // Notice, here creates a copy of the nums[i]
 // we are still modifying a copy
 num1++;  // this is updating the copy
 num2++;
 }
}

void shift_fixed(vector<std::pair<int, int>>& nums) {
 for (auto& [num1, num2] : nums) { // notice that we add a '&' and now its the reference 
 	num1++;
 	num2++;
 }
 /* same as:
 for (size_t i = 0; i < num.size(); i++) {
 	// num is passed by reference and [] operator returns a reference, so we are modifying the actual number
 	nums[i].first++; 
 	nums[i].second++;
 }
 */
}
```
##### Principles

When do we use refences/const reference?

* If we’re working with a variable that takes up little space in memory (e.g. int, double), we don’t need to use a reference and can just copy the variable

* If we need to alias the variable **in order to modify the original**, use references

* If we don’t need to modify the variable, but **it’s a big variable** (e.g. std::vector, std::string), we can use **const references** so that we can **save space and time**

  ```c++
  ostream& operator<<(ostream& os, const Student& s) { // student may be very big(in memory), so we pass it by const reference to avoid copy
  	os << s.ID << ' ' << s.name << ' ' << s.major << "\n";
  	return os;
  }
  ```

### left-value & right-value

> **We can only create references to variables! Not r-value!**

##### Difference

|l-values|r-values|
|--------|--------|
|l-values can appear on the **left or right** of an =  |r-values can **ONLY appear on the right** of an =|
|variable x is a l-value  |3 is an r-value|
|l-values have names |r-values don’t have names|
|l-values are not temporary(life time: scope) |r-values are temporary(life time: one line)|
|```int x = 3; int y = x; ``` |```int x = 3; int y = x; ```|
|we can only create reference to a variable<br>(since it has an address) |reference to a r-value will cause compile error.  <br>```int& thisWontWork = 5; // This doesn't work!```|
|So it can be passed by reference as parameter or return value  |Cannot pass in an r-value by reference because they’re temporary|

##### code demo

```c++
void shift(vector<std::pair<int, int>>& nums) {
	for (auto& [num1, num2]: nums) {
	num1++;
	num2++;
	}
}
shift({{1, 1}, {2, 2}}); // compile error. It is an r-value, it can’t be referenced

auto my_nums = {{1, 1}};
shift(my_nums);// correct
```
### keyword `const`
> *A qualifier for objects that declares they cannot be modified*
>
> https://en.cppreference.com/w/cpp/language/cv

Example: 
```c++
#include <iostream>
#include <vector>
int main()
{
 std::vector<int> vec{ 1, 2, 3 }; /// a normal vector
 const std::vector<int> const_vec{ 1, 2, 3 }; /// a const vector
 std::vector<int>& ref_vec{ vec }; /// a reference to 'vec'
 const std::vector<int>& const_ref{ vec }; /// a const reference
    
 vec.push_back(3); /// this is ok!
 const_vec.push_back(3); /// no, this is const!
 ref_vec.push_back(3); /// this is ok, just a reference!
 const_ref.push_back(3); /// this is const, compiler error!
 return 0;
}
```
* **We can’t declare non-const reference to const variable!**  

```c++
#include <iostream>
#include <vector>
int main()
{
 const std::vector<int> const_vec{ 1, 2, 3 }; // a const vector
    
 std::vector<int>& bad_ref{ const_vec }; // BAD - can't declare non-const ref to const variable
 const std::vector<int>& good_ref{ const_vec }; // Good!
 std::vector<int>& ref = c_ref; // also BAD, it should always be const since the source variable is a const.
 return 0;
}
```
##### Tricky: `const` and `auto` and `&`  

* `auto`, `const auto`, `auto&`, `const auto&`

```c++
std::vector<int> vec{1, 2, 3};
const std::vector<int> c_vec{7, 8};

// Here we are making copy
auto copy_v = vec; 
const auto c_copy_v = vec;
auto copy_cv = c_vec;
const auto c_copy_cv = c_vec; 
// for copy, since it won't affect the original, it doesn't matter whether we state the copy is const or not

// Here we are making reference
auto& ref_v = vec;         
const auto& c_ref_v = vec;
auto& ref_cv = c_vec; // this will be invalid!         
const auto& c_ref_cv = c_vec;
// for ref, since we will affect the original, we should keep the const consistency.
```

### Compiling C++ program

* C++ is a compiled language
* There are computer programs called compilers
* A few popular compilers include clang and g++
* Here is how to compile a program using g++ (on Linux) 
  * details  page 104
  * g++ -std=c++20 main.cpp -o main

###  What's more

##### what is `size_t`?

> https://www.embedded.com/why-size_t-matters/  
> When you see an object declared as a size_t , you immediately know it represents a size in bytes or an index, rather than an error code or a general arithmetic value.  

##### `*` and `&` for variables and types

* for variables:
  * `*` means **dereference**
    * `int* a; *a = 100;`
  * `&` means **get the address of this variable**
    * `int* a; int b = 3; a = &b;`
* for types:
  * `*` means **a pointer points to a address that stores this type**
    * `std::Vector<std::string*>* vp;`
  * `&` means **a reference**
    * `int a = 3; int& b = a`
    * `T& MyContainer::at(size_t index);` 返回一个引用
