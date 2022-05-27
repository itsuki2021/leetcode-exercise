#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>

namespace utils {
    using std::cout;
    using std::endl;
    using std::vector;
    using std::string;
    
    /**
     * @brief Print 1-dimensional vector.
     * 
     * @tparam _Tp      Type of vector element
     * @param vec       Input 1D vector
     * @param prefix    prefix string
     * @param suffix    suffix string
     */
    template<typename _Tp>
    void printVec1D(const vector<_Tp>& vec, string prefix="[", string suffix="]\n") {
        cout << prefix;
        if (vec.empty()) {
            cout << suffix;
            return;
        }
        
        for (auto v : vec) cout << v << ", ";
        cout << "\b\b" << suffix;
    }

    /**
     * @brief Print 2-dimensional vector.
     * 
     * @tparam _Tp  Type of vector element.
     * @param vec   Input 2D vector
     */
    template<typename _Tp>
    void printVec2D(const vector<vector<_Tp>>& vec) {
        cout << "[\n";
        for (auto vc : vec) printVec1D<_Tp>(vc, "  [", "],\n");
        cout << "]\n";
    }

    float frand(float low, float high, unsigned int seed = static_cast<unsigned>(time(0))) {
        float r = low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high-low)));
        return r;
    }
}