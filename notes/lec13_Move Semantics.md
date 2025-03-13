# Move Semantics

### Why

copy data is expensive, using roughly **35% of the power**

By move semantics, we can reduce unnecessary copy

### Move Semantics

Key Idea: The return value of `takePhoto()` is temporary (it’s destroyed before the next line)

```c++
class Photo {
public:
Photo(int width, int height);
Photo(const Photo& other);
Photo& operator=(const Photo& other);
~Photo();
private:
int width;
int height;
int* data;
};
---
Photo selfie = takePhoto();
```

page 25:
problem: since `takePhoto()` will return a **right-value**, the resource `takePhoto()` get will be destoried immediately after this line of code  while `Photo selfie` still need to require and initialize it's resource. 

How about just **move** the resource of `takePhoto()` to `selfie`?

It's ok, remember to set the r-value's resource(especially dynamic allocated memory) to `nullptr` so that the resource we get wont be deleted by the r-value's destructor. page 34

##### Copy vs Move

`````c++
Photo pic(...);
Photo selfie = pic;
// make copies of persistent objects (e.g. variables)
// that might get used in the future

Photo selfie = takePhoto();
// move temporary objects (e.g return values)
// since we no longer need to use them
`````

but, How does the compiler know whether to move or copy? let's see next part

### l-value & r-value

```c++
void foo(Photo pic) {
	Photo beReal = pic; // pic is a l-value
	Photo insta = takePhoto(); // takePhoto() return a right value
}
```

* l-value can have a definite and get-address-able(using &) address, while r-value canot.

  * ```c++
    void foo(Photo pic) {
    	Photo* p1 = &pic; // valid
    	Photo* p2 = &takePhoto(); // Doesn't work!
    }
    ```

* A l-value can appear on either side of an = while a r-value can appear only right of an =

  * `x = y; y = 5;`, `x = 5; 5 = y;// invalid here` ~~5 = y~~ is invalid.

* l-value’s lifetime is until **the end of scope**, r-value’s lifetime is **until the end of line**

* An lvalue is persistent An rvalue is temporary

l-value and r-value have different reference way

| l-value                                                      | r-value                                                      |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `void upload(Photo& pic); int main() { Photo selfie = takePhoto(); upload(selfie); }` | `void upload(Photo&& pic);  int main() { upload(takePhoto()); }` |

We can do whatever we want with `Photo&& pic`, it’s temporary!

lvalue references

* Syntax: Type&
* Persistent, must keep object in valid state after function terminates

rvalue references

* Syntax: Type&&
* Temporary, we can steal (move) its resources
* Object might end up in an invalid state, but that’s okay! It’s temporary!

**Key Idea: Overloading & and && parameters distinguish lvalue and rvalue references**

Now we have two special type of SMFs

* Move constructor • `Type::(Type&& other) `
* Move assignment operator • `Type& Type::operator=(Type&& other)`

### `std::move` and SMFs

* Solution: force move semantics by using `std::move`
* `std::move` doesn’t do anything special!
  * `std::move` just type casts an lvalue to an rvalue
  * ![image-20250307100010756](C:\Users\47949\Desktop\CS106L\notes\pic\lec13_stdmove.png)

* Like `const_cast`, we ”opt in” to potentially error-prone behaviour
  * What if we try to use an object after it’s been moved!
* Try to avoid explicitly using std::move unless you have good reason!
  * E.g. performance really matters, and you know for sure the object won’t be used!



Now we have many SMFs

* Do I need to define them all!?
  * No! **Rule of zero, three, and five!**
* Rule of Zero
  * If a class doesn’t manage memory (or another external resource), the compiler generated versions of the SMFs are sufficient!
  * Example: Compiler generated SMFs of Post will call SMFs of Photo and std::string
* Rule of Three
  * If a class manages external resources, we must define copy assignment/constructor
    * Rule of Three: If you need any one of these, you need them all:
      * Destructor
      * Copy Assignment
      * Copy Constructor
  * If we don’t, compiler-generated SMF won’t copy underlying resource
    * This will lead to bugs, e.g. two Photo’s referring to the same underlying data
* Rule of Five
  * If we defined copy constructor/assignment and destructor, we should also define move constructor/assignment
  * This is not required, but our code will be slower as it involves unnecessary copying
  * ![image-20250307100347218](C:\Users\47949\Desktop\CS106L\notes\pic\lec13_ruleof5.png)
