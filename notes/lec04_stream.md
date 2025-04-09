# Lec 04 Stream
> *a general input/output(IO) abstraction for C++*

### DEF
> An abstraction for input/output.   
> Streams convert between data and the string representation of data.  

Abstraction:

> Abstractions provide a consistent interface,  and in the case of streams the interface is for reading and writing data!

Basic stream usage: `std::cin` and `std::cout`   
```
// use a stream to print any primitive type! 
std::cout << 5 << std::endl; // prints 5 
// and most from the STL work!
std::cout << "Sarah" << std::endl;
// Mix types!
std::cout << "Sarah is " << 21 << std::endl;
Student s = {"Sarah", "CA", 21};
//std::cout << s << std::endl; // this doesn't works!
std::cout << s.name << s.age << std::endl; // this works
// Any primitive type + most from the STL work!
// For other types, you will have to overload the << operator yourself!
// We’ll talk about how to write the << operator for custom types during lecture 11 on Operators!
```

The `std::cout` stream is an instance of `std::ostream` which represents the **standard output stream**!

The `std::cin` stream is an instance  of `std::istream` which represents the **standard input stream**!

Why Stream: Streams allow for a **universal way** of dealing with external data

### Streams Overview

> `std::cout` means 'console output' while 'c' means character.

Here we have many types of streams.  

![stream inheritance](C:\Users\47949\Desktop\CS106L\notes\pic\lec04_stream inheritance.png)

![image-20250223095458233](C:\Users\47949\Desktop\CS106L\notes\pic\lec04_stream ios_base.png)

![image-20250223095617594](C:\Users\47949\Desktop\CS106L\notes\pic\lec04.png)

![image-20250223100256300](C:\Users\47949\Desktop\CS106L\notes\pic\lec04_iostream.png)

##### Ways to classify streams:  

First, By Direction:  

* Input streams (I): Used for **reading** data (ex. `std::istream`, `std::cin`)  
  * a way to read data from a source
  * Are inherited from `std::istream`
  * ex. reading in something from the console (`std::cin`) 
  * primary operator:` >>` (called the **extraction operator**)

* Output streams (O): Used for **writing** data (ex. `std::ostream`, `std::cout`)  
  * a way to write data to a destination
  * Are inherited from `std::ostream` 
  * ex. writing out something to the console (`std::cout`) 
  * primary operator: `<<` (called the **insertion operator**)

* Input/Output(IO) streams: Used for **both reading and writing** data (ex. `std::iostream`, `std::stringstream`)  

Second, By Source or Destination:  

* Console streams: Read/write to **console** (ex. `std::cout`, console output, `std::cin`, console input)  
* File streams: Read/write to **files** (ex. `std::fstream`, `std::ifstream`, `std::ofstream`)  
* String streams: Read/write to **strings** (ex. `std::stringstream`, `std::istringstream`, `std::ostringstream`)

What's more, operator `>>` and `<<`  

* `>>` is the stream extraction operator or simply extraction operator
	* Used to extract data from a stream and place it into a variable  
* `<<` is the stream insertion operator or insertion operator  
	* Used to insert data into a stream usually to output the data to a file, console, or string  

### `std::stingstream`

> a way to treat strings as streams, it inherit  `std::iostream`

stringstreams are useful for use-cases that deal with mixing data types

usage demonstration: 2025W_PPT page 39

```
int main() {
 /// partial Bjarne Quote
 std::string initial_quote = “Bjarne Stroustrup C makes it easy to shoot yourself in the foot”;
 /// create a stringstream
 std::stringstream ss(initial_quote);
 /// data destinations
 std::string first;
 std::string last;
 std::string language, extracted_quote;
 ss >> first >> last >> language;
 std::getline(ss, extracted_quote);
 std::cout << first << “ ” << last << “ said this: ‘” << language << “ “ << extracted_quote + “‘“ << std::endl;
}
```





### `std::getline()`

> Used to read a line from an input stream

`getline()` reads an input stream, `is`, up until the `delim` char and  stores it in some buffer, `str`

`istream& getline(istream& is, string& str, char delim);`

* `istream& is`: the `istream` where `getline` reads from, e.g. `std::cin`

* `string& str`: the buffer where stores the output

* `char delim`: delimiter, where to stop when reading, **set as '\n' by default.**
* `getline()`  consumes the delim character! 
  * PAY ATTENTION TO THIS:)
* Designed to work with character sequences



### Output Streams: `std::ostream`, `std::ofstream`
> `std::cout` is the output stream that goes to the console stream. It has type `std::ostream`.  

##### Output Stream have type `std::ostream`  

* a way to write data to a destination/external source 
  * ex. writing out something to the console (`std::cout`) 

