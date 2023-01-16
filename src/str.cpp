/**
 * @file str.cpp
 * @author your name (you@domain.com)
 * @brief KMP algorithm
 *          https://www.zhihu.com/question/21923021/answer/1032665486
 *          https://programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html
 * @version 0.1
 * @date 2023-01-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "str.h"

namespace kmp {


int KMP::search(const string& haystack, const string& needle) {
    if (needle.size() == 0) return 0;

    vector<int> next = getNext(needle);
    int j = -1;
    for (int i = 0; i < haystack.size(); ++i) {
        while (j >= 0 && haystack[i] != needle[j + 1]) j = next[j];
        if (haystack[i] == needle[j + 1]) ++j;

        if (j == (needle.size() - 1)) return i - needle.size() + 1;
    }

    return -1;
}

vector<int> KMP::getNext(const string s) {
    vector<int> next(s.size());
    int j = -1;
    next[0] = j;
    for (int i = 1; i < s.size(); ++i) {
        while (j >= 0 && s[i] != s[j + 1]) j = next[j];
        if (s[i] == s[j + 1]) ++j;

        next[i] = j;
    }

    return next;
}

};  // namespace kmp
