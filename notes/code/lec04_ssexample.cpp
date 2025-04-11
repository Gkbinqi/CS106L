#include<string>
#include<iostream>
#include<sstream>

int main() {
    /// partial Bjarne Quote
    std::string initial_quote = "Bjarne Stroustrup C makes it easy to shoot yourself in the foot";
    /// create a stringstream
    std::stringstream ss;
    ss << initial_quote;
    /// data destinations
    std::string first;
    std::string last;
    std::string language, extracted_quote;
    ss >> first >> last >> language;
    std::getline(ss, extracted_quote);
    std::cout << first << " " << last << " said this: '" << language << ", "  << extracted_quote + "'" << std::endl;
}