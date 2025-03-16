#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

// Corpus tokenize(const std::string& source) {return Corpus();}

Corpus tokenize(const std::string& source) {
  /* TODO: Implement this method */
  Corpus tokens;

  auto iterators = find_all(source.begin(), source.end(), isspace);
  // 这个函数看一下cppref的实现例子更好理解
  std::transform(iterators.begin(), iterators.end(), iterators.begin()+1
  , std::inserter(tokens, tokens.end())
  , [&source](auto it1, auto it2){
    return Token{source, it1, it2};
  });

  std::erase_if(tokens, [](const auto& token){
    return token.content.empty();
  });

  return tokens;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  return std::set<Mispelling>();
};

/* Helper methods */

#include "utils.cpp"