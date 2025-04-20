# Iterator 2025/2/25

`for (const auto& elem : container)`

* How does this work?
* The Standard Template Library (STL)
  * Containers
  * Iterators(We are here now)
  * Functors
  * Algorithms

### Iterator Basics 

When we iterating a container, we need something to **track where we are** in a container… 

* sort of like an index

* **Containers** and **iterators** *work together* to allow iteration
* Here **Container** provides the `c.begin()` and `c.end()` interface

  * `end()` never points to an element!
    * Instead, it points one past the end of the container
    * dereference a iterator points to `end()` will cause undefined behavior

  * If `c` is empty, then `begin()` and `end()` are equal!

![image-20250225092856645](C:\Users\47949\Desktop\CS106L\notes\pic\lec06_container interface.png)

All iterators provide these operation:

```c++
// Copy construction 复制一个c.begin() 到 it 来, 注意是**复制**
auto it = c.begin();
// Increment iterator forward 开始遍历 用++it转向下一个元素
++it;
// Dereference iterator -- undefined if it == end() 即此时解引用可以得到此处的element
auto elem = *it;
// Equality: are we in the same spot? 当it == c.end(), 到达容器终点, 此时it不指向实际elem
if (it == c.end()) ...
```

Now we can build our own **range-based for loop**

```c++
std::vector<int> c{1,2,3,4,5};

for (const auto& elem : c) {
	somecode...;
}
// is equal to
for (auto it = c.begin(); it != c.end(); ++it) {
	const auto& elem = *it; // dereference
	somecode...;
}
```

What are the type of iterator?

* Using `auto` avoids spelling out long iterator types

```c++
std::map<int, int> m { {1, 2}, {3, 4}, {5, 6}};
auto it = m.begin();
auto elem = *it; // {1, 2}
// is equal to:
std::map<int, int> m { {1, 2}, {3, 4}, {5, 6}};
std::map<int, int>::iterator it = m.begin();
std::pair<int, int> elem = *it;
```

### Iterator Types 

* All iterators provide four operations

  ```c++
  auto it = c.begin(); // copy iterator
  ++it; // move to next one
  *it; // deref
  it == c.end() // end check
  ```

* But most provide even more

  ```c++
  --it; // Move backwards 
  *it = elem; // Modify
  it += n; // Randomly access 
  it1 < it2 // Is before?
  ```

##### Input Iterator

* Most basic kind of iterator
* Allows us to **read** elements
  * `auto elem = *it;`


* when we want to access a filed(member) of a struct, using operator `->`

```c++
struct Bibble {
	int zarf;
};
std::vector<Bibble> v {...};
auto it = v.begin();
int m = (*it).zarf;
int m = it->zarf; 
```

##### Output Iterator

* Allows us to **write** elements
  * `*it = elem;`


##### Forward Iterator

* An input iterator that allows us to make multiple passes 
  * All **STL** container iterators fall here


```c++
// Multi-pass guarantee
it1 == it2; // if it is true
// then
++it1 == ++it2 // true
```

##### Bidirectional Iterators(双向)

* Allows us to move forwards and backwards
  * `std:map`, `std::set`


```c++
auto it = m.end(); // Get last element
--it; // we can move back
auto& elem = *it; // if the m is not empty, this works
```

##### Random Access Iterators

* Allows us to quickly skip forward and backward
  * `std::vector`, `std::deque`

* Be careful not to go out of bounds!

```c++
auto it2 = it + 5; // 5 ahead
auto it3 = it2 - 2; // 2 back
// Get 3rd element
auto& second = *(it + 2);
auto& second = it[2];
```

### Bouns

##### Difference: ++i & i++

* Conclusion first: `++i` is better than `i++`, **most of the time we should use `++i`.**
  * using `++i` never lose anything while sometimes we gain something.

* reason: `++it` avoids making an **unnecessary copy**

```c++
// Prefix ++it
// Increments it and returns a **reference** to same object
Iterator& operator++(int);

// Postfix it++
// Increments it and returns **a copy of the old value**
Iterator operator++();

// Remember: an iterator can be fully-fledged object, it might be really huge and confusing, 
// so it’s often more expensive to make a copy than, say, an int
```

##### Why **Iterator Types** matter?

some algorithms require a certain iterator type!

```c++
std::vector<int> vec{1,5,3,4};
std::sort(vec.begin(), vec.end());
// ok. begin/end are random access

std::unordered_set<int> set {1,5,3,4};
std::sort(set.begin(), set.end());
// ×. begin/end are bidirectional
```

##### Why have multiple iterator types?

* Goal: provide a **uniform abstraction** over all containers
* Caveat(警告): the way that a container is implemented affects how you iterate through it
  * Skipping ahead 5 steps (random access) is a lot easier/faster when you have a sequence container (`std::vector`, `std::deque`) than associative (`std::map`, `std::set`)
  * C++ generally avoids providing you with slow methods by design, so that’s why you can’t do random access on a map::iterator

![image-20250225100438458](C:\Users\47949\Desktop\CS106L\notes\pic\lec06_STL Iterator Types.png)

##### Pointers and Memory 

* An ***iterator*** points to a ***container element***
* A ***pointer*** points to ***any object***
* Remember, they two are similar but **NOT THE SAME THING**!

##### Memory Basics

* Every variable lives somewhere in memory
* All the places something could live form the address space

![image-20250225100723321](C:\Users\47949\Desktop\CS106L\notes\pic\lec06_Memory.png)![image-20250225100805457](C:\Users\47949\Desktop\CS106L\notes\pic\lec06_address example.png)

##### Pointer

* **A pointer is the address of a variable**
  * Essentially, a pointer is just a number usually presented using hex.(0x...)


```c++
int x = 106;
int* px = &x; // int* means px is a pointer to an int, & is the "address of" operator

std::cout << x << std::endl; // 106
std::cout << *px << std::endl; // 106
std::cout << px << std::endl; // 0x50527c
```

![image-20250225101124243](C:\Users\47949\AppData\Roaming\Typora\typora-user-images\image-20250225101124243.png)



* Iterators have a **similar interface** to pointers
* **iterator** is a **type alias**(类型别名)
  * Remember: `using` makes a **type alias**


```c++
template <typename T>
class vector {
	using iterator = /* some iterator type */;;
	// Implementation details...
};
// actually it will be:
template <typename T>
class vector {
	using iterator = T*; // wow
	// Implementation details...
};
```

* `T*` is the backing type for `vector::iterator`

> In the real STL implementation, the actual type is not T*. But for all intents and purposes, you can think of it this way.

##### At the end...

So, how do we implement other iterators?
* for example, a `std::map::iterator`

```c++
template <typename K, typename V>
class map {
	using iterator = ???????;
	// Implementation details...
};
```

We’ll learn about them next time in lecture: **Classes**