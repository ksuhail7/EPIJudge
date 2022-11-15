#include <string>

#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
  // TODO - you fill in here.
  if(num_as_string == "") return "";
  bool isNeg = (num_as_string[0] == '-');
  int base10 = 0;
  for(int i = isNeg ? 1 : 0; i < num_as_string.length(); ++i) {
    char c = num_as_string[i];
    int val = (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10;
    base10 = base10 + (val * pow(b1, num_as_string.length() - 1 - i));
  }
  string convertedString = base10 == 0 ? "0" : "";
  while(base10 > 0) {
        int rem = base10 % b2;
        base10 = base10 / b2;
        char val = (rem > 9) ? ('A' + (rem - 10)) : '0' + rem;
        convertedString.push_back(val);

  }
  if(convertedString.empty()) convertedString.push_back('0');
  if(isNeg) convertedString.push_back(('-'));
  std::reverse(convertedString.begin(), convertedString.end());
  return convertedString;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
