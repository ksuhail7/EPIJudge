#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindMaximumSubarray(const vector<int>& A) {
  // TODO - you fill in here.
  int maxSum = 0;
  int sum = 0, minSum = 0;
  for(int i = 0; i < A.size(); ++i) {
      sum += A[i];
      if(sum < minSum) minSum = sum;
      if((sum - minSum) > maxSum) {
          maxSum = sum - minSum;
      }
  }
  return maxSum;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "max_sum_subarray.cc", "max_sum_subarray.tsv",
                         &FindMaximumSubarray, DefaultComparator{},
                         param_names);
}
