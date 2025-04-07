# Lec 03 Initialization & References & Const

### Initialization & Uniform initialization
> How we provide initial values to variables  

e.g. Multiple ways to initialize a pair...  
```
std::pair<int, string> numSuffix1 = {1,"st"}; // first way
std::pair<int, string> numSuffix2; // second
numSuffix2.first = 2;
numSuffix2.second = "nd";
std::pair<int, string> numSuffix2 = std::make_pair(3, "rd"); // third
```

##### **Uniform initialization**:  
Curly bracket initialization `{}`. Available for **all types**, immediate initialization on declaration!

> https://www.onlinegdb.com/8uxNBkJBx

```.cpp file
std::vector<int> vec{1,3,5};
std::pair<int, string> numSuffix1{1,"st"};
Student s{"Sarah", "CA", 21};
```
TLDR: use uniform initialization to initialize every field of your non-primitive typed variables - but be careful not to use vec(n, k)! 

##### Use of `auto`

> Keyword used in lieu of type when declaring a variable, tells the compiler to deduce the type.  

e.g. Quadratic  
```
int main() {
	int a, b, c;
	std::cin >> a >> b >> c;
	std::pair<bool, std::pair<double, double>> result = quadratic(a, b, c);
	bool found = result.first;
	if (found) {
		std::pair<double, double> solutions = result.second;
		std::cout << solutions.first << solutions.second << endl;
	} else {
		std::cout << “No solutions found!” << endl;
	}
}
```

Using auto we can make the code easier.
```
int main() {
   int a, b, c;
   std::cin >> a >> b >> c;
   auto result = quadratic(a, b, c); // using auto
   bool found = result.first;
   if (found) {
      auto solutions = result.second; // using auto
      std::cout << solutions.first << solutions.second << endl;
   } else {
      std::cout << “No solutions found!” << endl;
   }
 }
```

We can use auto to make our work lighter since we know what are we doing.  
Meanwhile, do not overuse `auto`  
```
int main() {
   auto a, b, c; // compiler error!
   std::cin >> a >> b >> c;
   ...
```
We should use it to reduce long type name while it doesn't make the code less straightforward.

Cool.  

##### Structured Binding

> Structured binding lets you initialize directly from the contents of a struct.  

Before:  
```
auto p = std::make_pair(“s”, 5);
string a = p.first;
int b = p.second;
```
After:  
```
auto p = std::make_pair(“s”, 5);
auto [a, b] = p;
// a is string, b is int
// auto [a, b] = std::make_pair(...);
```
This works for regular structs, too.  What's more, **no** nested structured binding.  

Here is the code above using structured binding:  
```
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

### References
> An alias (别名, another name) for a named variable

References to variables:
```
vector<int> original{1, 2};
vector<int> copy = original; // '=' is overloaded so it will actually copy and create a new vector, copy and original points to different address
vector<int>& ref = original; // using & we got ref as a reference to original, they have the same address
original.push_back(3);
copy.push_back(4);
ref.push_back(5);
std::cout << original << std::endl; // {1, 2, 3, 5}
std::cout << copy << std::endl;     // {1, 2, 4}
std::cout << ref << std::endl;      // {1, 2, 3, 5}
```
* Here **“=”** automatically makes a copy because **operator overloading**! If we don't want it we must use & to avoid this.
  It's all about using `&` to create a alias
* We can declare a function parameter be a reference so that it won't make a copy when passing parameter.
* We can also return a reference which won't make a copy

##### code 01

```
void shift(vector<std::pair<int, int>>& nums) {
 for (size_t i = 0; i < nums.size(); ++i) {
	 auto [num1, num2] = nums[i]; // This creates a copy of the nums[i]
	 num1++; 
	 num2++; // this is updating the copy
 }
}
```
code 01 fixed:  
```
void shift(vector<std::pair<int, int>>& nums) {
 for (size_t i = 0; i < nums.size(); ++i) {
 	auto& [num1, num2] = nums[i]; // notice that we add a '&' and now its the reference 
 	num1++;
 	num2++;
 }
}
```

##### code 02: using new syntax `for(auto element: container)`  

```
void shift(vector<std::pair<int, int>>& nums) {
 for (auto [num1, num2]: nums) { // same as the 01, its just the copy
 	num1++;
 	num2++;
 }
}
```
code 02 fixed:
```
void shift(vector<std::pair<int, int>>& nums) {
 for (auto& [num1, num2]: nums) { // notice that we add a '&' and now its the reference 
	 num1++;
	 num2++;
 }
}
```

##### left value & right value

> **We can only create references to variables! Not r-value!**

|l-values|r-values|
|--------|--------|
|l-values can appear on the **left or right** of an =  |r-values can **ONLY appear on the right** of an =|
|variable x is a l-value  |3 is an r-value|
|l-values have names |r-values don’t have names|
|l-values are not temporary |r-values are temporary|
|```int x = 3; int y = x; ``` |```int x = 3; int y = x; ```|
|we can only create reference to a variable<br>(since it has an address) |reference to a rvalue will cause compile error.  <br>```int& thisWontWork = 5; // This doesn't work!```|
Here is another example:  

