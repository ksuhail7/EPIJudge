#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::queue;


// 2, 3, 7, final_score = 12
// 2, 3, 7 -> 10
/// 2, 3, 7 -> 8
// 0

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
    vector<int> combinations(final_score + 1, 0);
    combinations[0] = 1;
    for(int i = 0; i < individual_play_scores.size(); i++) {
        for(int j = individual_play_scores[i]; j <= final_score; ++j) {
            combinations[j] += combinations[j - individual_play_scores[i]];
        }
    }
    return combinations[final_score];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
