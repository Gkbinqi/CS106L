#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

/*
不知道为何 如果有comment
autograder就会报错
可能是中文编码问题
总之 分两个文件 一个有comment 一个给autograder
*/

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  /* TODO: Implement this method */
  // std::cout << "geting iterators" << std::endl;
  auto iterators = find_all(source.begin(), source.end(), isspace);
  

  // std::cout << "using transform" << std::endl;
  Corpus tokens;

  // 这个函数看一下cppref的实现例子更好理解
  /*
    transform(_InputIterator1 __first1, _InputIterator1 __last1,
	      _InputIterator2 __first2, _OutputIterator __result,
	      _BinaryOperation __binary_op)
    {
      for (; __first1 != __last1; ++__first1, (void)++__first2, ++__result)
	*__result = __binary_op(*__first1, *__first2);
      return __result;
    }
  // 注意 停止条件为 __first1 != __last1, 如果__last1 == iterators.end(), __first2会指向end, 导致内存错误
  */

  std::transform(iterators.begin(), iterators.end() - 1 // 这个-1, 真离谱
  , iterators.begin() + 1
  , std::inserter(tokens, tokens.end())
  , [&source](auto it1, auto it2){
    return Token{source, it1, it2};
  });

  // for (size_t i = 0; i + 1 < iterators.size(); ++i) {
  //   tokens.insert(Token{source, iterators[i], iterators[i + 1]});
  // }

  // std::cout << "erasing space" << std::endl;
  std::erase_if(tokens, [](const auto& token){
    // std::cout << "Token: " << token.content << std::endl;
    return token.content.empty();
  });

  return tokens;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  namespace rv = std::ranges::views;

  // notice that here we want the misspelled word so we need a ! operator
  auto view = source 
  | rv::filter([&dictionary](const auto& token){
    return !dictionary.contains(token.content);
    // if (!dictionary.contains(token.content)) {
    //   std::cout << "-- Typo found: <<" << token.content << ">>" << '\n';
    //   return true;
    // } else return false;
  }) 
  | rv::transform([&dictionary](const auto& token){
    auto likely = dictionary | rv::filter([&token](const auto& word){
      return levenshtein(token.content, word) == 1;});
    std::set<std::string> suggestion(likely.begin(), likely.end());
    return Mispelling{token, suggestion};
  })
  | rv::filter([](const auto& mis){
    return !mis.suggestions.empty(); // 又是一处! 注意这个'!'
  });

  return std::set<Mispelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"