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
 * @brief Find the first element(index) not less than target 
 *        or -1 if every element is less than target.
 * 
 * @param nums      sorted array.
 * @param target    target number.
 * @return int      index.
 */
int search_lower(const vector<int> nums, int target) {
    int l = 0, r = nums.size() - 1, ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] >= target) {
            r = mid - 1;
            ans = mid;
        } else l = mid + 1;
    }

    return ans;
}

/**
 * @brief Find the last element(index) not more than target
 *        or -1 if every element is more than target.
 * 
 * @param nums      sorted array.
 * @param target    target number.
 * @return int      index.
 */
int search_upper(const vector<int> nums, int target) {
    int l = 0, r = nums.size() - 1, ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] <= target) {
            l = mid + 1;
            ans = mid;
        } else r = mid - 1;
    }

    return ans;
}

}   // namespace bin_search