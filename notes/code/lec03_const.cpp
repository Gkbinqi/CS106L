#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cin;
using std::cout;

int main() 
{
    vector<int> vec = {1,2,3};
    const vector<int> c_vec = {1,2,3};
    
    // 正确：auto 推导为 vector<int>，拷贝构造新对象
    auto copy = vec;
    // 正确：auto& 推导为 vector<int>&，绑定到 vec 的非常量引用
    auto& ref = vec;
    // 正确：auto 推导为 vector<int>（忽略顶层 const），拷贝构造新对象
    auto copy_c = c_vec;
    // 正确（标注1）：auto& 推导为 const vector<int>&，绑定到 c_vec 的常量引用
    auto& ref_c = c_vec;  // ✅ 合法：引用必须匹配 const 性
    
    
    // 正确：const auto 推导为 const vector<int>，拷贝构造新对象
    const auto c_copy = vec;
    // 正确（标注2）：const auto& 推导为 const vector<int>&，安全绑定到 vec
    const auto& c_ref = vec;  // ✅ 合法：允许常量引用绑定到非常量对象
    // 正确（标注3）：const auto 推导为 const vector<int>，等价于 const vector<int>
    const auto c_copy_c = c_vec;  // ✅ 合法：拷贝时自动添加 const
    // 正确（标注4）：const auto& 推导为 const vector<int>&，安全绑定到 c_vec
    const auto& c_ref_c = c_vec;  // ✅ 合法：双重 const 等价于单层
}