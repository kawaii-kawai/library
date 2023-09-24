#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_E"
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
    cout << comb::comb(k, n) << endl;
}