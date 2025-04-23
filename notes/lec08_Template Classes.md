# Lec 08: Template Classes & Const Correctness

### Template Classes

#####  Recap

* `this`: a **pointer** to the current class instance
* `->`: pointer dereference

##### Template

Here is a example(Not a faultless code, just for demonstration)

```.h file
template <typename T> // Template Declaration
// Vector is a template that takes in the name of a type T
class Vector {
public:
	T& at(size_t index);
	void push_back(const T& elem);
private:
	T* elems; // T gets replaced when Vector is instantiated
};
```

* `T` gets replaced when Vector is **instantiated(实例化)**
* **Template Instantiation**: Code for a specific type is generated on-demand, when you use it 

| Template                                | Type                                               |
| --------------------------------------- | -------------------------------------------------- |
| `template<typename T> class Vector`     | `Vector<std::string>`                              |
| This is a template. It’s **not a type** | This is a type. A.K.A a **template instantiation** |

```.cpp file
void foo(std::vector<int> v);
int main() {
	std::vector<double> v;
	foo(v); 
    // error: No suitable user-defined conversion from "std::vector<double>" to "std::vector<int>" exists
    // Vector<double> & Vector<int> two instantiations (of the same template) are completely different (runtime and compile-time) types
}
```

* Different instantiations of the same template are different (runtime and compile-time) types
* A template is like a factory
  * Takes in type, generate another class


Fun facts: `typename` are interchangeable

```.cpp file
template<typename T, std::size_t N> // here std::size_t
struct std::array { /* ... */ };
// An array of exactly 5 strings
std::array<std::string, 5> arr;
```

##### Template in Details

###### Must copy the template declaration `template <…>` syntax in .cpp file

* Attention, **FOR EVERY MEMBER METHOD IN THE .cpp FILE!**

* ```.cpp file
  // Vector.cpp
  template <typename T>
  Vector<T>::Vector()
  {
    _size = 0;
    _capacity = 4;
    _data = new T[_capacity];
  }
  
  template <typename T>
  Vector<T>::~Vector()
  {
    delete[] _data;
  }
  
  //...
  
  template <typename T>
  typename Vector<T>::iterator Vector<T>::begin()
  {
    return _data;
  }
  
  template <typename T>
  typename Vector<T>::iterator Vector<T>::end()
  {
    return _data + _size;
  }
  ```

###### For template classes,  .h file must include .cpp file at bottom of file

* For non-template classes, the .cpp file includes the .h file

* For template classes, the .h file includes the .cpp file

  ```.h file
  // Vector.h
  template <typename T>
  class Vector {
  public:
  	T& at(size_t i);
  };
  #include "Vector.cpp" // include .cpp file at the end of the .h file
  ```

  ```.cpp file
  // Vector.cpp
  template <typename T>
  T& Vector<T>::at(size_t i) {
  	// Implementation...
  }
  ```

* Why?

  * Template .h must include .cpp due to the way template code generation is implemented in the compiler (and linker)
  * Don’t worry too much about the why

* `typename` is the same as `class`
  * Just know that `typename` and `class` are the same semantically here.

### Code Demo

More details in `./code/lec08_Vector.h`, here we implement a vector by ourselves.

### `const` Correctness

##### const interface

* Inside a `const` method, this has type `const Vector*`

  * >lec08_Vector.cpp:66:19: error: assignment of member '_capacity' in read-only object
    >   66 |   this->_capacity = 0;
    >    	|   ~~~~~~~~~~~~~~~~^~~

* The `const` interface

  * The `const` interface are the functions that are `const` in an object
    * Objects marked as `const` can **only** make use of the `const` interface
    * Meanwhile, non-const object can use `const` interface since `const` interface is considered **safe**.
    * ![image-20250228092656360](C:\Users\47949\AppData\Roaming\Typora\typora-user-images\image-20250228092656360.png)

  * 如果类中同时定义了 `const` 和非 `const` 版本的同名函数，**非 `const` 对象会优先调用非 `const` 版本**，而 `const` 对象只能调用 `const` 版本

