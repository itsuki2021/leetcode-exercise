#include <algorithm>
#include <iostream>
#include <stack>

#include "tree.h"
#include "utils.hpp"

using namespace std;
using bin_tree::NULL_NODE;
using bin_tree::TreeNode;

class Solution {
  public:
    vector<int> foo(vector<int> nums) {
        nums.push_back(0);
        return nums;
    }
};

int main() {
    int target = 8;
    vector<int> nums = {1, 2, 3, 4};

    auto sol = new Solution();
    auto ans = sol->foo(nums);
    cout << "\nAnswer is:\n";
    // cout << ans << endl;
    utils::printVec1D(ans);
    // utils::printVec2D(ans);
    delete sol;

    return 0;
}