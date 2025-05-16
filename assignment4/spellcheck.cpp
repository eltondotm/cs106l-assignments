#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  Corpus tokens;

  // Collect iterators for every space, as well as begin and end
  auto space_its = find_all(source.begin(), source.end(), 
                            [](unsigned char c) { return std::isspace(c); });

  // Generate a token between each consecutive pair of iterators
  std::transform(space_its.begin(), space_its.end() - 1, space_its.begin() + 1,
                 std::inserter(tokens, tokens.end()),
                 [&source](auto it1, auto it2) { return Token(source, it1, it2); });

  // Delete any empty tokens
  std::erase_if(tokens, [](Token token) { return token.content.empty(); });

  return tokens;
}

namespace rv = std::ranges::views;

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  auto ms = source | rv::filter([&dictionary](Token t) { return !dictionary.contains(t.content); })
                   | rv::transform([&dictionary](Token t) {
                       auto suggest_view = dictionary | rv::filter([&t](std::string word) {
                         return levenshtein(t.content, word) == 1;
                       });
                       std::set<std::string> suggestions(suggest_view.begin(), suggest_view.end());
                       return Misspelling{t, suggestions};
                     })
                   | rv::filter([](Misspelling m) { return !m.suggestions.empty(); });
  return std::set<Misspelling>(ms.begin(), ms.end());
};

/* Helper methods */

#include "utils.cpp"