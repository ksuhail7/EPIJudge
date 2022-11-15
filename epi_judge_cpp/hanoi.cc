#include <array>
#include <stack>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::array;
using std::stack;
using std::vector;
const int kNumPegs = 3;

// P1: 1 - n (n is the biggest ring)
// P2: {}
// P3: {}

// transfer 1 -> (n-1) to P3 via P2
// transfer n from P1 -> P2
// transfer 1 -> (n-1) from P3 to P2 via P1
vector<vector<int>> moveRings(int rings, int from, int to, int intermediate) {
    if(rings < 1) return {};
    vector<vector<int>> moves;
    vector<vector<int>> movesFromToInter = moveRings(rings - 1, from, intermediate, to);
    moves.insert(moves.end(), movesFromToInter.begin(), movesFromToInter.end());
    moves.push_back({from-1, to-1});
    auto movesFromInterToTo = moveRings(rings - 1, intermediate, to, from);
    moves.insert(moves.end(), movesFromInterToTo.begin(), movesFromInterToTo.end());
    return moves;
}
vector<vector<int>> ComputeTowerHanoi(int num_rings) {
    return moveRings(num_rings, 1, 2, 3);
}
void ComputeTowerHanoiWrapper(TimedExecutor& executor, int num_rings) {
  array<stack<int>, kNumPegs> pegs;
  for (int i = num_rings; i >= 1; --i) {
    pegs[0].push(i);
  }

  vector<vector<int>> result =
      executor.Run([&] { return ComputeTowerHanoi(num_rings); });

  for (const vector<int>& operation : result) {
    int from_peg = operation[0], to_peg = operation[1];
    if (!pegs[to_peg].empty() && pegs[from_peg].top() >= pegs[to_peg].top()) {
      throw TestFailure("Illegal move from " +
                        std::to_string(pegs[from_peg].top()) + " to " +
                        std::to_string(pegs[to_peg].top()));
    }
    pegs[to_peg].push(pegs[from_peg].top());
    pegs[from_peg].pop();
  }
  array<stack<int>, kNumPegs> expected_pegs1, expected_pegs2;
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs1[1].push(i);
  }
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs2[2].push(i);
  }
  if (pegs != expected_pegs1 && pegs != expected_pegs2) {
    throw TestFailure("Pegs doesn't place in the right configuration");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_rings"};
  return GenericTestMain(args, "hanoi.cc", "hanoi.tsv",
                         &ComputeTowerHanoiWrapper, DefaultComparator{},
                         param_names);
}
