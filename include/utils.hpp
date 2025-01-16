#pragma once
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace utils {

// 打印一维 vector
template <typename T> void printVector(const std::vector<T> &vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// 打印二维 vector
template <typename T>
void print2DVector(const std::vector<std::vector<T>> &vec2D) {
    for (const auto &row : vec2D) {
        std::cout << "  ";
        printVector(row);
    }
}

// 生成指定范围内的随机整数
int generateRandomInt(int min, int max, unsigned int seed = 0) {
    if (seed == 0) {
        std::random_device rd; // 用于获取随机种子
        seed = rd();
    }
    std::mt19937 gen(seed); // 使用固定的或随机种子
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// 生成指定范围内的随机浮点数
double generateRandomDouble(double min, double max, unsigned int seed = 0) {
    if (seed == 0) {
        std::random_device rd; // 用于获取随机种子
        seed = rd();
    }
    std::mt19937 gen(seed); // 使用固定的或随机种子
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

} // namespace utils
