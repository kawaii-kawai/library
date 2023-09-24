#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_C"
#include "../../../template/template.hpp"
#include "../../../math/binomial.hpp"
#include "../../../math/modint.hpp"
using namespace std;
using namespace cp_library;
using mint = modint1000000007;
using comb = Binomial<mint>;
int main() {
    ll n, k;
    cin >> n >> k;
    mint ans = 0;
    for (ll i = 0; i <= k; i++) {
        ans += mint(-1).pow(k - i) * comb::comb(k, i) * mint(i).pow(n);
    }
    cout << ans << endl;
}