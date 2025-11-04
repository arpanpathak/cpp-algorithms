//
// Created by Arpan Pathak on 03/11/25.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template<typename T>
class Graph {
    // Data Structures used...
    int vertices;
    std::vector<vector<T>> adj;
    std::vector<vector<T>> revAdj;

    void fillOrder(T node, vector<bool>& visited, stack<T>& stk) {
        visited[node] = true;
        for (const auto& neighbor : adj[node]) {
            if (!visited[neighbor]) {
                fillOrder(neighbor, visited, stk);
            }
        }
        stk.push(node);
    }

    void dfs(T node, vector<bool>& visited, vector<T>& component) {
        visited[node] = true;
        component.push_back(node);
        for (const auto& neighbor : revAdj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, component);
            }
        }
    }

public:
    Graph(int V) : vertices(V), adj(V), revAdj(V) {}

    void addEdge(T u, T v) {
        adj[u].push_back(v);
        revAdj[v].push_back(u);
    }

    vector<vector<T>> getSCCs() {
        vector<bool> visited(vertices, false);
        stack<T> stk;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                fillOrder(i, visited, stk);
            }
        }

        // Reset the visited array to re-use for the next round of Depth First Search Algorithm Exeution...
        fill(visited.begin(), visited.end(), false);
        vector<vector<T>> sccs;

        while (!stk.empty()) {
            T node = stk.top();
            stk.pop();

            if (!visited[node]) {
                vector<T> component;
                dfs(node, visited, component);
                sccs.push_back(component);
            }
        }
        return sccs;
    }
};

int main() {
    Graph<int> g(5);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    vector<vector<int>> sccs = g.getSCCs();

    cout << "Strongly Connected Components:\n";
    for (const auto& component : sccs) {
        for (int node : component) {
            cout << node << " ";
        }
        cout << "\n";
    }

    return 0;
}

/**
 * The above code is not so extensible for any data type, especially if we wanna store
 *
 */