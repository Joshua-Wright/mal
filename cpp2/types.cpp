#include "types.h"

symbol::symbol(string s) : string(s){};
string symbol::str() { return *this; }