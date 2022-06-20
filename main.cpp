#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include "binary_search.hpp"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;


class ChthollyTree {
using ll = long long;
private:    
    struct ChthollyNode {
        ll l, r;
        mutable ll v;
        ChthollyNode(ll l_, ll r_, ll v_) : l(l_), r(r_), v(v_) {}
        bool operator<(const ChthollyNode &other) const { return l < other.l; }
    };

    set<ChthollyNode> tree;

public:
    ChthollyTree() {}
    set<ChthollyNode>::iterator split(ll pos) {
        auto it = tree.lower_bound(ChthollyNode(pos, 0, 0));
        if (it != tree.end() && it->l == pos) return it;

        it--;
        ll l = it->l, r = it->r, v = it->v;
        tree.erase(it);
        tree.insert(ChthollyNode(l, pos - 1, v));
        return tree.insert(ChthollyNode(pos, r, v)).first;
    }

    void assign(ll l, ll r, ll v) {
        auto end = split(r + 1), begin = split(l);
        tree.erase(begin, end);
        tree.insert(ChthollyNode(l, r, v));
    }

    bool check(ll l, ll r) {
        auto end = split(r + 1), begin = split(l);
        while (begin != end) if (begin->v == 0) return false;

        return true;
    }

    void insert(ll l, ll r, ll v) {
        tree.insert(ChthollyNode(l, r, v));
    }

};


class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int max = INT32_MAX;

        int n = arr.size(), cnt = 0;
        for (auto v : arr) cnt += (v == 0);
        for (int i = n - 1; i >= 0; --i) {
            if (arr[i] == 0) cnt--;

            int j = i + cnt;
            if (j < n) arr[j] = arr[i];
            if (arr[i] == 0 && j + 1 < n) arr[j + 1] = 0;
        }
    }
};


int main() {
    vector<int> arr = {1,0,2,3,0,4,5,0};

    auto sol = new Solution();
    // auto ans = sol->duplicateZeros(arr);
    sol->duplicateZeros(arr);

    cout << "Answer is:\n";
    utils::printVec1D(arr);
    // cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    
    delete sol;
    return 0;
}