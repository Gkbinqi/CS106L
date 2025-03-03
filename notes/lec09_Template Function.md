# lec 09 Template Function

### Recap

What is a template class? 

​	• A blueprint for creating classes with generic types 

Why would you use a template class? 

​	• Template classes eliminate code redundancy!

### Template Functions

```
template <typename T>
T min(T a, T b) {
	return a < b ? a : b;
}
```

| This is a template. It’s not a function                      | This is a function. A.K.A a template instantiation |
| ------------------------------------------------------------ | -------------------------------------------------- |
| `template <typename T> T min(const T& a, const T& b)  {return a < b ? a : b;} ` | `min <std::string>`                                |

##### explicit instantiation &  implicit instantiation

* explicit instantiation: `int a = min<int>(106, 107);`

* implicit instantiation: `auto a = min(1.2, 3.4)`, here compiler automatically determine which type will this function generates

  * problem1:  `min("Jacob", "Fabio");`, these two will have a type `const char*`

    * which means it will be a **pointer comparasion**

  * solution: We can always use explicit instantiation in ambiguous cases like this

    * `min<std::string>("Jacob", "Fabio");`
    * `const char*` gets converted to `std::string` here

  * problem2: `min(106, 3.14);` Doesn't compile

    * These two input have different types

  * solution: make the template more flexable

    * ```
      template <typename T, typename U>
      auto min(const T& a, const U& b) { // let the compiler figure the return type out with auto
      	return a < b ? a : b;
      }
      ```

##### practice

Q: Where do we use template functions in practice?

A: All over the place! One prominent example: `iterators`

Let's write a `find` function

```c++
// Version 01: PPT page 51
template <typename TIterator, typename TValue>
TIterator find(TIterator begin, TIterator end, TValue value) {
  // Logic to find and return the iterator 
  // in this container whose element is value.
  // Should return end if no such element is found.
  Titerator it = begin;
  for (; it != end, ++it) {
    if (*it == value) break;
  }
  return it;
}
```

But, here is one problem

```
StanfordID jacob { "Jacob", "jtrb" };
StanfordID fabio { "Fabio", "fabioi" };
min<StanfordID>(jacob, fabio);
StanfordID min(const StanfordID& a, const StanfordID& b)
{
	return a < b ? a : b;
	// Compiler: ”AHHH what do I do here! I don’t know how to compare two StanfordIDs”
}
```

* Compiler only finds the error **after instantiation**

the compiler yells: 

```c++
$ g++ main.cpp --std=c++20
main.cpp:9:12: error: invalid operands to binary expression
('const StanfordID' and 'const StanfordID')
return a < b ? a : b;
 ~ ^ ~
main.cpp:20:3: note: in instantiation of function template
specialization 'min<StanfordID>' requested here
min<StanfordID>(jacob, fabio);
^
1 error generated.
```

### `Concept`

Some templates' inner operation need specific "tools"

> `std::set s { jacob, fabio };` 
>
> The error message continues to go on Recall: "std::set requires operator<"
>
> Bad templates can produce really confusing compiler errors…

* Idea here: How do we **put constraints on templates**
* How can we be up-front about what we require of a template type?

Java Example: `class ListObject<T extends Comparable<T>>`

Compiler shouldn’t instantiate a template **unless all constraints are met**

```c++
template <typename T>
T min(const T& a, const T& b) // T must have operator<

template <typename T>
struct set; // T must have operator<

template <typename It, typename T>
It find(It begin, It end, const T& value) // It must be an iterator type
```

##### C++ header: `concept`

> https://en.cppreference.com/w/cpp/header/concepts
>
> with many build-in concept
>
> ![image-20250303144126416](C:\Users\47949\Desktop\CS106L\notes\pic\le09_concept.png)
>
> including iterator concepts!
>
> ![image-20250303144359982](C:\Users\47949\Desktop\CS106L\notes\pic\lec09_iterator concepts.png)

```.h file
template <typename T>
concept Comparable = requires(T a, T b) {
	{ a < b } -> std::convertible_to<bool>;
};
```

* `concept`: a **named set of constraints**
* `requires`: Here, given two T’s, I expect the following to hold
* constraint `{ a < b }`: Anything inside the `{ }` must **compile without error**
* constraint `-> std::convertible_to<bool>`: ...and the result must be bool-like, `std::convertible_to<>` is also a concept!
* **Meaning**: All these make a concept that requires a type whose `<` operation is defined and valid and will return a bool value

Using our concept, our definition will be like: 

```.h file
template <typename T> requires Comparable<T>
T min(const T& a, const T& b);
// Super slick shorthand for the above
template <Comparable T>
T min(const T& a, const T& b);
```

Concepts greatly improve compiler errors

##### Recap

* Two reasons to use concepts
  * Better compiler error messages
  * Better IDE support (Intellisense/autocomplete, etc.)
* Concepts are still a new feature
  * STL does not yet support them fully
  * We’ll talk more about this on lec10

### Variadic Templates(可变参数)

> page 82

### Template Metaprogramming

> run code at compile time



