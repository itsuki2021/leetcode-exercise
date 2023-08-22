#include <iostream>
#include <algorithm>
#include <stack>

#include "utils.hpp"
#include "tree.h"

using namespace std;
using bin_tree::NULL_NODE;
using bin_tree::TreeNode;

class Solution {
public:
  vector<vector<int>> ans;
  vector<int> path;
  vector<bool> visited;
  void backTracking(const vector<int> &cdd, const int &target, int sum, int i) {
    if (sum >= target) {
      if (sum == target) ans.push_back(path);
      return;
    }

    for (; i < cdd.size(); ++i) {
      if (i > 0 && cdd[i] == cdd[i - 1] && visited[i - 1] == false)
        continue;
      visited[i] = true;
      path.push_back(cdd[i]);
      backTracking(cdd, target, sum + cdd[i], i + 1);
      visited[i] = false;
      path.pop_back();
    }
  }


  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    ans.clear();
    path.clear();
    visited = vector<bool>(candidates.size(), false);
    sort(candidates.begin(), candidates.end());

    backTracking(candidates, target, 0, 0);
    return ans;
  }
};

int main() {
  vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
  int target = 8;

  auto sol = new Solution();
  auto ans = sol->combinationSum2(candidates, target);
  cout << "\nAnswer is:\n";
  // cout << ans << endl;
  // utils::printVec1D(ans);
  utils::printVec2D(ans);
  delete sol;

  return 0;
}