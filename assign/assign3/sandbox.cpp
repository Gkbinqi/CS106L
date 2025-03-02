/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include "class.cpp"

void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  Canteen c("001", "SCUT", 1000, 5);
  c.add_dish("111");
  c.add_dish("222");
  c.add_dish("333");
  c.add_dish("444");
  c.add_dish("555");
  c.add_dish("666");
  c.add_dish("777");
  c.add_dish("888");
  c.add_dish("999");
  c.add_dish("000");
  std::set<std::string> menu = c.get_menu();
  for(auto dish : menu) {
    std::cout << dish << '\n';
  }
}