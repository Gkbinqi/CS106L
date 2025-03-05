#include <iostream>
#include <string>

template <typename It, typename Pred>
It my_find_if(It first, It last, Pred pred) {
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) return it;
    }
    return last;
}

int main() {
    std::string s = "Here is a string.";
    std::cout << "please input a string: ";
    std::getline(std::cin, s);

    // 如果直接使用find_if作为名字, 会报错无法选择正确的函数, 因为<Algorithms>中包含了find_if
    // 可以采取改名, 或者使用 ::find_if 限定命名空间的方法进行
    auto it = my_find_if(s.begin(), s.end(), 
    [](auto c){
        c = toupper(c);
        return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    });
    if (it == s.end()) {
        std::cout << "no vowel" << '\n';
    } else std::cout << *it << std::endl;
}