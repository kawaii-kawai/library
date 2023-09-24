#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A"
#include "../../../template/template.hpp"
#include "../../../graph/kruskal.hpp"
using namespace std;
using namespace cp_library;
int main() {
    int v, e;
    cin >> v >> e;
    Edges<int> edges;
    for (int i = 0; i < e; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        edges.emplace_back(from, to, cost);
    }
    auto res = kruskal(edges, v);
    cout << res.cost << endl;
}