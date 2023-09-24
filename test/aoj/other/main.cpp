#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0233"
#include "../../../template/template.hpp"
#include "../../../math/convert-base.hpp"
using namespace std;
using namespace cp_library;
int main() {
    while (true) {
        int x;
        cin >> x;
        if (x == 0) break;
        auto res = convert_base(x, -10);
        for (auto& e : res) cout << e;
        cout << endl;
    }
}