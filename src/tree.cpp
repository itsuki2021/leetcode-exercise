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
            auto val = st.top();
            st.pop();
            if (val.second == nullptr) continue;
            
            if (!val.first) {
                st.push({false, val.second->right});
                st.push({false, val.second->left});
                st.push({true, val.second});
            } else {
                ret.push_back(val.second);
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
            auto val = st.top();
            st.pop();
            if (val.second == nullptr) continue;
            
            if (!val.first) {
                st.push({false, val.second->right});
                st.push({true, val.second});
                st.push({false, val.second->left});
            } else {
                ret.push_back(val.second);
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
            auto val = st.top();
            st.pop();
            if (val.second == nullptr) continue;
            
            if (!val.first) {
                st.push({true, val.second});
                st.push({false, val.second->right});
                st.push({false, val.second->left});
            } else {
                ret.push_back(val.second);
            }
        }

        return ret;
    }

    TreeNode* buildTree(const vector<int>& nums) {
        if (nums.empty()) return nullptr;
        
        deque<TreeNode*> list = {new TreeNode(nums[0])};
        TreeNode* root = list.front();
        TreeNode* curNode = nullptr;
        TreeNode* newNode = nullptr;
        int i = 1;
        while (!list.empty()) {
            curNode = list.front();
            list.pop_front();
            if (curNode == nullptr) {
                // assert both left and right node is nullptr
                for (int _cnt = 0; _cnt < 2; ++_cnt) {
                    if (i >= nums.size()) break;
                    if (nums[i] != NULL_NODE) throw NodeException();
                    list.push_back(nullptr);
                    i++;
                }
            }
            else {
                if (i >= nums.size()) break;
                newNode = nums[i] == NULL_NODE ? nullptr : new TreeNode(nums[i]);
                curNode->left = newNode;
                list.push_back(newNode);
                i++;

                if (i >= nums.size()) break;
                newNode = nums[i] == NULL_NODE ? nullptr : new TreeNode(nums[i]);
                curNode->right = newNode;
                list.push_back(newNode);
                i++;
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

    void printTree(TreeNode* const root) {
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
}


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
}