```
void shift(vector<std::pair<int, int>>& nums) {
	for (auto& [num1, num2]: nums) {
	num1++;
	num2++;
	}
}
shift({{1, 1}}); // compile error. {{1, 1}} is an rvalue, it can’t be referenced
```
fixed:  
```
void shift(vector<pair<int, int>>& nums) {
	for (auto& [num1, num2]: nums) {
	num1++;
	num2++;
	}
}
auto my_nums = {{1, 1}};
shift(my_nums);// correct
```

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
  * `&` means **reference**
    * `int a = 3; int& b = a`
    * `T& MyContainer::at(size_t index);` 返回一个引用

### keyword `const`
> `const` indicates that a variable can not be modified.

Here is a example.  
```
std::vector<int> vec{1, 2, 3}; // a regular variable
const std::vector<int> c_vec{7, 8};  // a const variable
std::vector<int>& ref = vec;         // a regular reference
const std::vector<int>& c_ref = vec;  // a const reference
vec.push_back(3);    // OKAY
c_vec.push_back(3);  // BAD - const
ref.push_back(3);   // OKAY
c_ref.push_back(3); // BAD - const
```
* **We can’t declare non-const reference to const variable!**  

```
const std::vector<int> c_vec{7, 8}; // a const variable
std::vector<int>& bad_ref = c_vec; // BAD - can't declare non-const ref to const vector
```
fixed:  
```
const std::vector<int> c_vec{7, 8}; // a const variable
const std::vector<int>& c_ref = c_vec; // fixed, const ref

std::vector<int>& ref = c_ref; // also BAD, it should always be const since the source variable is a const.
```
##### `const` and `auto`  

```
std::vector<int> vec{1, 2, 3};
const std::vector<int> c_vec{7, 8};
std::vector<int>& ref = vec;
const std::vector<int>& c_ref = vec;
auto copy = c_ref;         // a non-const copy
const auto copy = c_ref;   // a const copy
auto& a_ref = ref;         // a non-const reference
const auto& c_aref = ref;  // a const reference
```

- **`auto` 的类型推导规则**：

  - 对于 `auto var = expr`，会忽略 `expr` 的顶层 `const` 和引用。
  - 对于 `auto& var = expr`，会保留 `expr` 的 `const` 属性。

  ```
  const auto& cref = non_const_obj;  // 合法：承诺不修改对象
  auto& ref = const_obj;             // ❌ 非法：非常量引用不能绑定到常量对象
  
  // ❌ 错误：非常量引用绑定到常量对象
  auto& invalid_ref = c_vec;  // 错误：无法从 'const vector<int>' 推导出 'vector<int>&'
  
  // ❌ 错误：试图修改常量引用绑定的对象
  ref_c.push_back(4);         // 错误：'const vector<int>' 没有名为 'push_back' 的非 const 成员
  ```

We can return a reference as well.  

> https://www.onlinegdb.com/o8luVxGpf

```
// Note that the parameter must be a non-const reference to return
// a non-const reference to one of its elements!
int& front(std::vector<int>& vec) {
	// assuming vec.size() > 0
	return vec[0];
}


// it can also return a const reference
const int& c_front(std::vector<int>& vec) {
	// assuming vec.size() > 0
    return vec[0];
}

int main() {
    std::vector<int> numbers{1, 2, 3};
    front(numbers) = 4; // vec = {4, 2, 3}
    return 0;
}
```

**Remember: C++, by default, makes copies when we do `=` variable assignment! We need to use & if we need references instead.**  

Most of the time, `=` will **simply copy the right side's variable's value in memory to the left side,** so it will just be copy the data in the variable address, which are likely to be a address value points to someplace.   
For some classes that overloads '=' operator, it will do something else and the result is defined by the overloaded function.  

**When do we use refences/const reference?**

* If we’re working with a variable that takes up little space in memory (e.g. int, double), we don’t need to use a reference and can just copy the variable
* If we need to alias the variable to modify it, we can use references
* If we don’t need to modify the variable, but it’s a big variable (e.g. std::vector, std::string), we can use const references so that we can save space and time
