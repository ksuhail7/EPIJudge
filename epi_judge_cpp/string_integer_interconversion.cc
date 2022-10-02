#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  // TODO - you fill in here.
    string s = "";
    if (x == 0) return "0";
    bool isNeg = x < 0;

    while(abs(x) > 0)
    {
        const short rem = x % 10;
        s.push_back(rem);
        x = x / 10;
    }
    if (isNeg) s.push_back('-');
   std::reverse(s.begin(), s.end());
   return s;
}
int StringToInt(const string& s) {
  // TODO - you fill in here.
    int value = 0;
    if (s.length() < 1) return 0;
    bool isNeg = false;
    for(int i = 0; i < s.length(); ++i)
    {
        if (s[i] == '-') {
            isNeg = true;
        } else       {
            const int digit = s[i] - '0';
            if(digit >=0 && digit <= 9)
            {
                value = value * 10 + digit;
            }
        }

    }
  return isNeg ? -value : value;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
