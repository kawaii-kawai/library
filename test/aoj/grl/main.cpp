#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A"
#include "../../../template/template.hpp"
#include "../../../graph/dijkstra.hpp"
using namespace std;
using namespace cp_library;
int main() {
    int v, e, s;
    cin >> v >> e >> s;
    Graph<int> g(v);
    for (int i = 0; i < e; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        g.add_edge(from, to, cost);
    }
    auto res = dijkstra(g, s);
    for (int i = 0; i < v; i++) {
        if (res.dist[i] == numeric_limits<int>::max()) {
            cout << "INF" << endl;
        } else {
            cout << res.dist[i] << endl;
        }
    }
}