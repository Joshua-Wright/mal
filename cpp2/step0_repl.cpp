#include <iostream>
#include <string>

using std::string;

string read(const string s) {
  return s;
}

string eval(const string s) {
  return s;
}

string print(const string s) {
  return s;
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