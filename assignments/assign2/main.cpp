/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

// self include
#include <sstream>

std::string kYourName = "Binqi Wang"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::ifstream ifs(filename);
  std::string s;
  std::set<std::string> applicants;

  if (!ifs.is_open()) exit(1);
  while(getline(ifs, s)) {
    applicants.insert(s);
  }
  ifs.close();// 有开必有关!
  return applicants;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::queue<const std::string*> matched_ones;
  std::string first, last;
  std::stringstream ss(name);
  ss >> first >> last;
  for (auto it = students.begin(); it != students.end(); ++it) { // 为熟练iterator, 故使用该方式
    ss.clear();
    ss << *it;
    std::string it_f, it_l;
    ss >> it_f >> it_l;
    if (first[0] == it_f[0] && last[0] == it_l[0]) {
      // 注意iterator和pointer虽然相似, 但并非相同, 需要先解iterator引用, 再取string地址
      matched_ones.push(&(*it));
    }
  }

  // 测试选取的queue的元素
  std::cout << "choosen ones: " << '\n';
  size_t size = matched_ones.size();
  for (int i = 0;i < size; matched_ones.pop(), ++i) {
    std::cout << *matched_ones.front() << '\n';
    matched_ones.push(matched_ones.front());
  }

  return matched_ones;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO: Implement this function.
  if (matches.empty()) {
    std::cout << "NO MATCHES FOUND." << '\n';
    return "NO MATCHES FOUND.";
  } else return *matches.front();
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
