#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include <iostream>

using namespace std;
using namespace bin_tree;

class Codec {
public:
    void dfs1(TreeNode* root, vector<string>& list) {
        if (root == nullptr) return;
        list.push_back(to_string(root->val));
        dfs1(root->left, list);
        dfs1(root->right, list);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";

        vector<string> list;
        dfs1(root, list);
        string ans;
        for (auto s : list) ans += (s + ",");
        return ans;
    }

    TreeNode* dfs2(int le, int ri, const vector<string>& ss) {
        if (le > ri) return nullptr;
        int j = le + 1, t = stoi(ss[le]);
        TreeNode* ans = new TreeNode(t);
        while (j <= ri && stoi(ss[j]) <= t) j++;
        ans->left = dfs2(le + 1, j - 1, ss);
        ans->right = dfs2(j, ri, ss);
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "") return nullptr;

        vector<string> ss;
        int i = 0, j = 0;
        while (i < data.size()) {
            while (j < data.size() && data[j] != ',') j++;
            ss.push_back(data.substr(i, j-i));
            i = ++j;
        }

        return dfs2(0, ss.size() - 1, ss);
    }
};



int main() {
    int null = bin_tree::NULL_NODE;
    vector<int> nums = {41,37,44,24,39,42,48};
    TreeNode* root = buildTree(nums);
    cout << "Input tree" << endl;
    printTree(root);


    Codec* ser = new Codec();
    Codec* deser = new Codec();
    string data = ser->serialize(root);
    TreeNode* ans = deser->deserialize(data);
    cout << "Data is:" << endl;
    cout << data << endl;
    cout << "Answer is:" << endl;
    printTree(ans);

    // vector<string> dictionary = {"looked","just","like","her","brother"};
    // string sentence = "jesslookedjustliketimherbrother";

    // auto sol = new Solution();
    // auto ans = sol->respace(dictionary, sentence);

    // cout << "Answer is:\n";
    // cout << ans << endl;
    // // utils::printVec1D(ans);
    // // utils::printVec2D(ans);
    
    // delete sol;
    return 0;
}