#include "utils.hpp"
#include "tree.h"
#include <iostream>
#include <algorithm>

using namespace std;
using bin_tree::TreeNode;


class Solution {
public:
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        } else if (val > root->val) {
            return new TreeNode(val, root, nullptr);
        } else {
            root->right = insertIntoMaxTree(root->right, val);
            return root;
        }
    }
};


int main() {
    int null = bin_tree::NULL_NODE;
    vector<int> arr = {5, 2, 4, null, 1};
    int val = 3;

    TreeNode* root = bin_tree::buildTree(arr);
    bin_tree::printTree(root);
    auto sol = new Solution();
    auto ans = sol->insertIntoMaxTree(root, val);

    cout << "Answer is:\n";
    bin_tree::printTree(ans);
    // cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    
    delete sol;

    return 0;
}