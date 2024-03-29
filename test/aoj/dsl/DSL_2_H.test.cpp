#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H"
#include "../../../template/template.hpp"
#include "../../../data-structure/lazy-segment-tree.hpp"
using namespace std;

using S = long long;
using F = long long;

// range add, range min
S op(S a, S b) { return min(a, b); }
S e() { return 1LL << 31; }
S mapping(F f, S x) { return x + f; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

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
            seg.apply(l, r + 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r + 1) << endl;
        }
    }
}