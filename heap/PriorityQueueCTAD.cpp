//
// Created by Arpan Pathak on 25/10/25.
//

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::priority_queue;
using std::vector;
using std::cout;

template <class ValueType, class WeightType>
struct Edge {
    ValueType to;
    WeightType weight;

    Edge(ValueType v, WeightType w) : to(v), weight(w) {}
};

template <class ValueType, class WeightType>
struct QueueNode {
    ValueType vertex;
    WeightType weight;

    QueueNode(ValueType v, WeightType w) : vertex(v), weight(w) {}
};

template <class ValueType, class WeightType>
struct SpanningTree {
    vector<Edge<ValueType, WeightType>> edges;
    WeightType total_weight = 0;
};

template <class ValueType, class WeightType>
class Graph {
private:
    std::unordered_map<ValueType, vector<Edge<ValueType, WeightType>>> adj;

public:
    Graph(std::initializer_list<std::tuple<ValueType, ValueType, WeightType>> edges) {
        for (const auto& [u, v, w] : edges) {
            add_edge(u, v, w);
        }
    }

    void add_edge(ValueType u, ValueType v, WeightType w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    SpanningTree<ValueType, WeightType> prim_mst(ValueType start_vertex) {
        SpanningTree<ValueType, WeightType> result;
        std::unordered_set<ValueType> visited;

        // priority_queue pq(
        //     [](const auto& a, const auto& b) { return a.weight > b.weight; },
        //     vector<QueueNode<ValueType, WeightType>>{}
        // );
        auto comparator = [](const auto& a, const auto& b) { return a.weight > b.weight;  };

        priority_queue<QueueNode<ValueType, WeightType>, vector<QueueNode<ValueType, WeightType>, decltype(comparator)> pq(comparator);


        pq.push({start_vertex, 0});

        while (!pq.empty()) {
            auto current = pq.top();
            pq.pop();

            if (visited.count(current.vertex)) continue;

            visited.insert(current.vertex);

            if (current.vertex != start_vertex) {
                result.edges.emplace_back(current.vertex, current.weight);
                result.total_weight += current.weight;
            }

            for (const auto& edge : adj[current.vertex]) {
                if (!visited.count(edge.to)) {
                    pq.push({edge.to, edge.weight});
                }
            }
        }

        return result;
    }
};

template <class ValueType, class WeightType>
void print_spanning_tree(const SpanningTree<ValueType, WeightType>& result) {
    cout << "Spanning Tree Edges:\n";
    for (const auto& edge : result.edges) {
        cout << "  -- " << edge.to << " : " << edge.weight << "\n";
    }
    cout << "Total weight: " << result.total_weight << "\n\n";
}

int main() {
    Graph<int, double> graph {
        {0, 1, 4.0},
        {0, 2, 3.5},
        {1, 2, 2.0},
        {1, 3, 5.0},
        {2, 3, 7.0}
    };

    auto spanning_tree = graph.prim_mst(0);
    print_spanning_tree(spanning_tree);

    return 0;
}
