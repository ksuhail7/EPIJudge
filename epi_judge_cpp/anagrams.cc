#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::map;

map<char, int> countLetters(const string& word) {
    map<char, int> charCountMap;
    for(int i = 0; i < word.length(); ++i) {
        char c = word.at(i);
        auto search = charCountMap.find(c);
        if(search == charCountMap.end()) {
            charCountMap[c] = 0;
        }
        charCountMap[c] += 1;
    }
    return charCountMap;
}

bool areAnagrams(const string& word1, const string& word2) {
    map<char, int> countLetters1 = countLetters(word1);
    map<char, int> countLetters2 = countLetters(word2);

    for(auto it = countLetters1.begin(); it != countLetters1.end(); ++it) {
        auto search = countLetters2.find(it->first);
        if(search == countLetters2.end() || search->second != it->second) {
            return false;
        }
    }
    return true;
}

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  // TODO - you fill in here.
  vector<vector<string>> anagramSets;
  map<string, vector<string>> sets;
  for(const string& word : dictionary) {
      auto w_copy = word;
      std::sort(w_copy.begin(), w_copy.end());
      sets[w_copy].push_back(word);
  }
  for(auto set: sets) {
      if(set.second.size() > 1) {
          anagramSets.push_back(set.second);
      }
  }
  return anagramSets;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
