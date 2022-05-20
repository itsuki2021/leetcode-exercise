#pragma once
#include <vector>

namespace bin_search {
    using std::vector;

    /**
     * @brief Binary search.
     * 
     * @param nums      sorted array with unique element.
     * @param target    target number.
     * @return int      -1 if not found else target index.
     */
    int search(const vector<int>& nums, int target) {
        int n = nums.size();
        int le = 0, ri = n - 1;
        while (le <= ri) {
            int mid = le + (ri - le) / 2;
            if (nums[mid] > target) ri = mid - 1;
            else if (nums[mid] < target) le = mid + 1;
            else return mid;
        }

        return -1;
    }



}