#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "Reader.h"
#include "printer.h"

using std::string;
using std::regex;
using std::vector;


MalType read(string s) {
  Reader r = read_str(s);
  return read_form(r);
}

MalType eval(MalType s) {
  return s;
}

string print(const MalType s) {
  return pr_str(s);
}




int main() {
  using namespace std;
  const string prompt = "user> ";
  string line;
  cout << prompt;
  // cout.flush();
  while (getline(cin, line)) {
    cout << print(eval(read(line))) << endl;
    cout << prompt;
  }
  return 0;
}
