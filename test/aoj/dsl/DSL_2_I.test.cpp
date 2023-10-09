#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_I"
#include "../../../template/template.hpp"
#include "../../../data-structure/lazy-segment-tree.hpp"
using namespace std;

struct S {
    long long val;
    int size;
};
using F = long long;

// range update range sum
S op(S a, S b) { return {a.val + b.val, a.size + b.size}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return {x.size * f, x.size}; }
F composition(F f, F) { return f; }
F id() { return (1LL << 60); }

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
            seg.apply(l, r + 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r + 1).val << endl;
        }
    }
}