//
// Created by Arpan Pathak on 06/11/25.
//

#include <iostream>
#include <vector>
#include <queue>

// Containers that am goona use
using std::vector;
using std::queue;

class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n), result(n);

        // Build graph
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }

        for (int i = 0; i < n; i++) {
            vector<bool> visited(n, false);
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                const int curr = q.front(); q.pop();

                for (int neighbor : graph[curr]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        result[neighbor].push_back(i);
                        q.push(neighbor);
                    }
                }
            }
        }

        return result;
    }
};