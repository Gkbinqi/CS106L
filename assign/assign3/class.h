#include <string>
#include <set>
#include <random>
#include <iostream>

class Canteen {
private:
    static const size_t max_menu_size = 10;
    static const std::vector<std::string> all_dishes = {
    "Pizza", "Burger", "Salad", "Pasta", "Soup",
    "Steak", "Sushi", "Rice", "Noodles", "Curry"
    };
    std::string ID_;
    std::string location_;
    size_t capacity_;
    size_t menu_size_;

    std::set<std::string> dishes_;

    std::set<std::string> generate_menu();
public:
    Canteen();
    Canteen(const std::string& ID, const std::string& location, size_t capacity, size_t menu_size);
    ~Canteen();

    const std::string& get_ID() const;
    const std::string& get_location() const;
    std::set<std::string> get_menu();
    const std::set<std::string>& get_dishes() const;

    void add_dish(const std::string& dish);
};