#pragma once

#include <string>
#include <vector>

namespace kmp {

using std::string;
using std::vector;

class KMP {
public:
  static int search(const string &haystack, const string &needle);

private:
  static vector<int> getNext(const string s);
};

}; // namespace kmp