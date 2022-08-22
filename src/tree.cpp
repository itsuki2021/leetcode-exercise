#include "tree.h"
#include <deque>
#include <string>
#include <stack>
#include <math.h>


namespace bin_tree {
using std::deque;
using std::string;
using std::stack;
using std::pair;
using std::to_string;
using std::cout;
using std::cerr;
using std::endl;

vector<TreeNode*> bfs(TreeNode* const root) {
    if (root == nullptr) return {nullptr};

    vector<TreeNode*> ret;
    deque<TreeNode*> list = {root};
    int cnt = 1;    // number of valid node in list
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
            list.push_back(nullptr);    // left node
            list.push_back(nullptr);    // right node
            list.pop_front();
        }
    }

    return ret;
}

vector<TreeNode*> preOrderTraversal(TreeNode* const root) {
    vector<TreeNode*> ret;
    if (root == nullptr) return ret;

    stack<pair<bool, TreeNode*>> st;
    st.push({false, root});     // need output, node

    while (!st.empty()) {
        auto [flag, node] = st.top();
        st.pop();
        if (node == nullptr) continue;
        
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

vector<TreeNode*> inOrderTraversal(TreeNode* const root) {
    vector<TreeNode*> ret;
    if (root == nullptr) return ret;

    stack<pair<bool, TreeNode*>> st;
    st.push({false, root});     // need output, node

    while (!st.empty()) {
        auto [flag, node] = st.top();
        st.pop();
        if (node == nullptr) continue;
        
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

vector<TreeNode*> postOrderTraversal(TreeNode* const root) {
    vector<TreeNode*> ret;
    if (root == nullptr) return ret;

    stack<pair<bool, TreeNode*>> st;
    st.push({false, root});     // need output, node

    while (!st.empty()) {
        auto [flag, node] = st.top();
        st.pop();
        if (node == nullptr) continue;
        
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

int getHeight(TreeNode* const root) {
    if (root == nullptr) return 0;

    return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

TreeNode* buildTree(const vector<int>& vec) {
    vector<TreeNode*> vecTree (vec.size(), nullptr);
    TreeNode* root = nullptr;
    for (int i = 0; i < vec.size(); i++) {
        TreeNode* node = nullptr;
        if (vec[i] != NULL_NODE) node = new TreeNode(vec[i]);
        vecTree[i] = node;
        if (i == 0) root = node;
    }

    for (int i = 0; i * 2 + 2 < vec.size(); i++) {
        if (vecTree[i] != nullptr) {
            vecTree[i]->left = vecTree[i * 2 + 1];
            vecTree[i]->right = vecTree[i * 2 + 2];
        }
    }

    return root;
}

void deleteTree(TreeNode*& root) {
    vector<TreeNode*> ret = bfs(root);
    for (int i = ret.size()-1; i >= 0; i--) {
        if (ret[i]) delete ret[i];
    }

    root = nullptr;
}

inline void printNTimes(int n, const string& str) {
    for (int i = 0; i < n; ++i) cout << str;
}

void printTreeBak(TreeNode* const root) {
    if (root == nullptr) return;

    vector<TreeNode*> ret = bfs(root);
    int curDepth = 1;
    int maxWidth = 2;   // max width of tree
    while (maxWidth < ret.size() + 1) maxWidth *= 2;
    maxWidth -= 1;

    // print tree node
    printNTimes(maxWidth, "-");
    cout << endl;
    printNTimes(maxWidth / int(pow(2, curDepth)), " ");
    for (int i = 0; i < ret.size(); ++i) {
        // first node of a layer
        if (i > pow(2, curDepth) - 2) {
            curDepth++;
            cout << endl;
            printNTimes(maxWidth / int(pow(2, curDepth)), " ");
        }

        if (ret[i]) cout << ret[i]->val;
        else cout << " ";

        // interval between nodes
        printNTimes(maxWidth / int(pow(2, curDepth-1)), " ");
    }
    cout << endl;
    printNTimes(maxWidth, "-");
    cout << endl;
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
void fill(vector<vector<string>>& arr, TreeNode* node, int i, int l, int r) {
    if (node == nullptr) return;

    arr[i][(l+r)/2] = to_string(node->val);
    fill(arr, node->left, i + 1, l, (l + r) / 2);
    fill(arr, node->right, i + 1, (l + r + 1) / 2, r);
}

void printTree(TreeNode* const root) {
    int height = getHeight(root);
    vector<vector<string>> arr(height, vector<string>((1 << height) - 1, ""));
    fill(arr, root, 0, 0, arr[0].size());

    utils::printVec2D(arr);
}

}   // namespace bin_tree


namespace trie {
TrieNode::TrieNode() {
    isWord = false;
    for (int i = 0; i < MAX_CHILD; ++i) children[i] = nullptr;
}

TrieNode::~TrieNode() {
    for (int i = 0; i < MAX_CHILD; ++i)
        if (children[i]) delete children[i];
}

void TrieNode::insert(const string& word) {
    TrieNode* root = this;
    int cur;
    for (char c : word) {
        cur = c - MIN_CHAR;
        if (root->children[cur] == nullptr)
            root->children[cur] = new TrieNode();
        root = root->children[cur];
    }
    root->isWord = true;
}

bool TrieNode::search(const string& word) {
    TrieNode* root = this;
    int cur;
    for (char c : word) {
        cur = c - MIN_CHAR;
        if (root->children[cur] == nullptr) return false;
        root = root->children[cur];
    }

    return root->isWord;
}

bool TrieNode::startsWith(const string& prefix) {
    TrieNode* root;
    int cur;
    for (char c : prefix) {
        cur = c - MIN_CHAR;
        if (root->children[cur] == nullptr) return false;
        root = root->children[cur];
    }

    return true;
}
}   // namespace trie


namespace odt {
ChthollyTree::ChthollyTree() {}

set<ChthollyTree::ChthollyNode>::iterator ChthollyTree::split(ll pos) {
    auto it = tree.lower_bound(ChthollyNode(pos, 0, 0));
    if (it != tree.end() && it->l == pos) return it;

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
}   // namespace odt


namespace seg_tree {

void buildTree(const vector<int>& arr, Node* node, ll start, ll end) {
    if (start == end) {
        node->val = arr[start];
        return;
    }

    ll mid = start + (end - start) / 2;
    node->left = new Node();
    buildTree(arr, node->left, start, mid);
    node->right = new Node();
    buildTree(arr, node->right, mid + 1, end);
    // push up
    pushUp(node);
}

void pushUp(Node *const& node) {
    node->val = node->left->val + node->right->val;
}

void pushDown(Node *const& node, ll leftNum, ll rightNum) {
    if (node->left == nullptr) node->left = new Node();
    if (node->right == nullptr) node->right = new Node();

    if (node->add == 0) return;

    node->left->val += node->add * leftNum;
    node->right->val += node->add * rightNum;

    node->left->add += node->add;
    node->right->add += node->add;

    node->add = 0;
}

void update(Node* node, ll start, ll end, ll l, ll r, int val) {
    if (l <= start && end <= r) {
        node->val += (end - start + 1) * val;
        node->add += val;
        return;
    }

    ll mid = start + (end - start) / 2;
    pushDown(node, mid - start + 1, end - mid);
    if (l <= mid) update(node->left, start, mid, l, r, val);
    if (r > mid) update(node->right, mid + 1, end, l, r, val);
    pushUp(node);
    
}

int query(Node* node, ll start, ll end, ll l, ll r) {
    if (l <= start && end <= r) return node->val;
    ll mid = start + (end - start) / 2;
    int ans = 0;
    pushDown(node, mid - start + 1, end - mid);
    if (l <= mid) ans += query(node->left, start, mid, l, r);
    if (r > mid) ans += query(node->right, mid + 1, end, l, r);

    return ans;
}

} // namespace seg_tree
