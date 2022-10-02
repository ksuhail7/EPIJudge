#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  // TODO - you fill in here.
    vector<int> sortedList;
    std::priority_queue<int, vector<int>, std::greater<int>> p_queue;
    for(auto arr : sorted_arrays)
    {
	    for(auto element : arr)
	    {
            p_queue.emplace(element);

	    }
    }
    while(!p_queue.empty())
    {
        sortedList.push_back(p_queue.top());
        p_queue.pop();
    }

  return sortedList;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
