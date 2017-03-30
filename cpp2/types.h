#pragma once
#include <iostream>
#include <mapbox/variant.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;
using namespace mapbox::util;

struct symbol: public string {
  symbol(string s);
  string str();
};
typedef variant<symbol, int64_t> atom_t;

struct MalList;
typedef variant<atom_t,MalList> MalType;
struct MalList : public vector<MalType>{
};
// class MalType : public variant<value_t,recursive_wrapper<MalType>> {    
// };