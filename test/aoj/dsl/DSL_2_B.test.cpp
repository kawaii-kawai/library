#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B"
#include "../../../data-structure/segment-tree.hpp"
#include "../../../template/template.hpp"
using namespace std;
int main() {
    int n, q;
    cin >> n >> q;
    SegmentTree<Monoid::Sum<int>> seg(n, 0);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int k, x;
            cin >> k >> x;
            k--;
            seg.set(k, seg.get(k) + x);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << seg.prod(l, r + 1) << endl;
        }
    }
}