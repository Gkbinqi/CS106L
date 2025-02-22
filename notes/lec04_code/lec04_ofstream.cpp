//https://www.onlinegdb.com/A3WW3Ow_l
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
