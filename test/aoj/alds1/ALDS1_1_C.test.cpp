#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C"
#include "../../../template/template.hpp"
#include "../../../math/is-prime.hpp"
using namespace std;
using namespace cp_library;
int main() {
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (is_prime(x)) ans++;
    }
    cout << ans << endl;
}