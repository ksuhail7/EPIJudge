#include "test_framework/generic_test.h"
double Power(double x, int y) {
  // TODO - you fill in here.
  if(y == 0) return 1;
  if(y == 1) return x;
  double inter = Power(x, abs(y)/2);
  double result;
  if((abs(y) & 1) == 0) {
      result = inter * inter;
  } else {
      result = x * inter * inter;
  }
  return y < 0 ? 1/result : result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);

}
