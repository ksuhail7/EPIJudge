#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfKHelper(const vector<int>& A, int k, int left, int right) {
    if(left > right) return -1;
    int mid = left + (right - left)/2;
    if(A[mid] == k) {
        int first = SearchFirstOfKHelper(A, k, left, mid - 1);
        return first == -1 ? mid : first;
    } else if (A[mid] > k) {
        return SearchFirstOfKHelper(A, k, left, mid - 1);
    } else {
        return SearchFirstOfKHelper(A, k, mid + 1, right);
    }
}
int SearchFirstOfK(const vector<int>& A, int k) {
  // TODO - you fill in here.
  return SearchFirstOfKHelper(A, k, 0, A.size() - 1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
