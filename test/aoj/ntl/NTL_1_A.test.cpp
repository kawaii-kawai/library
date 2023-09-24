#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A"
#include "../../../template/template.hpp"
#include "../../../math/prime-factorize.hpp"
using namespace std;
using namespace cp_library;
int main() {
    int n;
    cin >> n;
    cout << n << ':';
    for (auto &p : prime_factorize(n)) {
        while (p.second--) cout << ' ' << p.first;
    }
    cout << endl;
}