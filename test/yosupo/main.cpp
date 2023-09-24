#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"
#include "../../template/template.hpp"
#include "../../math/enumerate-primes.hpp"
using namespace std;
int main() {
    int n, a, b;
    cin >> n >> a >> b;
    auto primes = enumerate_primes(n);
    vector<int> ans;
    for (int i = b; i < primes.size(); i += a) {
        ans.push_back(primes[i]);
    }
    cout << primes.size() << " " << ans.size() << endl;
    for (int i = 0; i < (int)(ans.size()); i++) {
        cout << ans[i] << " \n"[i + 1 == (int)(ans.size())];
    }
}