#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> foo1() {
        return {1,2,3,4,5};
    }

    vector<vector<int>> foo2() {
        return {{1,2,3},{4,5,6},{7,8,9}};
    }

    bin_tree::TreeNode* foo3(vector<int> nums) {
        bin_tree::TreeNode* root = bin_tree::createTree(nums);
        return root;
    }
};



int main() {
    using bin_tree::NULL_NODE;

    auto sol = new Solution();
    auto ret1 = sol->foo1();
    auto ret2 = sol->foo2();
    auto ret3 = sol->foo3({1,2,3,NULL_NODE,4, 5, 6,NULL_NODE,NULL_NODE,7,8,NULL_NODE,NULL_NODE,9});

    cout << "Answer is:\n";
    utils::printVec1D(ret1);
    cout << endl;
    utils::printVec2D(ret2);
    cout << endl;
    bin_tree::printTree(ret3);
    cout << endl;
    
    delete sol;
    return 0;
}