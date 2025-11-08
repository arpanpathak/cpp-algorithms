#include <vector>
#include <queue>
#include <limits>
#include <iostream>

struct Flow {
    struct Edge { int to; int rev; long long cap; };

    int n;
    std::vector<std::vector<Edge>> g;
    std::vector<int> lvl, ptr;

    Flow(int n,
         std::initializer_list<std::tuple<int,int,long long>> edges)
        : n(n), g(n), lvl(n), ptr(n)
    {
        for (auto &[u, v, c] : edges)
            add(u, v, c);
    }

    void add(int u, int v, long long c) {
        g[u].emplace_back(Edge{v, (int)g[v].size(), c});
        g[v].emplace_back(Edge{u, (int)g[u].size() - 1, 0});
    }

    bool bfs(int s, int t) {
        std::fill(lvl.begin(), lvl.end(), -1);
        lvl[s] = 0;
        std::queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u]) {
                if (e.cap > 0 && lvl[e.to] == -1) {
                    lvl[e.to] = lvl[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return lvl[t] != -1;
    }

    long long dfs(int u, int t, long long f) {
        if (u == t || f == 0) return f;

        for (int &i = ptr[u]; i < (int)g[u].size(); ++i) {
            auto &e = g[u][i];
            if (lvl[e.to] == lvl[u] + 1 && e.cap > 0) {
                long long pushed = dfs(e.to, t, std::min(f, e.cap));
                if (pushed) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long maxflow(int s, int t) {
        long long flow = 0, INF = std::numeric_limits<long long>::max();
        while (bfs(s, t)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, INF))
                flow += pushed;
        }
        return flow;
    }
};

int main() {
    Flow f{
        6,
        {
                {0,1,16}, {0,2,13}, {1,2,10}, {2,1,4},
                {1,3,12}, {3,2,9},  {2,4,14}, {4,3,7},
                {3,5,20}, {4,5,4}
        }
    };

    std::cout << f.maxflow(0, 5) << "\n";
}
