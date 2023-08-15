#include <iostream>
#include <algorithm>
#include <stack>

#include "utils.hpp"
#include "tree.h"

using namespace std;
using bin_tree::TreeNode;
using bin_tree::NULL_NODE;

class Solution
{
public:
    vector<int> argsort(const vector<int>& vec) {
        vector<int> res;
        for (int i = 0; i < vec.size(); ++i) res.push_back(i);

        sort(res.begin(), res.end(), 
            [&](int a, int b) { return vec[a] < vec[b]; });

        return res;
    }

    string findReplaceString(string s, vector<int> &indices,
                             vector<string> &sources, vector<string> &targets) {
        int offset = 0, minInd = 0;
        for (int i : argsort(indices)) {
            if (s.substr(indices[i] + offset, sources[i].size()) == sources[i]) {
                s.replace(indices[i] + offset, sources[i].size(), targets[i]);
                offset += targets[i].size() - sources[i].size();
            }
        }

        return s;
    }
};

int main() {
    string s = "vmokgggqzp";
    vector<int> indices = {3, 5, 1};
    vector<string> sources = {"kg","ggq","mo"};
    vector<string> target = {"s","so","bfr"};

    auto sol = new Solution();
    auto ans = sol->findReplaceString(s, indices, sources, target);
    cout << "\nAnswer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    delete sol;

    return 0;
}