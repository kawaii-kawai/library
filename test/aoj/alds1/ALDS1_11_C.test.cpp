#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_11_C"
#include "../../../graph/bfs.hpp"
#include "../../../template/template.hpp"
using namespace std;
int main() {
    int n;
    cin >> n;
    Graph<int> g(n);
    for (int i = 0; i < n; i++) {
        int u, k;
        cin >> u >> k;
        u--;
        for (int j = 0; j < k; j++) {
            int v;
            cin >> v;
            v--;
            g.add_edge(u, v);
        }
    }
    auto dist = bfs(g, 0);
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " "
             << (dist[i] == numeric_limits<int>::max() ? -1 : dist[i]) << endl;
    }
}