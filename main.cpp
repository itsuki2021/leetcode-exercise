#include "utils.hpp"
#include "tree.h"
#include "graph.h"
#include "binary_search.hpp"
#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
private:
    vector<double> wts;
    vector<vector<int>> rects;
public:
    Solution(vector<vector<int>>& _rects) {
        rects.assign(_rects.begin(), _rects.end());
        double acc = 0.0;
        for (auto rect : rects) {
            double ai = rect[0], bi = rect[1], xi = rect[2], yi = rect[3];
            acc += (xi - ai + 1) * (yi - bi + 1);
            wts.push_back(acc);
        }

        for (int i = 0; i < wts.size(); ++i) wts[i] /= acc;
    }
    
    vector<int> pick() {
        double r = double(rand()) / double(RAND_MAX);
        for (int i = 0; i < wts.size(); ++i) {
            if (r <= wts[i]) {
                double ai = rects[i][0], bi = rects[i][1], xi = rects[i][2], yi = rects[i][3];
                int x = ai + double(rand()) / double(RAND_MAX) * (xi - ai);
                int y = bi + double(rand()) / double(RAND_MAX) * (yi - bi);
                return {x, y};
            }
        }

        return {0, 0};
    }
};


int main() {
    utils::RandReal ri(10.0, 100.0);
    for (int _ = 0; _ < 10; ++_)
        cout << ri.next() << endl;
    
    

    // auto sol = new Solution();
    // auto ans = sol->isBoomerang(points);

    // cout << "Answer is:\n";
    // cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    
    // delete sol;
    return 0;
}