#pragma once
#include <iostream>
#include <mapbox/variant.hpp>
#include <string>
#include <vector>
#include "types.h"

using std::string;
using std::vector;
using namespace mapbox::util;

class Reader {
  vector<string> content;
  vector<string>::iterator current_token;

public:
  Reader(const vector<string> &input);

  string next();

  string peek();
};

vector<string> tokenizer(const string &input);

Reader read_str(const string &input);

MalType read_form(Reader &r);
MalList read_list(Reader &r);
atom_t read_atom(Reader &r);