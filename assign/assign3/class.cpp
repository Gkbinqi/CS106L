#include "class.h"

Canteen::Canteen() : ID_("null"), location_("null"), capacity_(0), menu_size_(0){
    this->dishes_{};
};

Canteen::Canteen(const std::string& ID, const std::string& location, size_t capacity, size_t menu_size) 
: ID_(ID), location_(location), capacity_(capacity), menu_size_(menu_size){
    this->dishes_{};
};

Canteen::~Canteen() {};

std::set<std::string> Canteen::generate_menu(){
    if (dishes_.size() > this->menu_size_) {
        std::set<std::string> menu;
        auto it = dishes_.begin();
        for(size_t i = 0; i < menu_size_; ++i) {
            menu.insert(*it);
            ++it;
        }
        return menu;
    } else {
        std::set<std::string> menu = dishes_;
        return menu;
    }
}

const std::string& Canteen::get_ID() const{
    return this->ID_;
}

const std::string& Canteen::get_location() const{
    return this->location_;
}

std::set<std::string> Canteen::get_menu(){
    return this->generate_menu();
};

const std::set<std::string>& Canteen::get_dishes() const{
    return this->dishes_;
};

void Canteen::add_dish(const std::string& dish) {
    this->dishes_.insert(dish);
};
