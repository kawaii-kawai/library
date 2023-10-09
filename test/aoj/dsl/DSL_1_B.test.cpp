#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B"
#include "../../../template/template.hpp"
#include "../../../data-structure/potentialized-unionfind.hpp"
using namespace std;

int op(int a, int b) { return a + b; }
int e() { return 0; }
int inv(int a) { return -a; }

int main() {
    int n, q;
    cin >> n >> q;
    PotentializedUnionFind<int, op, e, inv> uf(n);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int x, y, z;
            cin >> x >> y >> z;
            uf.merge(x, y, z);
        } else {
            int x, y;
            cin >> x >> y;
            if (uf.same(x, y)) {
                cout << uf.diff(x, y) << endl;
            } else {
                cout << "?" << endl;
            }
        }
    }
}