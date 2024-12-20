#pragma once
#include "utils.hpp"
#include <cassert>
#include <exception>
#include <iostream>
#include <set>
#include <vector>

namespace bin_tree {
using std::exception;
using std::vector;

const int NULL_NODE = INT32_MIN; // means null node

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
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class NodeException : public exception {
    virtual const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
        return "Invalid node, can not make a non-empty node be the child of a "
               "empty node.";
    }
};

/**
 * @brief Breadth First Search, INCLUDE NULL NODE.
 *
 * @param root                  Binary tree
 * @return vector<TreeNode*>    Result items
 */
vector<TreeNode *> bfs(TreeNode *const root);

/**
 * @brief Preorder traversal.
 *
 * @param root                  Binary tree
 * @return vector<TreeNode*>    Result items
 */
vector<TreeNode *> preOrderTraversal(TreeNode *const root);

/**
 * @brief Inorder traversal.
 *
 * @param root                  Binary tree
 * @return vector<TreeNode*>    Result items
 */
vector<TreeNode *> inOrderTraversal(TreeNode *const root);

/**
 * @brief Postorder traversal.
 *
 * @param root                  Binary tree
 * @return vector<TreeNode*>    Result items
 */
vector<TreeNode *> postOrderTraversal(TreeNode *const root);

/**
 * @brief Get tree height
 *
 * @param root
 * @return int
 */
int getHeight(TreeNode *const root);

/**
 * @brief Create a Tree object from BFS items.
 *
 * @param vec BFS items, INT32_MIN in "vec" means null node
 * @return TreeNode root pointer
 */
TreeNode *buildTree(const vector<int> &nums);

/**
 * @brief Delete a Tree object.
 *
 * @param root TreeNode root pointer
 */
void deleteTree(TreeNode *&root);

/**
 * @brief Print binary tree.
 *
 * @param root  TreeNode root pointer
 */
void printTree(TreeNode *const root);

} // namespace bin_tree

namespace trie {
using std::string;

auto constexpr MAX_CHILD = 26; // maximum size of charset
auto constexpr MIN_CHAR = 'a'; // minimum char in charset

/**
 * @brief Trie tree.
 *
 */
class TrieNode {
  private:
    TrieNode *children[MAX_CHILD];
    bool isWord;

  public:
    TrieNode();
    ~TrieNode();

    /**
     * @brief Insert a new word.
     *
     * @param word Input word
     */
    void insert(const string &word);

    /**
     * @brief Search a word in trie tree.
     *
     * @param word      Input word
     * @return true     Find word in tree
     * @return false    Or not
     */
    bool search(const string &word);

    /**
     * @brief Search a prefix in trie tree.
     *
     * @param prefix    Input prefix
     * @return true     Find prefix in tree
     * @return false    Or not
     */
    bool startsWith(const string &prefix);
};
} // namespace trie

namespace odt {
using std::set;

class ChthollyTree {
    using ll = long long;

  private:
    struct ChthollyNode {
        ll l, r;      // left, right
        mutable ll v; // value
        ChthollyNode(ll l_, ll r_, ll v_) : l(l_), r(r_), v(v_) {}
        bool operator<(const ChthollyNode &other) const { return l < other.l; }
    };

    set<ChthollyNode> tree;

  public:
    ChthollyTree();
    /**
     * @brief split chtholly node into two parts
     *
     * @param pos split position
     * @return the right part after splitting
     */
    set<ChthollyNode>::iterator split(ll pos);

    /**
     * @brief assign node(l, r, v) to tree
     *
     * @param l left
     * @param r right
     * @param v value
     */
    void assign(ll l, ll r, ll v);
};
} // namespace odt

namespace seg_tree {
using ll = long long;
using cll = const long long;

class SegTree {
  private:
    /**
     * @brief node of segment tree
     *
     */
    class Node {
      public:
        Node *left = nullptr, *right = nullptr;
        ll sum = 0, lazy = 0; // sum, lazy mark
      private:
        ll _start, _end; // position

      public:
        Node(ll start, ll end) : _start(start), _end(end) {}
        inline ll start() const { return _start; }
        inline ll end() const { return _end; }
        inline ll mid() const { return _start + (_end - _start) / 2; }
        inline ll len() const { return _end - _start + 1; }
    };
    Node *root = nullptr;
    ll _start, _end;

  public:
    SegTree(ll start, ll end);
    ~SegTree();

    /**
     * @brief update the tree node value
     *
     * @param l     left index
     * @param r     right index
     * @param val   value add to nodes
     */
    void update(cll &l, cll &r, cll &val);

    /**
     * @brief query the sum
     *
     * @param l     left index
     * @param r     right index
     * @return ll
     */
    ll query(cll &l, cll &r);

  private:
    void pushUp(Node *node);
    void pushDown(Node *node);
    void _update(Node *node, cll &l, cll &r, cll &val);
    ll _query(Node *node, cll &l, cll &r);
    void deleteTree(Node *node);
};

} // namespace seg_tree
