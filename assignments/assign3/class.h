#include <string>
#incldue <set>

class Canteen {
private:
    std::string ID;
    std::string location;

    size_t capacity;
    std::set<std::string> menu;
    std::set<std::string> all_dished;

    bool refresh_menu();
public:
    Canteen();
    Canteen(std::string ID, std::string location, size_t capacity);
    std::string get_ID();
    std::string get_location();
}