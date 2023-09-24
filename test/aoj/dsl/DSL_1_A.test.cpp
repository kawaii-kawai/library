#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_A"
#include "../../../data-structure/unionfind.hpp"
#include "../../../template/template.hpp"
using namespace std;
int main() {
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v;
            cin >> u >> v;
            uf.merge(u, v);
        } else {
            int u, v;
            cin >> u >> v;
            if (uf.same(u, v))
                cout << 1 << endl;
            else
                cout << 0 << endl;
        }
    }
}
