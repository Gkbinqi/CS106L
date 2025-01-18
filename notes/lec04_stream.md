# Stream
> *How can we convert between string-represented data and the real thing?*

e.g. exempli gratia 例如    

### **stream** DEF
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

### streams overview
> `std::cout` is an output stream. It has type `std::ostream`.  

Two ways to classify streams:  

First, By Direction:  

* Input streams: Used for **reading** data (ex. ‘std::istream’, ‘std::cin’)  
* Output streams: Used for **writing** data (ex. ‘std::ostream’, ‘std::cout’)  
* Input/Output streams: Used for **both reading and writing** data (ex. ‘std::iostream’, ‘std::stringstream’)  

Second, By Source or Destination:  

* Console streams: Read/write to **console** (ex. ‘std::cout’, console out, ‘std::cin’, console in)  
* File streams: Read/write to **files** (ex. ‘std::fstream’, ‘std::ifstream’, ‘std::ofstream’)  
* String streams: Read/write to **strings** (ex. ‘std::stringstream’, ‘std::istringstream’, ‘std::ostringstream’)

### output stream: `std::ostream`, 'std::ofstream'

`std::cout` is the output stream that goes to the console  
Output Stream have type `std::ostream`  

* We can only **send** data to the stream  
* Interact with the stream using the `<<` operator  
* Converts any type into string and sends it to the stream  
```
std::cout << 5 << std::endl; 
// converts int value 5 to string “5”
// and sends “5” to the console output stream
```  

Output File Streams have type `std::ofstream`  

* We can only *send* data to file using the `<<` operator  
* Converts data of any type into a string and sends it to the file stream  
* Must initialize your own ofstream object linked to your file  
```
std::ofstream out(“out.txt”); // variable out is now an ofstream that outputs to out.txt
out << 5 << std::endl; // out.txt contains 5\n
```  
> https://www.onlinegdb.com/A3WW3Ow_l

```
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    std::ofstream out("out.txt");

    // Step 1: Look at out.txt
    // Step 2: Run code as is, and look at out.txt
    // Step 3: Comment out lines 22,23; Run; Look at out.txt
    out << "Hello Sarah" << endl;
    out << "Are there two lines???" << endl;

    return 0;
}
```  
