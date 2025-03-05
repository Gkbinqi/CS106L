#include "lec10_soundex.h"
#include <map>

static char soundexEncode(char c)
{
  static const std::map<char, char> encoding = {
    {'A', '0'}, {'E', '0'}, {'I', '0'}, {'O', '0'}, {'U', '0'}, {'H', '0'}, {'W', '0'}, {'Y', '0'},
    {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
    {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
    {'D', '3'}, {'T', '3'},
    {'L', '4'},
    {'M', '5'}, {'N', '5'},
    {'R', '6'}
  };
  return encoding.at(std::toupper(c));
}

bool isalpha(char c) {
    
}

std::string soundex(const std::string& s) {
    // first step
    std::string letters;
    std::copy_if(s.begin(), s.end(), std::back_inserter(letters), ::isalpha);
    for (auto& c : s) {
        c = soundexEncode(c);
    }

    // second Coalesce adjacent duplicates
}



std::string soundexRanges(const std::string& s);