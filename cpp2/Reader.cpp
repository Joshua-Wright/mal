#include "Reader.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using std::regex;
const regex token_regex(R"regex([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"|;.*|[^\s\[\]{}('"`,;)]*))regex");

Reader::Reader(const vector<string> &input) : content(input), current_token(content.begin()) {}
string Reader::next() {
  current_token++;
  return *current_token;
}

string Reader::peek() {
  return *current_token;
}

vector<string> tokenizer(const string &input) {
  return vector<string>(std::sregex_token_iterator(input.begin(), input.end(), token_regex),
                        std::sregex_token_iterator());
}

Reader read_str(const string &input) {
  return Reader(tokenizer(input));
}

MalType read_form(Reader &r) {
  switch (r.peek()[0]) {
  case '(':
    return read_list(r);
  default:
    return read_atom(r);
  }
}

MalList read_list(Reader &r) {
  r.next(); // read off the "("
  MalList lst;
  while (r.peek() != ")") {
    // std::cout << r.peek() << std::endl;
    lst.push_back(read_form(r));
  }
  return lst;
}

atom_t read_atom(Reader &r) {
  string next = r.next();
  std::stringstream stream(next);
  int64_t x;
  char test;
  if ((!(stream >> x)) || (stream >> test)) {
    return x;
  } else {
    return symbol(next);
  }
}
