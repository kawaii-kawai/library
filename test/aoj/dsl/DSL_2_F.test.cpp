#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_F"
#include "../../../data-structure/lazy-segment-tree.hpp"
#include "../../../template/template.hpp"
using namespace std;
using namespace cp_library;
int main() {
    int n, q;
    cin >> n >> q;
    UpdateMinLazySegmentTree<int> seg(n, 2147483647);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            seg.apply(l, r + 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r + 1) << endl;
        }
    }
}