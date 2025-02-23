# What the heck is the STL? What are templates?

•”The Standard Template Library”

STL: Standard TemplateLibrary

* Containers
  How do we store groups of things?
* Iterators
  How do we traverse containers?
* Functors
  How can we represent functions as objects?
* Algorithms
  How do we transform and modify containers in a generic way?

# Sequence Containers

* Sequence containers store a linear sequence of elements

### `std::vector<T>`

> `#include <vector>`

![](C:\Users\47949\Desktop\CS106L\notes\pic\lec05_Vector.png)

```
std::vector<int> vec { 1, 2, 3, 4 };
vec.push_back(5);
vec.push_back(6);
vec[1] = 20;
for (size_t i = 0; i < vec.size(); i++) {
	std::cout << vec[i] << " ";
}
```

* Tip1: Use **range-based for** when possible. Applies for all **iterable** containers, not just `std::vector`

```
for(size_ti=0; i<vec.size(); i++) {//not good
	std::cout<<vec[i] <<" ";
}
for(autoelem: vec) {//more convenient
	std::cout<<elem<<" ";
}
```

* Tip2: Use `const auto&` when possible

```
std::vector `<MassiveType>`vec{ ... };

for(auto elem : vec) // not good
for(const auto& elem : v) // good
```

* Applies for all iterablecontainers, not just std::vector
* Saves making a potentially expensive copy of each element

Warning:

operator `[]` does not perform bounds checking

```
std::vector<int> vec{5, 6}; // {5, 6}
vec[1] = 3; // {5, 3}
vec[2] = 4; // undefined behavior
vec.at(2) = 4; // Runtime error
```



# Associative Containers

> Associative containers organize elements by unique keys

### `std::map`

> `#include <map>` 
>
> stores a collection of `std::pair<const K, V>`

In map, each K is unique while value is arbitrary

![](C:\Users\47949\Desktop\CS106L\notes\pic\lec05_Map.png)

##### map as a collection of pair

We can iterate through the key-value pairs using a range based for loop

```std::map<std::string, int> map;
for (auto kv : map) {
  // kv is a std::pair<const std::string, int>
  std::string key = kv.first;
  int value = kv.second;
}
```

##### map implementation 

Map is implemented as a **red-black tree**, so `std::map<K, V>` requires `K` to have an operator `<`

```
//  OKAY - int has operator<
std::map<int, int> map1; 

//  ERROR - std::ifstream has no operator<
std::map<std::ifstream, int> map2;
```

### `std::set`
>  `#include <set>`

`std::set` stores a collection of **unique** items, a mathematical set(集合).

![](C:\Users\47949\Desktop\CS106L\notes\pic\lec05_Set.png)

`std::set` is an amoral `std::map`
`std::set` is an `std::map` without values

##### `std::set` implementation

* Also a red-black tree
  * So, it also requires the element have `<` operator 



### `std::unordered_map` & `std::unordered_set`
> #include <unordered_map> 
> #include <unordered_set>

These two class are essentially a **hash map/set**
They have the same interface as `std::map`/`std::set`

Since using hash, it will be super fast if maintained well.

##### hashable K

`std::unordered_map<K, V>` requires K to be hashable

```//  OKAY - int is hashable
// OKAY - int is hashable
std::unordered_map<int, int> map1; 
// ERROR - std::ifstream is not hashable
std::unordered_map<std::ifstream, int> map2; 
```

Most basic types (int, double, string) are hashable by default

### Summary

![](C:\Users\47949\Desktop\CS106L\notes\pic\lec05_Summary.png)

![](C:\Users\47949\Desktop\CS106L\notes\pic\lec05_more structure.png)

### Others

Assignment 1 due Friday
