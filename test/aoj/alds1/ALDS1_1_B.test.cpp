#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_B"
#include "../../../template/template.hpp"
#include "../../../math/gcd-lcm.hpp"
using namespace std;
int main() {
    long long a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
}