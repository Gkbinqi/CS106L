# Lecture 14: `std::optional`& type safety!

### Recap

Move semantics 

- We have move semantics because sometimes the resource we’re going to take is no longer needed by the original owner 
- Use std::move(x) to turn x, an l-value, to an r-value so that you can immediately take its resources

* Rule of zero: 
  * if you have self-managing member variables, and don’t need to define custom constructors, and operators, then don’t!
* Rule of three: 
  * if you define a custom destructor then you need to also define a custom copy constructor and copy assignment operator.

* Rule of Five: 
  * If you have a custom copy constructor, and copy assignment operator, then you should also define a move constructor and a move assignment operator!

### Type Safety 

> The extent to which a language prevents typing errors.

e.g.

```.cpp file
void removeOddsFromEnd(vector<int>& vec){
	while(vec.back() % 2 == 1){
		vec.pop_back();
	}
}
```

* What if vec is {} / an empty vector!?
  * Cause **Undefined behavior**
* **Undefined behavior**: Function could crash, could give us garbage, could accidentally give us some actual value

Solution:
````.cpp file
void removeOddsFromEnd(vector<int>& vec){
	while(!vec.empty() && vec.back() % 2 == 1){
		vec.pop_back();
	}
}
````

* Key idea: it is the programmers job to enforce the pre-condition that `vec` be non-empty, otherwise we get undefined behavior!