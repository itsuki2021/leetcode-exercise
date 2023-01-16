#include "utils.hpp"
#include "tree.h"
#include "binary_search.hpp"
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    vector<int> getNext(const string& s) {
        vector<int> next(s.size());
        int j = -1;
        next[0] = j;
        for (int i = 1; i < s.size(); ++i) {
            while (j >= 0 && s[i] != s[j + 1]) j = next[j];

            if (s[i] == s[j + 1]) ++j;

            next[i] = j;
        }

        return next;
    }

    int strStr(string haystack, string needle) {
        if (needle.size() == 0) return 0;

        vector<int> next = getNext(needle);
        int j = -1;
        for (int i = 0; i < haystack.size(); ++i) {
            while (j >= 0 && haystack[i] != needle[j + 1]) j = next[j];
            if (haystack[i] == needle[j + 1]) ++j;

            if (j == (needle.size() - 1)) return i - needle.size() + 1;
        }

        return -1;
    }
};

int main() {
    string haystack = "aabaabaafa";
    string needle = "aabaaf";
    // string needle = "abcabdddabcabc";

    auto sol = new Solution();
    auto ans = sol->strStr(haystack, needle);
    cout << "\nAnswer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    delete sol;

    return 0;
}