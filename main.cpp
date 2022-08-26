#include "utils.hpp"
#include "sort.h"
#include <iostream>
#include <algorithm>


using namespace std;


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        return (nums[n-1] - 1) * (nums[n-2] - 1);
    }
};


int main() {
    // vector<int> nums = {3, 4, 5, 2};

    // auto sol = new Solution();
    // auto ans = sol->maxProduct(nums);

    // cout << "Answer is:\n";
    // cout << ans << endl;
    // // utils::printVec1D(ans);
    // // utils::printVec2D(ans);
    
    // delete sol;

    vector<int> arr = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    my_sort::quickSort(arr);
    utils::printVec1D(arr);

    return 0;
}