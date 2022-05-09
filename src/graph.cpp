#include "graph.h"
#include <iostream>
#include <assert.h>

namespace graph {
    using std::min;

    vector<int> dijkstra(const vector<vector<int>>& graph, int s) {
        // dijkstra can't deal with negative weights
        for (auto row : graph)
            for (auto dist : row)
                assert(dist >= 0);

        int n = graph.size();
        vector<bool> S(n, false);   // source vertex set
        vector<int> distTo(n);      // distance from vertex s to vertex i
        for (int i = 0; i < n; ++i) distTo[i] = graph[s][i];
        S[s] = true;
        int verNum = n - 1, j;

        while (verNum) {
            int minDist = INT32_MAX, j = -1;
            // find closest vertex j to vertex s
            for (int i = 0; i < n; ++i) {
                if (S[i] || distTo[i] == -1) continue;
                if (distTo[i] <= minDist) {
                    minDist = distTo[i];
                    j = i;
                }
            }

            // move vertex j to S
            if (j == -1) break; // can not find closest vertex j
            S[j] = true;
            verNum--;

            // update distTo
            for (int i = 0; i < n; ++i) {
                if (S[i] || graph[j][i] == -1) continue;
                distTo[i] = min(distTo[i] == -1 ? INT32_MAX : distTo[i], distTo[j] + graph[j][i]);
            }
        }

        return distTo;
    }
}