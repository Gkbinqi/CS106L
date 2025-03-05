# Lec11 Operator Overloading

### Recap

* Template classes: a template is like a class factory
* Const Correctness: A contract between the class designer and C++ programs.
* Functors: any object that has a operator()
* Algorithm: modify container in a generic way by iterator

### Operator Overloading

* Why should we use operators at all rather than function?
  * **“Operators allow you to convey meaning about types that functions don’t”**

##### Operator Overloading Details

*  Just like we declare functions in a class, **we can declare an operator’s functionality**
* When we use that operator with our new object, it performs a custom function or operation
* Just like in function overloading, **if we give it the same name, it will override the operator’s behavior!**
  * ![image-20250305103314690](C:\Users\47949\Desktop\CS106L\notes\pic\lec11_Operators that can be Overloaded.png)
* Here is the operators that can't be overloaded
  * Scope Resolution `::`
  * Ternary`(statement) ? a : b`
  * Member Access `.`
  * Pointer-to-member access `.*`, `->`
  * Object size, type, and casting `sizeof() typeid() cast()`

##### Member Overloading & Non-member Overloading

There are two ways to overload: 

* Member overloading 
  * `bool StanfordID::operator< (const StanfordID& rhs) const {...}`
  * Declares the overloaded operator within the scope of your class
* Non-member overloading 
  * `bool operator< (const StanfordID& lhs, const StanfordID& rhs);`
  * Declare the overloaded operator outside of class definitions 
  * Define both the left and right hand objects as parameters 

* **Non-member overloading** is actually preferred by the STL, and is more idiomatic C++
  * Allows for the left-hand-side to be a non-class type
  * Allows us to overload operators with classes we don’t own
    * We could define an operator to compare a `StanfordID` to other custom classes you define.

##### Non-member Overloading & friend

`bool operator< (const StanfordID& lhs, const StanfordID& rhs);`

* Both the left and right hand side of the operator are passed in in non-member operator overloading!

* How can we access the variables of the class using a non-member overloading?(now we can't use `this->`!)

  * The `friend` keyword allows non-member functions or classes to access private information in another class!

  * In the header of the target class you declare the operator overload function as a friend

  * ```.h file
    class StanfordID {
    private:
    	std::string name;
    	std::string sunet;
    	int idNumber;
    public:
    	// constructor for our StudentID
    	StanfordID(std::string name, std::string sunet, int idNumber);
    	// many methods here...
     
    	friend bool operator < (const StanfordID& lhs, const StanfordID& rhs);
    }
    ```

  * ```.h file
    #include StanfordID.h
    bool operator< (const StanfordID& lhs, const StanfordID& rhs)
    {
    	return lhs.idNumber < rhs.idNumber;
    }
    ```

* Now, our compiler will be happy with this code:

  ```.cpp file
  StanfordID jacob;
  StanfordID fabio;
  auto minStanfordID = min<StanfordID>(jacob, fabio);
  StanfordID min(const StanfordID& a, const StanfordID& b)
  {
  	return a < b ? a : b; // now compiler knows what to do with < here
  } 
  ```

### Again, WHY?

* There are many operators that you can define in C++ like we saw
* There’s a lot of functionality we can unlock with operators
* **“Operators allow you to convey meaning about types that functions don’t”**

##### Rules and Philosophies 

* Because operators are intended to **convey meaning about a type**, **the meaning should be obvious**
* The operators that we can define are oftentimes arithmetic operators. The functionality should be **reasonably similar to their corresponding operations**(the meaning operator convey here should be consistent with the operator's generic meaning)
  * You don’t want to define `operator+` to be set subtraction

* If the meaning is not obvious, then maybe define a function for this
  * We can set the name of the function to make it specific
* This is known as the Principle of Least Astonishment (PoLA)
  * Less cognition load, more consistency

##### In general

* There are some good practices like the rule of contrariety

* For example when you define the `operator==` use the rule of contrariety to define `operator!=`

  ```.cpp file
  bool StanfordID::operator==(const StanfordID& other) const {
  	return (name == other.name) && (sunet == other.sunet) && (idNumber == other.idNumber);
  }
  
  bool StanfordID::operator!=(const StanfordID& other) const {
  	return !(*this == other);
  }
  ```

* However there’s also a lot of flexibility in implementing operators

  * For example `<<`stream insertion operator

  * ```c++
    std::ostream& operator << (std::ostream& out, const StanfordID& sid) {
    	out << sid.name << " " << sid.sunet << " " << sid.idNumber;
    	return out;
    }
    std::ostream& operator << (std::ostream& out, const StudentID& sid) {
    	out << "Name: " << sid.name << " sunet: " << sid.sunet << " idnumber: " << sid.idNumber;
    	return out;
    }
    ```

  * The way you use this operator may influence how you implement it

##### Final thoughts

* Operator overloading unlocks a new layer of functionality and meaning within objects that we define
* Operators should make **sense**, the entire point is that **convey some meaning** that functions don’t about the type itself.

* You should overload when you need to
  * for example if you’re not using a stream with your type, then don’t overload `<<` or `>>`.