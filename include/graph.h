#pragma once
#include <vector>

namespace graph {
using std::vector;

/**
 * @brief dijkstra algorithm for shortest route problem.
 *
 * @param graph         Adjacency graph
 * @param s             Index of source vertex
 * @return vector<int>  The shortest route
 */
vector<int> dijkstra(const vector<vector<int>> &graph, int s);

}
