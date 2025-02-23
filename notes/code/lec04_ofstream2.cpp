#include <fstream>
#include <iostream>

int main()
{
    std::ofstream ofs("hello.txt");
    if (ofs.is_open())
    {
        ofs << "Hello CS106L!" << '\n';
    } else exit(1);
    ofs << "this is the test line2" << '\n';

    ofs.close();
    ofs << "this line won't show up in the file" << '\n';
    
    char flag;
    std::cout << "choice append(a) or not(n): ";
    std::cin >> flag;

    if (flag == 'a') 
    {
        ofs.open("hello.txt", std::ios::app);
        ofs << "choose a, all the line will show up" << '\n';
    } else if (flag == 'n') {
        ofs.open("hello.txt", std::ios::ate);
        ofs << "choose n, only this line will show up" << '\n';
    } else exit(1);
    
    ofs.close();
    return 0;
}