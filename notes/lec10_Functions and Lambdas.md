# Lec 10 Functions and Lambdas

### Functions and Lambdas

Predicate

* Definition: A **predicate** is a Boolean-valued function

```c++
bool isDivisible(int n, int d)
{
	return n % d == 0;
}
```

##### Using predicate

How can we use `isVowel` to find the first vowel in a string?

Or `isPrime` to find a prime number in a vector? 

Or `isDivisible` to find a number divisible by 5?

* Key Idea: We need to pass a **predicate** to a **function**

```c++
template <typename It, typename T>
It find(It first, It last, const T& value) {
	for (auto it = first; it != last; ++it) {
		if (*it == value) return it; 
        // This condition worked for finding a specific value, but it’s too specific.
		// How can we modify it to handle a general condition?
    }
	return last;
}
```

What if we could instead pass a predicate to this function as a parameter?

By doing so, we got a new `find_if` function

```c++
template <typename It, typename Pred>
It find_if(It first, It last, Pred pred) {
	for (auto it = first; it != last; ++it) {
		if (pred(*it)) return it;
	}
	return last;
}
```

* **Passing functions allows us to generalize an algorithm with user-defined behavior**

```c++
bool isVowel(char c) {
	c = ::toupper(c);
	return c == 'A' || c == 'E' || c == 'I’ ||
		c == 'O' || c == 'U’;
}
std::string corlys = "Lord of the Tides";
auto it = find_if(corlys.begin(), corlys.end(), isVowel); // what's the type of isVowel?
*it = '0'; // “L0rd of the Tides”

bool isPrime(size_t n) {
	if (n < 2) return false;
	for (size_t i = 3; i <= std::sqrt(n); i++)
		if (n % i == 0) return false;
	return true;
}
std::vector<int> ints = {1, 0, 6}; 
auto it = find_if(ints.begin(), ints.end(), isPrime); // what's the type???
assert(it == ints.end());
```

* What's the type of `Pred`?
  *  For `isVowel`, the type is: `bool(*)(char)`
    * bool: returns a bool
    * (*): It's a function pointer
    * (char): It takes in a char as parameter

Now here is another problem: 

* We want to give our function extra state without introducing another parameter

  ```c++
  bool lessThan5(int x) { return x < 5; }
  bool lessThan6(int x) { return x < 6; }
  bool lessThan7(int x) { return x < 7; }
  find_if(begin, end, lessThan5);
  find_if(begin, end, lessThan6);
  find_if(begin, end, lessThan7);
  ```

* That's really redundant, how can we solve this?

##### ⭐Lambda

Lambda Syntax

```c++
auto lessThanN = [n](int x) {
	return x < n;
};
```

* `auto`: I don’t know the type! But the compiler does.
* `[]`: **Capture clause**, lets us use outside variables
* `()`: **Parameters** Function parameters, exactly like a normal function
* `{}`: **Function body** Exactly as a normal function, except only parameters and captures are in-scope

A note on Lambda

```c++
auto lambda = [capture-values](arguments) {
	return expression;
}

/*
[x](arguments) // captures x by value (makes a copy)
[&x](arguments) // captures x by reference
[x, y](arguments) // captures x, y by value
[&](arguments) // captures everything by reference
[&, x](arguments) // captures everything except x by reference
[=](arguments) // captures everything by value
*/

/*e. g. in assign04*/
using rv = ranges::view;
auto view = source 
  | rv::filter([&dictionary](const auto& token){
    return !dictionary.contains(token.content);
  }) 
  | rv::transform([&dictionary](const auto& token){
    auto likely = dictionary | rv::filter([&token](const auto& word){
      return levenshtein(token.content, word) == 1;});
    std::set<std::string> suggestion(likely.begin(), likely.end());
    return Mispelling{token, suggestion};
  })
  | rv::filter([](const auto& mis){
    return !mis.suggestions.empty();
  });
```

* Lambdas are good for making functions on the fly

```c++
std::string corlys = "Lord of the tides";
auto it = find_if(corlys.begin(), corlys.end(),
	[](auto c) {
		c = toupper(c);
		return c == 'A' || c == 'E' ||
		c == 'I' || c == 'O' || c == 'U’;
});
```

