#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  /* TODO: Implement this method */
  auto iterators = find_all(source.begin(), source.end(), ::isspace);
  std::set<Token> tokens;
  std::transform(iterators.begin(), iterators.end(), iterators.begin()+1
  , std::inserter(tokens, tokens.end())
  , [&source](auto it1, auto it2){
    return Token{source, it1, it2};
  });
  std::erase_if(tokens, [](Token t){
    if (t.content.empty()) return true;
    return false;
  });
  return tokens;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  return std::set<Mispelling>();
};

/* Helper methods */

#include "utils.cpp"