# Lec03 Initialization & References
> 2025/1/6

### Initialization
> How we provide initial values to variables  

e.g. Multiple ways to initialize a pair...  
```
std::pair<int, string> numSuffix1 = {1,"st"}; // first way
std::pair<int, string> numSuffix2; // second
numSuffix2.first = 2;
numSuffix2.second = "nd";
std::pair<int, string> numSuffix2 = std::make_pair(3, "rd"); // third
```  

**Uniform initialization**:  
curly bracket initialization. Available for all types, immediate initialization on declaration!

> https://www.onlinegdb.com/8uxNBkJBx

```
std::vector<int> vec{1,3,5};
std::pair<int, string> numSuffix1{1,"st"};
Student s{"Sarah", "CA", 21};
```  
TLDR: use uniform initialization to initialize every field of your non-primitive typed variables - but be careful not to use vec(n, k)! 

### Use of `auto`
> Keyword used in lieu of type when declaring a variable, tells the compiler to deduce the type.  

e.g. Quadratic  
```
int main() {
	int a, b, c;
	std::cin >> a >> b >> c;
	std::pair<bool, std::pair<double, double>> result = 
	quadratic(a, b, c);
	bool found = result.first;
	if (found) {
		std::pair<double, double> solutions = result.second;
		std::cout << solutions.first << solutions.second << endl;
	} else {
		std::cout << “No solutions found!” << endl;
	}
}
```  
using auto we can make the code easier.
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

### Structured Binding
> Structured binding lets you initialize directly from the contents of a struct.  

Before:  
```
auto p = std::make_pair(“s”, 5);
string a = p.first;
int b = p.second;
```  
After:
```
auto p = 
std::make_pair(“s”, 5);
auto [a, b] = p;
// a is string, b is int
// auto [a, b] = std::make_pair(...);
```
This works for regular structs, too.  Also, no nested structured binding.  
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

### `std::vector<T>`
```
std::vector<int> v;
std::vector<int> v(n, k);
v.push_back(k);
v[i] = k;
int k = v[i];
v.empty();
v.size();
v.clear();
```  

### References
> An alias (别名, another name) for a named variable

References to variables:
```
vector<int> original{1, 2};
vector<int> copy = original; // '=' is overloaded so it will actually copy and create a new vector
vector<int>& ref = original; // using & we got ref as a reference to original, they have the same address
original.push_back(3);
copy.push_back(4);
ref.push_back(5);
cout << original << endl; // {1, 2, 3, 5}
cout << copy << endl;     // {1, 2, 4}
cout << ref << endl;      // {1, 2, 3, 5}
```  
Here “=” automatically makes a copy! If we don't want it we must use & to avoid this.
It's all about using `&` to create a alias.

code 01:  
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

code 02:  
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

### left value & right value

**We can only create references to variables! Not rvalue!**

### `size_t`
> https://www.embedded.com/why-size_t-matters/  
> When you see an object declared as a size_t , you immediately know it represents a size in bytes or an index, rather than an error code or a general arithmetic value.  

