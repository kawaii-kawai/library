#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A"
#include "../../../template/template.hpp"
#include "../../../graph/topological_sort.hpp"
using namespace std;
int main() {
    int v, e;
    cin >> v >> e;
    Graph<int> g(v);
    for (int i = 0; i < e; i++) {
        int from, to;
        cin >> from >> to;
        g.add_edge(from, to);
    }
    auto res = topological_sort(g);
    if (res.empty()) cout << 1 << endl;
    else cout << 0 << endl;
}