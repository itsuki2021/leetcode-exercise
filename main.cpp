#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
  public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals) {
        sort(intervals.begin(), intervals.end(),
             [](vector<int> &a, vector<int> &b) { return a[1] < b[1]; });

        int ans = 0;
        int last_end = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= last_end) {
                last_end = intervals[i][1];
            } else {
                ans++;
            }
        }

        return ans;
    }
};

int main() {
    int n = 10;
    int MIN_VALUE = -5e4, MAX_VALUE = 5e4;
    int seed = 2025;
    vector<vector<int>> intervals;
    for (int i = 0; i < n; i++) {
        vector<int> interval;
        interval.push_back(
            utils::generateRandomInt(MIN_VALUE, MAX_VALUE, seed++));
        interval.push_back(
            utils::generateRandomInt(interval[0], MAX_VALUE, seed++));
        intervals.push_back(interval);
    }
    cout << "\nInput:\n";
    utils::print2DVector(intervals);

    auto sol = new Solution();
    auto ans = sol->eraseOverlapIntervals(intervals);

    cout << "\nAnswer is:\n";
    cout << ans << endl;
    // utils::printVector(ans);
    // utils::print2DVector(ans);
    delete sol;

    return 0;
}
