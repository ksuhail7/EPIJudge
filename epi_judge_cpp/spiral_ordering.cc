#include <vector>

#include "test_framework/generic_test.h"---y
using std::vector;

vector<int> spiralOrder(const vector<vector<int>>& matrix, int offset) {
    int N = matrix.size();
    vector<int> spiralSeq;
    int st = offset, end = N - 1 - offset;
    vector<vector<int>> direction = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for(int i = 0; i < direction.size(); ++i) {

    }
}
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  // TODO - you fill in here.
  return spiralOrder(square_matrix, 0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
