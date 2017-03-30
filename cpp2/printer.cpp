#include "printer.h"
#include <sstream>


string pr_str(MalType val) {
  return val.match(
      [](atom_t a) { return a.match([](symbol a) { return a.str(); },
                                    [](int64_t n) { return std::to_string(n); }); },
      [](MalList lst) {
        std::stringstream ss;
        ss << '(';
        for (MalType val : lst) {
          ss << pr_str(val) << ' ';
        }
        string str = ss.str();
        str.back() = ')'; // clobber trailing space
        return str;
      });
}

