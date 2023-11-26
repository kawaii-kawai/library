#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_C"
#include "../../../template/template.hpp"
#include "../../../graph/lowestcommonancestor.hpp"
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int c;
            cin >> c;
            graph[i].push_back(c);
        }
    }
    LowestCommonAncestor lca(graph, 0);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int ans = lca.query(u, v);
        cout << ans << endl;
    }
}