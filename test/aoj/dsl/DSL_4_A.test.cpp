#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_4_A"
#include "../../../other/compress.hpp"
#include "../../../other/cumulativesum2d.hpp"
#include "../../../template/template.hpp"
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<long long> x1(n), y1(n), x2(n), y2(n);
    for (int i = 0; i < n; i++) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }
    auto xs = compress2d(x1, x2, 0);
    auto ys = compress2d(y1, y2, 0);
    CumulativeSum2D<long long> cs((int)(xs.size()), (int)(ys.size()));
    for (int i = 0; i < n; i++) {
        cs.imos(x1[i], y1[i], x2[i], y2[i], 1);
    }

    cs.build();
    long long ans = 0;
    for (int i = 0; i < (int)(xs.size()) - 1; i++) {
        for (int j = 0; j < (int)(ys.size()) - 1; j++) {
            if (cs.imos_get(i, j))
                ans += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
        }
    }
    cout << ans << endl;
}