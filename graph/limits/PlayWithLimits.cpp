#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

constexpr int INF = std::numeric_limits<int>::max();

// Define a struct for a graph edge
struct Edge {
    int to;
    int weight;

    // Operator overload for the priority queue
    // This makes the priority queue behave as a min-heap
    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

// Function to perform Dijkstra's algorithm and return distances and parents
std::pair<std::vector<int>, std::vector<int>> dijkstra(const int start_node, int num_vertices, const std::vector<std::vector<Edge>>& adj) {
    std::vector<int> dist(num_vertices, INF);
    std::vector<int> parent(num_vertices, -1); // Parent array to reconstruct the path
    std::priority_queue<Edge> pq;

    dist[start_node] = 0;
    pq.push({start_node, 0});

    while (!pq.empty()) {
        auto [u, current_dist] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) {
            continue;
        }

        for (const auto& edge : adj[u]) {
            auto [v, weight] = edge;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u; // Update the parent
                pq.push({v, dist[v]});
            }
        }
    }
    return {dist, parent};
}

// Function to reconstruct and print the path
std::vector<int> get_path(int target_node, const std::vector<int>& parent) {
    std::vector<int> path;
    if (parent[target_node] == -1 && target_node != 0) {
        // Not reachable
        return path;
    }
    
    for (int curr = target_node; curr != -1; curr = parent[curr]) {
        path.push_back(curr);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// Function to print the calculated distances and paths
void print_results(int start_node, const std::vector<int>& dist, const std::vector<int>& parent) {
    std::cout << "Shortest distances and paths from source node " << start_node << ":" << std::endl;
    for (int i = 0; i < dist.size(); ++i) {
        std::cout << "Node " << i << ": ";
        if (dist[i] == INF) {
            std::cout << "Unreachable" << std::endl;
        } else {
            std::cout << "Distance = " << dist[i] << ", Path = ";
            std::vector<int> path = get_path(i, parent);
            for (int j = 0; j < path.size(); ++j) {
                std::cout << path[j] << (j == path.size() - 1 ? "" : " -> ");
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    constexpr int num_vertices = 5;
    std::vector<std::vector<Edge>> adj(num_vertices);

    // Graph edges: {from, to, weight}
    adj[0].push_back({1, 10});
    adj[0].push_back({2, 5});
    adj[1].push_back({2, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({1, 3});
    adj[2].push_back({3, 9});
    adj[2].push_back({4, 2});
    adj[3].push_back({4, 4});
    adj[4].push_back({3, 6});

    auto [distances, parents] = dijkstra(0, num_vertices, adj);
    print_results(0, distances, parents);

    return 0;
}