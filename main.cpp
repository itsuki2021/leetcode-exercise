#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include <iostream>

using namespace std;
using namespace trie;

class Solution {
public:
    int respace(vector<string>& dictionary, string sentence) {
        TrieNode* root = new TrieNode();
        for (auto word : dictionary) root->insert(word);

        int n = sentence.size();
        vector<int> dp(n + 1);
        for (int i = 1; i < n + 1; ++i) {
            dp[i] = dp[i - 1] + 1;
            for (int idx = 0; idx < i; ++idx)
                if (root->search(sentence.substr(idx, i - idx)))
                    dp[i] = min(dp[i], dp[idx]);
        }
        
        return dp[n];
    }
};



int main() {
    vector<string> dictionary = {"looked","just","like","her","brother"};
    string sentence = "jesslookedjustliketimherbrother";

    auto sol = new Solution();
    auto ans = sol->respace(dictionary, sentence);

    cout << "Answer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    
    delete sol;
    return 0;
}