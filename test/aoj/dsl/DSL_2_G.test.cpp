#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_G"
#include "../../../data-structure/lazy-segment-tree.hpp"
#include "../../../template/template.hpp"
using namespace std;
int main() {
    int n, q;
    cin >> n >> q;
    AddSumLazySegmentTree<long long> seg(n, 0);
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