//
// Created by Suhail Kandanur on 2022-11-15.
//

#include <iostream>
#include <set>
using namespace std;

bool isUniqueUsingSet(const string& s) {
    set<char> uniqueChars;
    for(char c : s) {
        if(uniqueChars.find(c) != uniqueChars.end()) {
            return false;
        }
        uniqueChars.insert(c);
    }
    return true;
}

bool isUniqueUsingBitVector(const string& s) {
    return true;
}

bool isUniqueUsingSort(const string& s) {
    string t;
    std::copy(s.begin(), s.end(), std::back_inserter(t));
    std::sort(t.begin(), t.end());
    auto it = t.begin();
    char prev = 0;
    while(it != t.end()) {
        if(prev == *it) {
            return false;
        }
        prev = *it;
        it++;
    }
    return true;
}
int main(int argc, char* argv[]) {
    string s = "abcc";
    cout << s << " is " << (isUniqueUsingSort(s) ? "" : "NOT") << " unique";
    return 0;
}