#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

/*
 * A = [2, 3, 6, 7, 9, 10]
 * B = [ 1, 2, 4, 5, 6]
 * C = [2, 6]
 */
vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  // TODO - you fill in here.
  vector<int> intersect;
  if(A.size() < 1 || B.size() < 1) return {};
  int it_A = 0, it_B = 0;
  while(it_A < A.size() && it_B < B.size()) {
        if(A[it_A] == B[it_B]) {
            int element = A[it_A];
            intersect.push_back(A[it_A]);
            while(A[it_A] == element) it_A++;
            while(B[it_B] == element) it_B++;
        } else if(A[it_A] > B[it_B]){
            while(B[it_B] < A[it_A]) it_B++;
        } else {
            while(A[it_A] < B[it_B]) it_A++;
        }
  }
  return intersect;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
