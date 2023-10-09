#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G"
#include "../../../template/template.hpp"
#include "../../../data-structure/lazy-segment-tree.hpp"
using namespace std;

struct S {
    long long val;
    int size;
};
using F = long long;

S op(S a, S b) { return {a.val + b.val, a.size + b.size}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return {x.val + x.size * f, x.size}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
    int n, q;
    cin >> n >> q;
    LazySegmentTree<S, op, e, F, mapping, composition, id> seg(n, {0, 1});
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            seg.apply(l - 1, r, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l - 1, r).val << endl;
        }
    }
}