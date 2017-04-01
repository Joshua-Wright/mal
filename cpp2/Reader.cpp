#include "Reader.h"
#include "debug.h"
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
#include <regex>
#include <string>
#include <vector>

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                  std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
              .base(),
          s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

using std::regex;
const regex token_regex(R"rgx([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"|;.*|[^\s\[\]{}('"`,;)]*))rgx",
                        std::regex_constants::ECMAScript | std::regex_constants::extended);
const regex number_regex("[0-9]+");

Reader::Reader(const vector<string> &input) : content(input), current_token(content.begin()) {
  // trim whitespace of all tokens
  for (auto &str : content) {
    trim(str);
  }
}
string Reader::next() {
  return *current_token++;
}

string Reader::peek() {
  return *current_token;
}

vector<string> tokenizer(const string &input) {
  vector<string> tokens(std::sregex_token_iterator(input.begin(), input.end(), token_regex),
                        std::sregex_token_iterator());

  std::cout << "tokens: ";
  for (auto token : tokens) {
    std::cout << token << " ";
  }
  std::cout << std::endl;

  return tokens;
}

Reader read_str(const string &input) {
  return Reader(tokenizer(input));
}

MalType read_form(Reader &r) {
  if (r.peek()[0] == '(') {
    r.next();
    return read_list(r);
  } else {
    return read_atom(r);
  }
}

MalList read_list(Reader &r) {
  MalList lst;
  while (r.peek()[0] != ')') {
    lst.push_back(read_form(r));
  }
  // consume ")"
  r.next();
  return lst;
}

atom_t read_atom(Reader &r) {
  string next = r.next();
  if (regex_match(next, number_regex)) {
    return std::stoll(next);
  } else {
    return symbol(next);
  }
}
