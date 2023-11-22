#include <algorithm>
#include <iostream>
#include <stack>

#include "tree.h"
#include "utils.hpp"

using namespace std;

class Solution {
  public:
    using Vec1D = vector<bool>;
    using Vec2D = vector<Vec1D>;

    int countSubstrings(string s) {
        int n = s.size();
        Vec2D dp(n, Vec1D(n));
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
            ans += 1;
        }

        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                if (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    ans += 1;
                }
            }
        }

        return ans;
    }
};

int main() {
    string s = "abc";

    auto sol = new Solution();
    auto ans = sol->countSubstrings(s);
    cout << "\nAnswer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    delete sol;

    return 0;
}
