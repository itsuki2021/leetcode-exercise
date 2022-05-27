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
        if (target < nums[0] || target > nums[n-1]) return -1;

        int le = 0, ri = n - 1;
        while (le <= ri) {
            int mid = le + (ri - le) / 2;
            if (nums[mid] > target) ri = mid - 1;
            else if (nums[mid] < target) le = mid + 1;
            else return mid;
        }

        return -1;
    }

    /**
     * @brief Binary search.
     * 
     * @param nums      sorted array.
     * @param target    target number.
     * @param lower     find last element lower than target
     * @return int      target index.
     */
    int search(const vector<int>& nums, int target, bool lower) {
        int left = 0, right = (int)nums.size() - 1, ans = (int)nums.size();
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

}