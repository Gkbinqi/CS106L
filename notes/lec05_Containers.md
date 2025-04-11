# What the heck is the STL? What are templates?

STL: Standard Template Library

* Containers(lec 05)
* Iterators(lec 06)
* Functors
* Algorithms

![image-20250411094246084](C:\Users\47949\Desktop\CS106L\notes\pic\lec05_containers.png)

### Sequence Containers

* store a linear sequence of elements

##### `std::vector<T>`

```c++
std::vector<int> vec { 1, 2, 3, 4 };
vec.push_back(5);
vec.push_back(6);
vec[1] = 20;
for(const auto& elem: vec) {
	std::cout<<elem<<" ";
}
```

* Tip1: Use **range-based for** when possible. 
  * Applies for all **iterate-able** containers, not just `std::vector`


* Tip2: Use `const auto&` when possible

  * Save space and time, no copy

    ```c++
    std::vector `<MassiveType>`vec{ ... };
    
    for(auto elem : vec) // copy happens here taking a lot of space and time
    for(const auto& elem : v) // const reference anyway!
    ```


* Warning:

operator `[]` does not perform bounds checking

```c++
std::vector<int> vec{5, 6}; // {5, 6}
vec[1] = 3; // {5, 3}
vec[2] = 4; // undefined behavior
vec.at(2) = 4; // Runtime error
```

##### `std::deque`

* A deque (“deck”) is a double-ended queue
* Allows efficient insertion/removal at either end
  * 可以`push_front` & `pop_front`

* 实现: 申请数组的数组

### Associative Containers

* Associative containers organize elements by unique key

##### `std::map`

* In map, each **K is unique** while **value is arbitrary**
* `std::map<K, V>` stores a collection of `std::pair<const K, V>`

###### map as a collection of pair

We can iterate through the key-value pairs using a range based for loop

```c++
for (auto& kv : map) {
  // kv is a std::pair<const std::string, int>
  std::string key = kv.first;
  int value = kv.second;
}
// or Structured bindings 
for (const auto& [key, value] : map) {
	// key has type const std::string&
	// value has type const int&
}
```

###### map implementation 

* Map is implemented as a **red-black tree**
  * So, `std::map<K, V>` requires `K` to have an operator `<`

```c++
// OKAY - int has operator<
std::map<int, int> map1; 

// ERROR - std::ifstream has no operator<
std::map<std::ifstream, int> map2;
```

##### `std::set`

* `std::set` stores a collection of **unique** items, a mathematical set(集合).
  * like an `std::map` without values

###### `std::set` implementation

* Also a red-black tree
  * So, it also requires the element have `<` operator 

##### `std::unordered_map` & `std::unordered_set`

* These two class are essentially a **hash map/set**
  * Since using hash, it will be super fast if maintained well.
* They have the same interface as `std::map`/`std::set`



##### hashable K

`std::unordered_map<K, V>` requires K to be hashable

```c++
// OKAY - int is hashable
std::unordered_map<int, int> map1; 
// ERROR - std::ifstream is not hashable
std::unordered_map<std::ifstream, int> map2; 
```

* Most basic types (int, double, string) are hashable by default
* hash table details in PPT

### Summary

![](C:\Users\47949\Desktop\CS106L\notes\pic\lec05_Summary.png)
