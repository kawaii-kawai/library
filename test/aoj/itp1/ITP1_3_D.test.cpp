#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_3_D"
#include "../../../template/template.hpp"
#include "../../../math/divisor.hpp"
using namespace std;
int main() {
    int a, b, c;
    cin >> a >> b >> c;
    auto res = divisor(c);
    int ans = 0;
    for (auto &p : res) {
        if (a <= p && p <= b) ans++;
    }
    cout << ans << endl;
}