* We can only **send** data to the stream  
* Interact with the stream using the `<<` operator  
* **Converts any type into string and sends it to the stream**  
```
std::cout << 5 << std::endl; 
// converts int value 5 to string “5”
// and sends “5” to the console output stream
```

##### Output File Streams have type `std::ofstream`  
* We can only *send* data to file using the `<<` operator  
* **Converts data of any type into a string and sends it to the file stream** 
* Must initialize your own ofstream object linked to your file  
```
std::ofstream out(“out.txt”); // variable out is now an ofstream that outputs to out.txt
out << 5 << std::endl; // out.txt contains 5\n
```

More about `ofstream` is in the code *lec04_ofstream*.  

##### Details  
**`std::cout` is a global constant object that you get from `#include <iostream>` that can be used directly.**  
**To use any other output stream, you must first initialize it!**  

### Input Streams
> `std::cin` is an input stream. It has type `std::istream`

##### Input Streams
* Have type `std::istream`  
* You can only receive strings using the `>>` operator  
* Receives a string from the stream and converts it to data 
* `std::cin >> a`, here `std::cin` is a `std::istream` and transfer the data to `a`  
* `std::cin` is the input stream that gets input from the console  
```
int x;
string str;
std::cin >> x >> str; //reads exactly one int then one string from console
```

##### `std::cin` in details:
* First call to `std::cin >>` creates a command line prompt(should use `std::cout` to show the prompt words, or there will only be a slash line shining) that allows the user to type until they hit enter(\n)  
* ⭐Each `>>` ONLY reads until the next **whitespace**!
	* Whitespace = tab, space, newline
* ⭐Everything after the first whitespace **gets saved** and **will be used at the next time std::cin >> is called.**
	* The place that the rest line is saved is called a **buffer**
* If there is nothing waiting in the buffer, `std::cin >>` creates a new command line prompt  
	* Which means if the buffer is not empty, `std::cin >>` will just use the buffer rather than require the user for a new input.
* Whitespace is eaten; it won’t show up in output(used as delimiter and then skipped)  

more details in the code demo *lec04_cin_details.cpp*.  
```
Iteration: 1
1 3 // first prompt, given 2 input
X: 1
Iteration: 2
X: 3 // here since there is '3' in the buffer `std::cin` wont give prompt
Iteration: 3
1 3 4 5 7 // empty buffer, new prompt
X: 1
Iteration: 4
X: 3
Iteration: 5
X: 4 // buffer is always not empty, using buffer rather than give prompt
```

##### `std::istream` Details:  As a Sequence of Characters

**More details in slides.**

##### e.g. 1. White Space

``````
int x; string y; int z;
// cin input: "42 ab 4\n"
cin >> x; 
cin >> y;
cin >> z;
``````

use □ to indicate that whitespace here

1. `cin >> x`: 

input "42□ab□4\n", pointer reads 42 in and meet the whitespace, reading stop, skip the whitespace.

Character exist, stored in buffer.

2. `cin >> y`

Since buffer is not empty, `cin >> y` will use the buffer instead of give a prompt.

pointer reads in ab and meet the whitespace, reading stop, skip □.

buffer is still not empty.

3. `cin >> z`

pointer reads in 4 and meed the \n.

##### e.g. 2. Reading Fail 

```
 string str;
 int x;
 std::cin >> str >> x;
 //what happens if input is blah blah?
 std::cout << str << x;
```

1. `std::cin **>> str** >> x` input into `str`

input: "blah□blah\n", reads the first "blah" in and meet the white space. stop, skip □.

`str` is "blah"

2. `std::cin >> str **>> x**` input into `x`

Now the pointer will read a stream like "blah\n", but `x` is a int variable so the read process will fail.

The program won't crash, but `x` will be set to 0 to indicate a fail has occured. 

##### e.g. 3. Fail Bits

```
// https://www.onlinegdb.com/X5RqXJKh1
#include <iostream>
using namespace std;
int main()
{
    string str;
    int x; 
    string otherStr;
    // Input: blah blah blah 
    cin >> str >> x >> otherStr;
    
    cout << "This is str: " << str << endl;
    cout << "This is x: " << x << endl; 
    cout << "This is otherStr: " << otherStr << endl; 

    return 0;
}
```

Here is the output:

```
blah blah blah
This is str: blah
This is x: 0
This is otherStr: 
```

Once an error is detected, the input stream’s **fail bit** is set, and it will no longer accept input

##### e.g. 4. No Whitespace

```
int age; double hourlyWage; 
cout << "Please enter your age: ";
cin >> age;  
cout << "Please enter your hourly wage: "; 
cin >> hourlyWage;
//what happens if first input is 2.17?
```

first, 2 is read into `age` when pointer meets '.', and then ".17" is read into`hourlyWage` since '.' won't be skip and pointer starts at '.'



