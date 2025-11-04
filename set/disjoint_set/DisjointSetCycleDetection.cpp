#include <iostream>
#include <vector>
#include <unordered_map>

template <typename T>
struct Edge {
    T from;
    T to;
};

template <typename T>
class UnionFind {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;

public:
    void add(const T& element) {
        if (!parent.contains(element)) {
            parent[element] = element;
            rank[element] = 0;
        }
    }

    T find(const T& i) {
        if (parent.at(i) == i) {
            return i;
        }
        return parent[i] = find(parent.at(i)); // Path Compression
    }

    // Simplified unite method that returns a boolean
    bool unite(const T& i, const T& j) {
        T root_i = find(i);
        T root_j = find(j);
        if (root_i != root_j) {
            if (rank.at(root_i) > rank.at(root_j)) {
                parent[root_j] = root_i;
            } else if (rank.at(root_i) < rank.at(root_j)) {
                parent[root_i] = root_j;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            return true; // A new union was formed
        }
        return false; // Already in the same set
    }
};

class Solution {
public:
    template <typename T>
    bool hasCycle(const std::vector<Edge<T>>& edges) {
        UnionFind<T> uf;
        for (const auto& edge : edges) {
            uf.add(edge.from);
            uf.add(edge.to);
            if (!uf.unite(edge.from, edge.to)) {
                return true; // Cycle detected
            }
        }
        return false;
    }
};

int main() {
    Solution solver;

    // Example 1: Undirected graph with a cycle
    std::vector<Edge<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    if (solver.hasCycle(edges1)) {
        std::cout << "Example 1: Cycle detected." << std::endl;
    } else {
        std::cout << "Example 1: No cycle detected." << std::endl;
    }

    // Example 2: Undirected graph with no cycle
    std::vector<Edge<std::string>> edges2 = {{"a", "b"}, {"a", "c"}, {"c", "d"}};
    if (solver.hasCycle(edges2)) {
        std::cout << "Example 2: Cycle detected." << std::endl;
    } else {
        std::cout << "Example 2: No cycle detected." << std::endl;
    }

    return 0;
}