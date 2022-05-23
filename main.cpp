#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


class Solution {
public:
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int bfs(vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) return 0;
        int steps = 0, row = forest.size(), col = forest[0].size();
        queue<pair<int, int>> qu;
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        qu.emplace(sx, sy);
        visited[sx][sy] = true;
        while (!qu.empty()) {
            steps++;
            int sz = qu.size();
            for (int i = 0; i < sz; ++i) {
                auto [cx, cy] = qu.front();
                qu.pop();
                for (int j = 0; j < 4; ++j) {
                    int nx = cx + dirs[j][0];
                    int ny = cy + dirs[j][1];
                    if (nx < 0 || nx >= row || ny < 0 || ny >= col) continue;
                    if (visited[nx][ny] || forest[nx][ny] < 1) continue;
                    if (nx == tx && ny == ty) return steps;
                    qu.emplace(nx, ny);
                    visited[nx][ny] = true;
                }
            }
        }

        return -1;
    }

    int cutOffTree(vector<vector<int>>& forest) {
        vector<pair<int, int>> trees;
        int row = forest.size(), col = forest[0].size();
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (forest[i][j] > 1) trees.emplace_back(i, j);
            }
        }
        sort(trees.begin(), trees.end(),
            [&](const pair<int, int>& a, const pair<int, int>& b) {
                return forest[a.first][a.second] < forest[b.first][b.second];
            }
        );

        int cx = 0, cy = 0, ans = 0;
        for (int i = 0; i < trees.size(); ++i) {
            int steps = bfs(forest, cx, cy, trees[i].first, trees[i].second);
            if (steps == -1) return -1;

            ans += steps;
            cx = trees[i].first;
            cy = trees[i].second;
        }

        return ans;
    }
};

int main() {
    vector<vector<int>> forest = {
        {2,3,4},
        {0,0,5},
        {8,7,6},
    };

    auto sol = new Solution();
    auto ans = sol->cutOffTree(forest);

    cout << "Answer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    
    delete sol;
    return 0;
}