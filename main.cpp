#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include "binary_search.hpp"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;


class Solution {
public:
    string defangIPaddr(string address) {
        string ans;
        for (char ch : address)
            if (ch == '.') ans += "[.]";
            else ans += ch;

        return ans;
    }
};


int main() {
    string address = "1.1.1.1";

    auto sol = new Solution();
    auto ans = sol->defangIPaddr(address);

    cout << "Answer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    
    delete sol;
    return 0;
}