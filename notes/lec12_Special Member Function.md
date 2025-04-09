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

* A **constructor** is called every time when a new instance of the class is created, and the **destructor** is called when it **goes out of scope**

### Constructor & Copy Operation

##### Constructor

* Initializer Lists

  ```c++
  template <typename T>
  Vector<T>::Vector() : _size(0), _capacity(4), _data(new T[_capacity]) { }
  ```

  * First, It’s **quicker and more efficient** to directly construct member variables with intended values

    * There are two steps happening here: the **first** is that `_size`, `_capacity`, and `_data` may have been default initialized

      ```.cpp file
      template <typename T>
      Vector<T>::Vector()
      {
       _size = 0; // we may do two things here: default initialize, and then assign a new value.
       _capacity = 4; // if the member type here is a customer type which need initialization(constrction), we will first call it's default constructor, then using copy assign.
       _data = new T[_capacity];
      }
      ```

      ⭐Member initialization happens **before** constructor body runs.

    * And then, we reassign the value to these member variables using `=`, which will be inefficient.

    * Here, we can use initializer lists to declare and initialize them with desired values at once!

      ```c++
      template <typename T>
      Vector<T>::Vector() : _size(0), _capacity(4), _data(new T[_capacity]) { }
      // my way to comprehend: it's like calling the constructor
      // just like MyClass c(some args...)
      // so we do all the things at the initialization
      ```
  
    * Now the member variables are declared and initialized at once with more efficiency, cool.
  
  * Second, Can be used for any constructor, even non-default ones with parameters!
  
  * Third, What if the variable is a non-assignable type?
  
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

##### Copy constructor & Copy assignment:



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
    size_t _size;
public:
    MyClass& operator=(const MyClass& other);
}

MyClass& MyClass::operator=(const MyClass& other) {
  if (this == &other) return *this; // check one, whether we are try to do a=a. If so, do nothing
  if (_data != nullptr) delete[] _data; // check two, whether `this` is managing its memory. If so, delete it. If we dont do the check one, undefined behaviour comes later.

  // some deep copy operation here...
    
  return *this;
}
```

### Why overloads SMFs?

Compiler will generate SMFs for us, but...

##### The problem using default copy

* e.g. Default Copy Constructor

  ```.cpp file
  template <typename T>
  Vector<T>::Vector<T>(const Vector::Vector<T>& other) :
  _size(other._size), _capacity(other._capacity), _data(other._data) { }
  ```

  * By default, the copy constructor will create **copies** of each member variable
  * This is member-wise copying, It's won't work well with manually allocated memory like pointers.
  * If your variable is a pointer, a member-wise copy will point to the same allocated data, not a new chunk of memory
    * Also called shallow copy, which is problematic because anything done to one pointer affects the other

* Most of the time we want to make a **deep copy**
  * Deep copy: an object that is a complete, **independent copy** of the original

* So we'd want to override it.

  * Declare them in the header and write their implementation in the .cpp, like any function!

  ```.cpp file
  Vector<T>::Vector(const Vector<T>& other)
   : _size(other._size), _capacity(other._capacity), _data(new T[other._capacity]) {
   for (size_t i = 0; i < _size; ++i) _data[i] = other._data[i];
  }
  ```

##### default & delete

delete:

* We can delete special member functions, here to prevent copy

  * Setting a special member function to `delete` removes its functionality!

    ```c++
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
      * **Move Constructible**, **Move Assignable**, but of neither **Copy Constructible** nor **Copy Assignable**

default:

* Declaring any user-defined constructor will make the default -- compiler produced one -- disappear without default setting.

  ```.cpp file
  class PasswordManager {
  	public: 
  		PasswordManager();
  		PasswordManager(const PasswordManager& other) = default; // set 'default' like this
  }
  ```

### Philosophy & Rules

##### Rules of Zero

If the default SMFs work, don’t define your own!

* We should only define new ones when the default ones generated by the compiler won't work
  * This usually happens when we work with **dynamically allocated memory**, like pointers to things on the heap.


* If you don’t need a constructor or a destructor or copy assignment etc. Then simply don’t use it! 

If your class relies on objects/classes that already have these SMFs implemented, then there’s no need to reimplement this logic!

* They will take care of themselves(if their SMFs are correctly implemented)

  ```.cpp file
  class a_string_with_an_id() {
   public:
   /// getter and setter methods for our private variables
   private:
   int id;
   std::string str;
  }
  a_string_with_an_id object;
  ```

  * `std::string` already has copy constructor, copy assignment, move constructor, and move assignment!
    * So let it go!

##### Rule of Three

If you need a custom destructor, then you also **probably need** to define a copy constructor and a copy assignment operator for your class 

* If you use a destructor, that often means that you are **manually dealing with dynamic memory allocation**/are generally just handling your own memory. 
  * Here, The compiler will not be able to automatically generate these for you, because of the manual memory management.

##### Remember

to do the pop quiz