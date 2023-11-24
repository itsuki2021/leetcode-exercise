#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#include "tree.h"
#include "utils.hpp"

using namespace std;

// leetcode 42
class Solution {
  public:
    int trap(vector<int> &height) {
        stack<int> st;
        int ans = 0;
        for (int i = 0; i < height.size(); ++i) {
            if (!st.empty() && height[i] >= height[st.top()]) {
                int bottom = 0;
                while (!st.empty()) {
                    ans += (min(height[i], height[st.top()]) - bottom) *
                           (i - st.top() - 1);
                    bottom = min(height[i], height[st.top()]);
                    if (height[i] < height[st.top()])
                        break;
                    st.pop();
                }
            }
            st.push(i);
        }

        return ans;
    }
};

int main() {
    // vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    vector<int> height = {4, 2, 0, 3, 2, 5};

    auto sol = new Solution();
    auto ans = sol->trap(height);
    cout << "\nAnswer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    delete sol;

    return 0;
}