* Now back to our Vector class

  ```c++
  template<class T>
  class Vector {
  public:
  	size_t size() const;
  	bool empty() const;
  	T& operator[] (size_t index);
  	T& at(size_t index) const;
  	void push_back(const T& elem);
  };
  ```

  ```c++
  // in .cpp file we declare const like that
  template <class T>
  size_t Vector<T>::size() const {
      // in a const method this has a type `const Vector<T>*`
  	return logical_size;
  }
  ```
  
  We have add `const` interface to these methods, but there are still more problems.
  
  * `const` consumers can modify!

    * Since we return a non-const reference, we can assign to it!

      ```.cpp file
      T& at(size_t index) const;
      void oops(const Vector<int>& v) {
      	v.at(0) = 42;//Remember, since v is const, we shouldn’t be able to modify it
      }
      ```
  
  * How about return a const reference `const T& at(size_t index) const;`

    * non-const consumers can’t modify!
  
      ```c++
      const T& at(size_t index) const;
      void ooh(Vector<int>& v) {
      	v.at(0) = 42;// now we can't update elements sinze `at` return a const T& 
      }
      ```
  
      ```
      lec08_main.cpp:14:17: error: assignment of read-only location '(& v)->Vector<int>::at(i)'
         14 |         v.at(i) = v.at(0);
            |         ~~~~~~~~^~~~~~~~~
      ```

We are in dilemma, how to solve this?

##### Solution: `const` overloading

Define two version of method, one gets called for `const` instance, another gets called for non-`const` instance.

```.h file
template<class T>
class Vector {
public:
	const T& at(size_t index) const;
	T& at(size_t index);
};
```

```cpp
template <class T>
const T& Vector<T>::at(size_t index) const {
	return elems[index];
}
template <class T>
T& Vector<T>::at(size_t index) {
	return elems[index];
}
```

It seems good now, but how about we got a  "larger" method?

```.h file
T& findElement(const T& value);
const T& findElement(const T& value) const;
```

```c++
template <typename T>
T& Vector<T>::findElement(const T& value) {
	for (size_t i = 0; i < logical_size; i++) {
		if (elems[i] == elem) return elems[i];
	}
	throw std::out_of_range("Element not found");
}

template <typename T>
const T& Vector<T>::findElement(const T& value) const {
	for (size_t i = 0; i < logical_size; i++) {
		if (elems[i] == elem) return elems[i];
	}
	throw std::out_of_range("Element not found");
}
```

This will work ,but its super redundant.

Now we will use `casting`

##### casting

* **Casting: the process of converting one type to another(There are many ways to cast in C++)**
* `const_cast` 
  * allows us to “cast away” the const-ness of a variable
  * Usage: `const_cast<target_type>(expression)` 

Now our code looks like:

```c++
template <typename T>
T& Vector<T>::findElement(const T& value) {
	for (size_t i = 0; i < logical_size; i++) {
		if (elems[i] == elem) return elems[i];
	}
	throw std::out_of_range("Element not found");
}
template <typename T>
const T& Vector<T>::findElement(const T& value) const {
	return const_cast<Vector<T>&>(*this).findElement(value); // what's that?
}
```

##### `const_cast<Vector<T>&>(*this).findElement(value);`

here, we split it into parts:

* `(*this)`: We will compute the things in the () first. Since this function is `const T& Vector<T>::findElement(const T& value) const`, it is a const interface
  * inside a const method, `this` has a type `const Vector<T>*`
  * `(*this)` means `const Vector<T>&`
* `const_cast<Vector<T>&>(*this)`
  * `(*this)` means `const Vector<T>&`, while `const_cast<Vector<T>&>` will cast a `const Vector<T>&` into `Vector<T>&`
* `const_cast<Vector<T>&>(*this).findElement(value);`
  * Now we got a `Vector<T>&`, and this instance will call non-const type `findElement` method
  * that is `T& Vector<T>::findElement(const T& value)`
* Then we get the return value of `T& Vector<T>::findElement(const T& value)`, a `T&`, then return it in `const T&` way.

##### const-cast details

When to use const_cast?

* Short answer: just about never
* **`const_cast` tells the compiler: “don’t worry I’ve got this”**
  * If you need a mutable value, just don’t add const in the first place

* Valid uses of `const_cast` are few and far between
  * All in all, a tricky, powerful but rarely used way.


##### A C++ party trick: mutable keyword

Like `const_cast`, `mutable` circumvents `const` protections. Use it carefully!

```c++
struct MutableStruct {
	int dontTouchThis;
	mutable double iCanChange;
};
const MutableStruct cm;
// cm.dontTouchThis = 42; // Not allowed, cm is const
cm.iCanChange = 3.14; // Ok, iCanChange is mutable
```

mutable example: storing debug info

```c++
struct CameraRay {
	Point origin;
	Direction direction;
	mutable Color debugColor;
}
void renderRay(const CameraRay& ray) {
ray.debugColor = Color.Yellow; // Show debug ray
/* Rendering logic goes here ... */
}
```
