#include <algorithm>
#include <iostream>
#include <vector>

#include "tree.h"
#include "utils.hpp"

using namespace std;

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if (word1.size() != word2.size())
            return false;

        int n = word1.size();
        int cnt1[26] = {}, cnt2[26] = {};
        for (int i = 0; i < n; ++i) {
            cnt1[word1[i] - 'a']++;
            cnt2[word2[i] - 'a']++;
        }

        vector<int> v1, v2;
        for (int i = 0; i < 26; ++i) {
            if (cnt1[i] == 0 && cnt2[i] == 0) {
                continue;
            } else if (cnt1[i] != 0 && cnt2[i] != 0) {
                v1.push_back(cnt1[i]);
                v2.push_back(cnt2[i]);
            } else {
                return false;
            }
        }

        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        for (int i = 0; i < v1.size(); ++i)
            if (v1[i] != v2[i])
                return false;

        return true;
    }
};

int main() {
    string word1 = "cabbba", word2 = "abbccc";

    auto sol = new Solution();
    auto ans = sol->closeStrings(word1, word2);
    cout << "\nAnswer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    delete sol;

    return 0;
}
