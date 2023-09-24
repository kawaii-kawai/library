#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A"
#include "../../../data-structure/segment-tree.hpp"
#include "../../../template/template.hpp"
using namespace std;
int main() {
    int n, q;
    cin >> n >> q;
    SegmentTree<Monoid::Min<int>> seg(n, 2147483647);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int k, x;
            cin >> k >> x;
            seg.set(k, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r + 1) << endl;
        }
    }
}