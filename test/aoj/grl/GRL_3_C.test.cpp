#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C"
#include "../../../template/template.hpp"
#include "../../../graph/strongly-connect-components.hpp"
using namespace std;
int main() {
    int V, E;
    cin >> V >> E;
    Graph<int> g(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        g.add_edge(s, t);
    }
    StronglyConnectedComponents<int> scc(g);
    int Q;
    cin >> Q;
    while (Q--) {
        int u, v;
        cin >> u >> v;
        cout << scc.same(u, v) << endl;
    }
    return 0;
}