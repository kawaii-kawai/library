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
    Compress<long long> xs, ys;
    for (int i = 0; i < n; i++) {
        xs.add(x1[i]);
        xs.add(x2[i]);
        ys.add(y1[i]);
        ys.add(y2[i]);
    }   
    xs.build();
    ys.build();
    CumulativeSum2D<long long> cs(xs.size(), ys.size());
    for (int i = 0; i < n; i++) {
        x1[i] = xs.get(x1[i]);
        x2[i] = xs.get(x2[i]);
        y1[i] = ys.get(y1[i]);
        y2[i] = ys.get(y2[i]);
    }
    for (int i = 0; i < n; i++) {
        cs.imos(x1[i], y1[i], x2[i], y2[i], 1);
    }
    cs.build();
    long long ans = 0;
    for (int i = 0; i < xs.size() - 1; i++) {
        for (int j = 0; j < ys.size() - 1; j++) {
            if (cs.imos_get(i, j)) {
                ans += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
            }
        }
    }
    cout << ans << endl;
}