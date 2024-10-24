#include <algorithm>
#include <iostream>
#include <vector>

#include "tree.h"
#include "utils.hpp"

using namespace std;

class Solution {
  public:
    int findWinningPlayer(vector<int> &skills, int k) {
        int n = skills.size();
        int curPlayer = 0;   // 当前赢家玩家的编号
        int curWinCount = 0; // 当前赢家的连胜次数

        // 技能值最大玩家的编号（因为技能唯一，最大玩家一定会成为赢家）
        int maxSkillIndex =
            max_element(skills.begin(), skills.end()) - skills.begin();

        for (int i = 1; i < n; ++i) {
            // 如果当前玩家胜出
            if (skills[curPlayer] > skills[i]) {
                curWinCount++; // 连胜次数增加
            } else {
                // 如果新的玩家胜出
                curPlayer = i;
                curWinCount = 1; // 重置连胜次数为1
            }

            // 如果连胜次数达到k，返回当前赢家
            if (curWinCount == k)
                return curPlayer;

            // 如果当前玩家是技能值最大的玩家，且技能值最大玩家已经连胜了 k
            // 场或更多
            if (curPlayer == maxSkillIndex)
                return curPlayer;
        }

        // 如果k足够大，那么最后的赢家一定是技能最大的玩家
        return maxSkillIndex;
    }
};

int main() {
    vector<int> skills = {4, 2, 6, 3, 9};
    int k = 2;

    auto sol = new Solution();
    auto ans = sol->findWinningPlayer(skills, k);
    cout << "\nAnswer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    delete sol;

    return 0;
}