* auto parameters are shorthand for templates

  * This is true wherever you see an auto parameter, not just in lambda functions!

  * Uses implicit instantiation! Compiler figures out types when function is called

  * ```c++
    auto lessThanN = [n](auto x) {
    	return x < n;
    };
    ```

  * ```c++
    template <typename T>
    auto lessThanN = [n](T x) {
    	return x < n;
    };
    ```


### Algorithms

##### functor & lambdas

* Definition: A **functor** is **any object that defines an `operator()`**

* An example of a functor: `std::greater`

  * ```c++
    template <typename T>
    struct std::greater {
    	bool operator()(const T& a, const T& b) const {
    		return a > b;
    	}
    };
    std::greater<int> g;
    g(1, 2); // return false
    ```

* Since a functor is an object, it can have **state**

  * ```c++
    struct my_functor {
    	bool operator()(int a) const {
    		return a * value;
    	}
    	int value;
    };
    my_functor f;
    f.value = 5;
    f(10); // 50
    ```

* When you use a lambda, a functor type is generated automatically under hood.

  * ```c++
    int n = 10;
    auto lessThanN = [n](int x) { return x < n; };
    ```

  * ```c++
    class __lambda_6_18
    {
    public:
    	bool operator()(int x) const { return x < n; }
    	__lambda_6_18(int& _n) : n{_n} {}
    private:
    	int n;
    };s
    int n = 10;
    auto lessThanN = __lambda_6_18{ n };
    ```

#####  Functions & Lambdas Recap

* Use functions/lambdas to **pass around behavior as variables**

* Aside: `std::function` is an overarching(非常重要的) type for functions/lambdas

  * Any functor/lambda/function pointer can be cast to it

  * It is a bit slower

  * I usually use auto/templates and don’t worry about the types!

  * ```c++
    std::function<bool(int, int)> less = std::less<int>{};
    std::function<bool(char)> vowel = isVowel;
    std::function<int(int)> twice = [](int x) { return x * 2; };
    ```

##### Algorithms Finally

Where do we use functions & lambdas?

`<algorithm>`

*  is a collection of template functions
* `<algorithm>` functions operate on iterators
  * `std::count_if(InputIt first, InputIt last, UnaryPred p);`
    * How many elements in [first, last] match predicate p?
  * `std::sort(RandomIt first, RandomIt last, Compare comp);`
    * Sorts the elements in [first, last) according to comparison comp
  * `std::max_element(ForwardIt first, ForwardIt last, Compare comp);`
    * Finds the maximum element in [first, last] according to comparison comp
  * ...
*  Things you can do with the STL are really countless, and **all in their most general form!**
* At most cases we should use STL 
  * page 69
* ![image-20250305095024444](C:\Users\47949\Desktop\CS106L\notes\pic\lec10_STL usage.png)

### Code: Soundex

details in lec_10 code.

### Ranges and Views

Ranges are a **new version of the STL**

* Definition: A range is anything with a begin and end

  * `std::vector`
  * `std::map<K, V>`
  * and so on

* Using ranges we can just pass the range to the function

  ```c++
  int main() {
  	std::vector<char> v = {'a', 'b', 'c', 'd', 'e’};
  	auto it = std::ranges::find(v, 'c');
  }
  ```

* Range algorithms are constrained

  * They make use of the new STL concepts
    * better error message


Views is a way to compose algorithms

* A view is a range that lazily adapts another range

  * There won't be actual effort made during the process
  * Actual operation will take place at the end(actual changes in memory)

* A view is a range that lazily transforms its underlying range, one element at a time

  * For ranges

    ```c++
    std::ranges::sort(v);// This actually sorts vec, RIGHT NOWWW!!!!
    ```

  * For views

    ```c++
    auto view = letters
    	| std::ranges::views::filter(isVowel)
    	| std::ranges::views::transform(toupper);
    std::vector<char> upperVowel = std::ranges::to<std::vector<char>>(view); // actual operation happens here
    ```

* Filter and transform with views

  * Views are composable

  * We can chain views together use operator|

    ```c++
    std::vector<char> letters = {'a','b','c','d','e'};
    std::vector<char> upperVowel = letters
    | std::ranges::views::filter(isVowel)
    | std::ranges::views::transform(toupper)
    | std::ranges::to<std::vector<char>>();
    ```
