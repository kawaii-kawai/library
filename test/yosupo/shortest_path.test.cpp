#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "../../template/template.hpp"
#include "../../graph/dijkstra.hpp"
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    Graph<ll> g(n);
    for (int i = 0; i < m; i++) {
        int from, to;
        ll cost;
        cin >> from >> to >> cost;
        g.add_edge(from, to, cost);
    }
    auto res = dijkstra(g, s);
    if (res.dist[t] == numeric_limits<ll>::max()) {
        cout << -1 << endl;
    } else {
        cout << res.dist[t] << ' ';
        vector<pair<int, int>> edges;
        while (s != t) {
            edges.emplace_back(res.from[t], t);
            t = res.from[t];
        }
        cout << edges.size() << endl;
        reverse(edges.begin(), edges.end());
        for (auto e : edges) {
            cout << e.first << ' ' << e.second << endl;
        }
    }
}