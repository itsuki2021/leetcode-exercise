#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <bitset>
#include <climits>

namespace utils {
    using std::cout;
    using std::endl;
    using std::vector;
    using std::string;
    using std::bitset;
    using std::uniform_int_distribution;
    using std::uniform_real_distribution;
    using std::default_random_engine;
    using std::mt19937;
    using std::random_device;
    
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

    inline void printBin(int x) {
        cout << bitset<sizeof(x) * 8>(x) << endl;
        
    }

    inline void printHex(int x) {
        cout << std::hex << x << endl;
    }

    template<typename _Tp = int>
    class RandInt {
    private:
        uniform_int_distribution<_Tp>* dis = nullptr;
        mt19937 gen{random_device{}()};
    public:
        RandInt() { dis = new uniform_int_distribution(0, 1); }
        RandInt(_Tp low, _Tp high) { dis = new uniform_int_distribution(low, high); }
        ~RandInt() { delete dis; }

        _Tp next() { return (*dis)(gen); }
    };

    template<typename _Tp = double>
    class RandReal {
    private:
        uniform_real_distribution<_Tp>* dis = nullptr;
        mt19937 gen{random_device{}()};
    public:
        RandReal() { dis = new uniform_real_distribution(0.0, 1.0);}
        RandReal(_Tp low, _Tp high) { dis = new uniform_real_distribution(low, high); }
        ~RandReal() { delete dis; }

        _Tp next() { return (*dis)(gen); }
    };

}