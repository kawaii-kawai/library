#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_E"
#include "../../../template/template.hpp"
#include "../../../data-structure/lazy-segment-tree.hpp"
using namespace std;

using S = long long;
using F = long long;
S op(S a, S b) { return min(a, b); }
S e() { return (S)(2147483647); }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return (F)(0); }

int main() {
    int n, q;
    cin >> n >> q;
    LazySegmentTree<S, op, e, F, mapping, composition, id> seg(n, 0);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            seg.apply(l - 1, r, x);
        } else {
            int k;
            cin >> k;
            cout << seg.get(k - 1) << endl;
        }
    }
}