# Stream
> *How can we convert between string-represented data and the real thing?*

e.g. exempli gratia 例如    

### **Stream** DEF
> An abstraction for input/output.   
> Streams convert between data and the string representation of data.  

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
// For other types, you will have to write the << operator yourself!
// We’ll talk about how to write the << operator for custom types during lecture 11 on Operators!
```  

### Streams Overview
> `std::cout` means 'console output' while 'c' means character.

Here we have many types of streams.  
##### Ways to classify streams:  

First, By Direction:  

* Input streams: Used for **reading** data (ex. ‘std::istream’, ‘std::cin’)  
* Output streams: Used for **writing** data (ex. ‘std::ostream’, ‘std::cout’)  
* Input/Output streams: Used for **both reading and writing** data (ex. ‘std::iostream’, ‘std::stringstream’)  

Second, By Source or Destination:  

* Console streams: Read/write to **console** (ex. ‘std::cout’, console output, ‘std::cin’, console input)  
* File streams: Read/write to **files** (ex. ‘std::fstream’, ‘std::ifstream’, ‘std::ofstream’)  
* String streams: Read/write to **strings** (ex. ‘std::stringstream’, ‘std::istringstream’, ‘std::ostringstream’)

What's more, operator `>>` and `<<`  

* “>>” is the stream extraction operator or simply extraction operator
	* Used to extract data from a stream and place it into a variable  
* “<<” is the stream insertion operator or insertion operator  
	* Used to insert data into a stream usually to output the data to a file, console, or string  

### Output Streams: `std::ostream`, `std::ofstream`
> `std::cout` is the output stream that goes to the console stream. It has type `std::ostream`.  

##### Output Stream have type `std::ostream`  
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

More about ofstream is in the code lec04_ofstream.  

##### Details  
**`std::cout` is a global constant object that you get from `#include <iostream>` that can use directly.**  
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
* First call to `std::cin >>` creates a command line prompt that allows the user to type until they hit enter(\n)  
* Each `>>` ONLY reads until the next **whitespace**
	* Whitespace = tab, space, newline
* Everything after the first whitespace **gets saved** and **will be used at the next time std::cin >> is called.**
	* The place it is saved is called a **buffer**
* If there is nothing waiting in the buffer, `std::cin >>` creates a new command line prompt  
	* Which means if the buffer is not empty, `std::cin >>` will just use the buffer rather than require the user for a new input.
* Whitespace is eaten; it won’t show up in output(used as delimiter and then skipped)  

more details in the code demo lec04_cin_details.cpp.  
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


