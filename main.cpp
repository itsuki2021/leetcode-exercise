#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] > target) r = mid - 1;
            else l = mid + 1;
        }

        return -1;
    }
};

int main() {
    vector<int> nums = {1,2,3,4,5,6,7,8,9};
    int target = 4;

    auto sol = new Solution();
    auto ans = sol->search(nums, target);

    cout << "Answer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    
    delete sol;
    return 0;
}