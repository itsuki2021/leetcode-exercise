#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include "binary_search.hpp"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;


class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                int l = 0, r = j - 1;
                while (l < r) {
                    int mid = (l + r) / 2;
                    if (nums[mid] > nums[i] - nums[j]) r = mid;
                    else l = mid + 1;
                }

                if (l == r && nums[r] + nums[j] > nums[i]) ans += j - r;
            }
        }

        return ans;
    }
};


int main() {
    // 3
    vector<int> nums = {2,2,3,4};

    auto sol = new Solution();
    auto ans = sol->triangleNumber(nums);

    cout << "Answer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    
    // delete sol;
   
    return 0;
}