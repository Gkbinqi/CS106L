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
  auto iterators = find_all(source.begin(), source.end(), isspace);

  Corpus tokens;
  std::transform(iterators.begin(), iterators.end() - 1
  , iterators.begin() + 1
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
  namespace rv = std::ranges::views;

  auto view = source 
  | rv::filter([&dictionary](const auto& token){
    return !dictionary.contains(token.content);
  }) 
  | rv::transform([&dictionary](const auto& token){
    auto likely = dictionary | rv::filter([&token](const auto& word){
      return levenshtein(token.content, word) == 1;});
    std::set<std::string> suggestion(likely.begin(), likely.end());
    return Mispelling{token, suggestion};
  })
  | rv::filter([](const auto& mis){
    return !mis.suggestions.empty(); 
  });

  return std::set<Mispelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"