#include "utils.hpp"
#include "tree.h"
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
using bin_tree::TreeNode;


class Solution {
public:
    vector<TreeNode*> bfs(TreeNode* const root) {
        if (root == nullptr) return {nullptr};

        vector<TreeNode*> ret;
        queue<TreeNode*> list;
        list.push(root);
        int cnt = 1;    // non-empty nodes in list
        while (cnt) {
            ret.push_back(list.front());

            if (list.front()) {
                list.push(list.front()->left);
                cnt += list.front()->left ? 1 : 0;
                list.push(list.front()->right);
                cnt += list.front()->right ? 1 : 0;
                list.pop();
                cnt--;
            } else {
                list.push(nullptr);     // left node
                list.push(nullptr);     // right node
                list.pop();
            }
        }

        return ret;
    }

    vector<vector<string>> printTree(TreeNode* root) {
        if (root == nullptr) return {};

        vector<TreeNode*> nodes = bfs(root);
        int maxWidth = 2;
        while (maxWidth < nodes.size() + 1) maxWidth *= 2;
        maxWidth -= 1;
        
        vector<vector<string>> ans;
        ans.push_back(vector<string>(maxWidth, ""));
        int curDepth = 1;
        int curWidth = maxWidth / int(pow(2, curDepth));
        for (int i = 0; i < nodes.size(); ++i) {
            if (i > pow(2, curDepth) - 2) {
                curDepth++;
                ans.push_back(vector<string>(maxWidth, ""));
                curWidth = maxWidth / int(pow(2, curDepth));
            }

            if (nodes[i]) ans[curDepth-1][curWidth] = to_string(nodes[i]->val);
            curWidth += (maxWidth / int(pow(2, curDepth-1)) + 1);
        }
        

        return ans;
    }
};


int main() {
    int null = bin_tree::NULL_NODE;
    vector<int> nums = {1,2,3,null,4, 5, 6, null, null, 7, 8};
    TreeNode* root = bin_tree::buildTree(nums);

    auto sol = new Solution();
    auto ans = sol->printTree(root);

    cout << "Answer is:\n";
    // cout << ans << endl;
    // utils::printVec1D(ans);
    utils::printVec2D(ans);
    
    delete sol;
    
    return 0;
}