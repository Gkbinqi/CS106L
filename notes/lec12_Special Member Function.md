# Special Member Functions (SMFs)

```c++
/*
These functions are generated only when they are called (and before any are explicitly defined by you):
We don’t have to write out any of these! They all have default versions that are generated automatically!(However, sometimes the default version doesn't work)
*/

● Default constructor: T()
● Destructor: ~T()

● Copy constructor: T(const T&)
// It's a **constructor**
Widget widgetOne;
Widget widgetTwo(widgetOne);
Widget widgetThree = widgetOne;

● Copy assignment operator: T& operator=(const T&)
// Assigns an already existing object to another
// Note that here both objects **are constructed** before the use of the = operator
// So, this will make things different when implementing constructor & assigner
Widget widgetOne;
Widget widgetTwo;
widgetOne = widgetTwo;

● Move constructor: T(T&&)
● Move assignment operator: T& operator=(T&&)
// Move operation, mentioned later.
// again, difference between implementing constructor & assigner
```

* A **constructor** is called every time when a new instance of the class is created, and the destructor is called when it **goes out of scope**

### Copy constructor & Copy assignment

##### Copy constructor

* Initializer Lists

  ```c++
  template <typename T>
  Vector<T>::Vector() : _size(0), _capacity(4), _data(new T[_capacity]) { }
  ```

  * It’s **quicker and more efficient** to directly construct member variables with intended values

    * There are two steps happening here: the **first** is that `_size`, `_capacity`, and `_data` may have been default initialized

      ```.cpp file
      template <typename T>
      Vector<T>::Vector()
      {
       _size = 0; // we may do two things here: default initialize, and then assign a new value.
       _capacity = 4; // if the member type here is a customer type which will do memory management, we actually do some extra work.
       _data = new T[_capacity];
      }
      ```

      ⭐Member initialization happens **before** constructor body runs.

    * And then, we reassign the value to these member variables using `=`, which will be inefficient.

    * Here, we can use initializer lists to declare and initialize them with desired values at once!

      ```c++
      template <typename T>
      Vector<T>::Vector() : _size(0), _capacity(4), _data(new T[_capacity]) { }
      ```

    * Now the member variables are declared and initialized at once with more efficiency, cool.

  * Can be used for any constructor, even non-default ones with parameters!

  * What if the variable is a non-assignable type?

    ```c++
    template <typename T>
    class MyClass {
     const int _constant;
     int& _reference;
    public:
     // Only way to initialize const and reference members
     MyClass(int value, int& ref) : _constant(value), _reference(ref) { }
    };
    ```

    * This code only works with initializer lists, WHY? page 33 - 35

      * In C++, **`const` members** and **reference members** **must** be initialized when the object is constructed — and they **cannot be assigned inside the constructor body**.
        * `const` members must be initialized **exactly once**, **at construction**.
        * References must be **bound to something** at construction, and can't be rebound.
      * Notice that if we use assign in the scope, two steps happening here
        * first, we default initialize the member variables, which will also default initialize the ref/const variable
        * second, we try to assign the ref/const variable
          * for the constant, we are trying to modify a const variable, which will cause error
          * for the reference, since reference can't be rebound, we are actually reassign the **value** of this reference rather than rebound it to something else. However, by default initialization, which value are reference refer to?
            * we are assign value to the abyss.

      * TLDR version by gpt

        * Initializer lists are **required** for:

          - `const` members
          - `reference` members
          - Base classes (if you're doing inheritance)
          - Members of classes without default constructors

          They run **before the constructor body**, which is when these special kinds of members must be set.

##### Copy assignment:

Here we need to notice that since the two objects are exist when doing copy assignment, there may be these problem:

* If the class need to handle memory management, What if `this` has some memory when copying another object?
* What if we do something like `a = a`?

Here when implementing copy assignment overloading, we need to do more check and we can't use list initializer since it's not a constructor(It really confuse me at the beginning)

```.cpp file
// we may do someting like:
// assuming MyClass is managing a chunk of memory pointed using _data
class Myclass {
private: 
    int* _data; // assume we are sure that _data will points to an array 
public:
    MyClass& operator=(const MyClass& other);
}

MyClass& MyClass::operator=(const MyClass& other) {
  if (this == &other) return *this; // check one, whether we are try to do a=a. If so, do nothing
  if (_data != nullptr) delete[] _data; // check two, whether `this` is managing its memory. If so, delete it

  this->_data = other._data;
  return *this;
}
```





// mark, 2025/4/7 refractor

### Why overloads SMFs?

* This is member-wise copying, It's won't work well with manually allocated memory like pointers.
* We want to create a copy that does more than just copies the member variables
* We will want to make a **deep copy**
  * Deep copy: an object that is a complete, independent copy of the original
* So we'd want to override it.

##### default & delete

delete:

* We can delete special member functions, here to prevent copy

  * Setting a special member function to delete removes its functionality!

  * ```c++
    class IntVec{
    public:
    	IntVec();
    	IntVec(const IntVec& other);
    	~IntVec();
    	// ...
    	IntVec(const IntVec& rhs) = delete;
    	IntVec& operator=(const IntVec& rhs) = delete; // Now copying isn’t a possible operation!
    private:
    	...
    }
    ```

* Why?

  * We can selectively allow functionality of special member functions!
  * This has lots of uses – what if we only want one copy of an instance to be allowed?
  * This is how classes like` std::unique_ptr` work

default:

* 

##### Rules

* Rules of Zero: If the default SMFs work, don’t define your own!

  * We should only define new ones when the default ones generated by the compiler won't work
    * This usually happens when we work with dynamically allocated memory, like pointers to things on the heap.

  * If you don’t need a constructor or a destructor or copy assignment etc. Then simply don’t use it! 

* If your class relies on objects/classes that already have these SMFs implemented, then there’s no need to reimplement this logic!

* If you need a custom destructor, then you also probably need to define a copy constructor and a copy assignment operator for your class 

  * If you use a destructor, that often means that you are manually dealing with dynamic memory allocation/are generally just handling your own memory. 
  * Here, The compiler will not be able to automatically generate these for you, because of the manual memory management.