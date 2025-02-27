# lec 08 Template Classes

### Template Classes

> How can we generalize across different types? 
>
> `std::vector<T>` How does `T` works?

#####  Recap

* `this`: a **pointer** to the current class instance
* `->`: pointer dereference

##### Old Template Example

Here is a toy example:

```.h file
#define GENERATE_VECTOR(MY_TYPE) 
class MY_TYPE##Vector { 
public: 
	MY_TYPE& at(size_t index); 
	void push_back(const MY_TYPE& elem); 
private: 
	MY_TYPE* elems; 
	size_t logical_size; 
	size_t array_size; 
}; 
```

* `#define ... `: **Preprocessor Macro**. Runs before compiler

However, it has backwards:

* Clunky syntax
* Hard to type check
* What if you forget to call macro? Or call it more than once?

##### Template

> Key Idea: Templates automate code generation

Here is a example(Not a faultless code, just for demostration)

```.h file
template <typename T> // Template Declaration
// Vector is a template that takes in the name of a type T
class Vector {
public:
	T& at(size_t index);
	void push_back(const T& elem);
private:
	T* elems;
};
```

* `T` gets replaced when Vector is **instantiated(实例化)**
* **Template Instantiation**: Code for a specific type is generated on-demand, when you use it 

| Template                                | Type                                               |
| --------------------------------------- | -------------------------------------------------- |
| `template<typename T> class Vector`     | `Vector<std::string>`                              |
| This is a template. It’s **not a type** | This is a type. A.K.A a **template instantiation** |

```
void foo(std::vector<int> v);
int main() {
	std::vector<double> v;
	foo(v); // error: No suitable user-defined conversion from "std::vector<double>" to "std::vector<int>" exists
}
```

* Different instantiations of the same template are different (runtime and compile-time) types.

Fun facts: `typename` are interchangeable

```
template<typename T, std::size_t N> // here std::size_t
struct std::array { /* ... */ };
// An array of exactly 5 strings
std::array<std::string, 5> arr;
```

##### Template in Details

* Must copy the template declaration `template <…>` syntax in .cpp file

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

* For template classes,  .h file must include .cpp file at bottom of file

  * For non-template classes, the .cpp file includes the .h file

  * For template classes, the .h file includes the .cpp file

  * ```.h file
    // Vector.h
    template <typename T>
    class Vector {
    public:
    	T& at(size_t i);
    };
    #include "Vector.cpp" // include .cpp file at the end of the .h file
    ```

  * ```.cpp file
    // Vector.cpp
    template <typename T>
    T& Vector<T>::at(size_t i) {
    	// Implementation...
    }
    ```

  * Why?

    * Template .h must include .cpp due to the way template code generation is implemented in the compiler (and linker)
    * Don’t worry too much about the why (unless you’re curious!)

* `typename` is the same as `class`

  * Just know that `typename` and `class` are the same semantically here.

### Code Demo

> Implementing a template class 





### `const` Correctness

> Unlocking the power of `const`