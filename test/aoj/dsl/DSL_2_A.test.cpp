#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"
#include "../../../template/template.hpp"
#include "../../../data-structure/segment-tree.hpp"
using namespace std;

using S = long long;
S op(S a, S b) { return std::min(a, b); }
S e() { return 2147483647; }

int main() {
    int n, q;
    cin >> n >> q;
    SegmentTree<S, op, e> seg(n);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int i, x;
            cin >> i >> x;
            seg.set(i, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r + 1) << endl;
        }
    }
}