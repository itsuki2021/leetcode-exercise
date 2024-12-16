#include "tree.h"
#include <deque>
#include <math.h>
#include <queue>
#include <stack>
#include <string>

namespace bin_tree {
using std::cerr;
using std::cout;
using std::deque;
using std::endl;
using std::pair;
using std::queue;
using std::stack;
using std::string;
using std::to_string;

vector<TreeNode *> bfs(TreeNode *const root) {
    if (root == nullptr)
        return {nullptr};

    vector<TreeNode *> ret;
    deque<TreeNode *> list = {root};
    int cnt = 1; // number of valid node in list
    while (cnt) {
        ret.push_back(list.front());

        if (list.front()) {
            list.push_back(list.front()->left);
            cnt += list.front()->left ? 1 : 0;
            list.push_back(list.front()->right);
            cnt += list.front()->right ? 1 : 0;
            list.pop_front();
            cnt--;
        } else {
            list.push_back(nullptr); // left node
            list.push_back(nullptr); // right node
            list.pop_front();
        }
    }

    return ret;
}

vector<TreeNode *> preOrderTraversal(TreeNode *const root) {
    vector<TreeNode *> ret;
    if (root == nullptr)
        return ret;

    stack<pair<bool, TreeNode *>> st;
    st.push({false, root}); // need output, node

    while (!st.empty()) {
        auto [flag, node] = st.top();
        st.pop();
        if (node == nullptr)
            continue;

        if (!flag) {
            st.push({false, node->right});
            st.push({false, node->left});
            st.push({true, node});
        } else {
            ret.push_back(node);
        }
    }

    return ret;
}

vector<TreeNode *> inOrderTraversal(TreeNode *const root) {
    vector<TreeNode *> ret;
    if (root == nullptr)
        return ret;

    stack<pair<bool, TreeNode *>> st;
    st.push({false, root}); // need output, node

    while (!st.empty()) {
        auto [flag, node] = st.top();
        st.pop();
        if (node == nullptr)
            continue;

        if (!flag) {
            st.push({false, node->right});
            st.push({true, node});
            st.push({false, node->left});
        } else {
            ret.push_back(node);
        }
    }

    return ret;
}

vector<TreeNode *> postOrderTraversal(TreeNode *const root) {
    vector<TreeNode *> ret;
    if (root == nullptr)
        return ret;

    stack<pair<bool, TreeNode *>> st;
    st.push({false, root}); // need output, node

    while (!st.empty()) {
        auto [flag, node] = st.top();
        st.pop();
        if (node == nullptr)
            continue;

        if (!flag) {
            st.push({true, node});
            st.push({false, node->right});
            st.push({false, node->left});
        } else {
            ret.push_back(node);
        }
    }

    return ret;
}

int getHeight(TreeNode *const root) {
    if (root == nullptr)
        return 0;

    return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

TreeNode *buildTree(const vector<int> &nums) {
    if (nums.empty())
        return nullptr;

    // create root node
    TreeNode *root = new TreeNode(nums[0]);
    queue<TreeNode *> q;
    q.push(root);

    int i = 1; // begin with second node
    while (!q.empty() && i < nums.size()) {
        TreeNode *current = q.front();
        q.pop();

        // deal with left child
        if (i < nums.size() && nums[i] != NULL_NODE) {
            current->left = new TreeNode(nums[i]);
            q.push(current->left);
        }
        i++;

        // deal with right child
        if (i < nums.size() && nums[i] != NULL_NODE) {
            current->right = new TreeNode(nums[i]);
            q.push(current->right);
        }
        i++;
    }

    return root;
}

void deleteTree(TreeNode *&root) {
    vector<TreeNode *> ret = bfs(root);
    for (int i = ret.size() - 1; i >= 0; i--) {
        if (ret[i])
            delete ret[i];
    }

    root = nullptr;
}

inline void printNTimes(int n, const string &str) {
    for (int i = 0; i < n; ++i)
        cout << str;
}

/**
 * @brief Fill the 2-D array
 *
 * @param arr       input array
 * @param node      binary tree node
 * @param i         column index
 * @param l         left node index
 * @param r         right node index
 */
void fill(vector<vector<string>> &arr, TreeNode *node, int i, int l, int r) {
    if (node == nullptr)
        return;

    arr[i][(l + r) / 2] = to_string(node->val);
    fill(arr, node->left, i + 1, l, (l + r) / 2);
    fill(arr, node->right, i + 1, (l + r + 1) / 2, r);
}

void printTree(TreeNode *const root) {
    int height = getHeight(root);
    if (height == 0)
        return;

    vector<vector<string>> arr(height, vector<string>((1 << height) - 1, " "));
    fill(arr, root, 0, 0, arr[0].size());

    utils::printVec2D(arr);
}
} // namespace bin_tree

namespace trie {
TrieNode::TrieNode() {
    isWord = false;
    for (int i = 0; i < MAX_CHILD; ++i)
        children[i] = nullptr;
}

TrieNode::~TrieNode() {
    for (int i = 0; i < MAX_CHILD; ++i)
        if (children[i])
            delete children[i];
}

void TrieNode::insert(const string &word) {
    TrieNode *root = this;
    int cur;
    for (char c : word) {
        cur = c - MIN_CHAR;
        if (root->children[cur] == nullptr)
            root->children[cur] = new TrieNode();
        root = root->children[cur];
    }
    root->isWord = true;
}

bool TrieNode::search(const string &word) {
    TrieNode *root = this;
    int cur;
    for (char c : word) {
        cur = c - MIN_CHAR;
        if (root->children[cur] == nullptr)
            return false;
        root = root->children[cur];
    }

    return root->isWord;
}

bool TrieNode::startsWith(const string &prefix) {
    TrieNode *root;
    int cur;
    for (char c : prefix) {
        cur = c - MIN_CHAR;
        if (root->children[cur] == nullptr)
            return false;
        root = root->children[cur];
    }

    return true;
}
} // namespace trie

namespace odt {
ChthollyTree::ChthollyTree() {}

set<ChthollyTree::ChthollyNode>::iterator ChthollyTree::split(ll pos) {
    auto it = tree.lower_bound(ChthollyNode(pos, 0, 0));
    if (it != tree.end() && it->l == pos)
        return it;

    it--;
    ll l = it->l, r = it->r, v = it->v;
    tree.erase(it);
    tree.insert(ChthollyNode(l, pos - 1, v));
    return tree.insert(ChthollyNode(pos, r, v)).first;
}

void ChthollyTree::assign(ll l, ll r, ll v) {
    auto end = split(r + 1), begin = split(l);
    tree.erase(begin, end);
    tree.insert(ChthollyNode(l, r, v));
}
} // namespace odt

namespace seg_tree {
SegTree::SegTree(ll start, ll end) {
    assert(start <= end);
    _start = start;
    _end = end;
    root = new Node(_start, _end);
}

SegTree::~SegTree() { deleteTree(root); }

void SegTree::update(cll &l, cll &r, cll &val) {
    assert(_start <= l && l <= r && r <= _end);
    _update(root, l, r, val);
}

ll SegTree::query(cll &l, cll &r) {
    assert(_start <= l && l <= r && r <= _end);
    return _query(root, l, r);
}

void SegTree::pushUp(Node *node) {
    node->sum = node->left->sum + node->right->sum;
}

void SegTree::pushDown(Node *node) {
    if (node->left == nullptr)
        node->left = new Node(node->start(), node->mid());
    if (node->right == nullptr)
        node->right = new Node(node->mid() + 1, node->end());
    if (node->lazy != 0) {
        node->left->sum += node->lazy * node->left->len();
        node->right->sum += node->lazy * node->right->len();
        node->left->lazy += node->lazy;
        node->right->lazy += node->lazy;
        node->lazy = 0;
    }
}

void SegTree::_update(Node *node, cll &l, cll &r, cll &val) {
    if (l <= node->start() && node->end() <= r) {
        node->sum += node->len() * val;
        node->lazy += val;
        return;
    }

    pushDown(node);
    if (l <= node->mid())
        _update(node->left, l, r, val);
    if (r > node->mid())
        _update(node->right, l, r, val);
    pushUp(node);
}

ll SegTree::_query(Node *node, cll &l, cll &r) {
    if (l <= node->start() && node->end() <= r)
        return node->sum;
    ll sum = 0;
    pushDown(node);
    if (l <= node->mid())
        sum += _query(node->left, l, r);
    if (r > node->mid())
        sum += _query(node->right, l, r);

    return sum;
}

void SegTree::deleteTree(Node *node) {
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
} // namespace seg_tree
