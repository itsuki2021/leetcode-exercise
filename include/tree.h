#pragma once
#include <vector>
#include <iostream>

namespace bin_tree {
    using std::vector;

    const int NULL_NODE = INT32_MIN;   // means null node

    /**
     * @brief Binary tree.
     * 
     */
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /**
     * @brief Breadth First Search, INCLUDE NULL NODE.
     * 
     * @param root                  Binary tree
     * @return vector<TreeNode*>    Result items
     */
    vector<TreeNode*> bfs(TreeNode* const root);

    /**
     * @brief Preorder traversal.
     * 
     * @param root                  Binary tree
     * @return vector<TreeNode*>    Result items
     */
    vector<TreeNode*> preOrderTraversal(TreeNode* const root);

    /**
     * @brief Inorder traversal.
     * 
     * @param root                  Binary tree
     * @return vector<TreeNode*>    Result items
     */
    vector<TreeNode*> inOrderTraversal(TreeNode* const root);

    /**
     * @brief Postorder traversal.
     * 
     * @param root                  Binary tree
     * @return vector<TreeNode*>    Result items
     */
    vector<TreeNode*> postOrderTraversal(TreeNode* const root);

    /**
     * @brief Create a Tree object from BFS items.
     * 
     * @param nums BFS items, INT32_MIN in "nums" means null node
     * @return TreeNode root pointer
     */
    TreeNode* createTree(const vector<int>& nums);

    /**
     * @brief Delete a Tree object.
     * 
     * @param root TreeNode root pointer
     */
    void deleteTree(TreeNode*& root);

    /**
     * @brief Print a Tree object.
     * 
     * @param root  TreeNode root pointer
     */
    void printTree(TreeNode* const root);
}


