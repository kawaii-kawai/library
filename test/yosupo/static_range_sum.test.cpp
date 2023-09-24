#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#include "../../template/template.hpp"
#include "../../other/cumulativesum.hpp"
using namespace std;
using namespace cp_library;
int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    CumulativeSum<long long> cs(a);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << cs.prod(l, r) << endl;
    }
}