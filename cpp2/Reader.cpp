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
template <class Predicate>
static inline void ltrim(std::string &s, Predicate pred) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), pred));
}

// trim from end (in place)
template <class Predicate>
static inline void rtrim(std::string &s, Predicate pred) {
  s.erase(std::find_if(s.rbegin(), s.rend(), pred).base(), s.end());
}

// trim from both ends (in place)
template <class Predicate>
static inline void trim(std::string &s, Predicate pred) {
  ltrim(s, pred);
  rtrim(s, pred);
}

using std::regex;
const regex token_regex(R"rgx([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"|;.*|[^\s\[\]{}('"`,;)]*))rgx",
                        std::regex_constants::ECMAScript | std::regex_constants::extended);
const regex number_regex("[0-9]+");

Reader::Reader(const vector<string> &input) : content(input), current_token(content.begin()) {
  for (auto &str : content) {
    trim(str, [](int c) { return !(std::isspace(c) || c == ','); });
  }
}
string Reader::next() {
  return *current_token++;
}

string Reader::peek() {
  return *current_token;
}

bool Reader::has_next() {
  return current_token != content.end();
}

vector<string> tokenizer(const string &input) {
  try {
    vector<string> tokens(std::sregex_token_iterator(input.begin(), input.end(), token_regex),
                          std::sregex_token_iterator());
    return tokens;
  } catch (std::logic_error &l) {
    return vector<string>();
  }
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
  while (r.has_next() && r.peek()[0] != ')') {
    lst.push_back(read_form(r));
  }
  if (!r.has_next()) {
    std::cerr << "Expected ')', got EOF" << std::endl;
    return MalList();
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
