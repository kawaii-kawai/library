#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_F"
#include "../../../template/template.hpp"
#include "../../../data-structure/lazy-segment-tree.hpp"
using namespace std;

using S = long long;
using F = long long;
S op(S a, S b) { return min(a, b); }
S e() { return (S)(2147483647); }
S mapping(F f, S) { return f; }
F composition(F f, F) { return f; }
F id() { return (F)(2147483647); }

int main() {
    int n, q;
    cin >> n >> q;
    LazySegmentTree<S, op, e, F, mapping, composition, id> seg(n);
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