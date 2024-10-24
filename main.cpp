#include <algorithm>
#include <iostream>
#include <vector>

#include "tree.h"
#include "utils.hpp"

using namespace std;

class Solution {
  public:
    int argmax(const vector<int> &vec) {
        if (vec.empty()) {
            throw std::invalid_argument("Vector is empty");
        }

        int maxIndex = 0;
        for (size_t i = 1; i < vec.size(); ++i) {
            if (vec[i] > vec[maxIndex]) {
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    int findWinningPlayer(vector<int> &skills, int k) { return 0; }
};

int main() {
    vector<int> skills = {};
    int k = 10;

    auto sol = new Solution();
    auto ans = sol->findWinningPlayer(skills, k);
    cout << "\nAnswer is:\n";
    cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);
    delete sol;

    return 0;
}
