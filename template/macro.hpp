#pragma once

#include "template.hpp"

namespace cp_library {

#define OVERLOAD5(a, b, c, d, e, ...) e
#define REP1(b) for (ll _i = 0; _i < (ll)(b); _i++)
#define REP2(i, b) for (ll i = 0; i < (ll)(b); i++)
#define REP3(i, a, b) for (ll i = (ll)(a); i < (ll)(b); i++)
#define REP4(i, a, b, c) for (ll i = (ll)(a); i < (ll)(b); i += (ll)(c))
#define rep(...) OVERLOAD5(__VA_ARGS__, REP4, REP3, REP2, REP1)(__VA_ARGS__)

#define RREP1(b) for (ll _i = (ll)(b)-1; _i >= 0; _i--)
#define RREP2(i, b) for (ll i = (ll)(b)-1; i >= 0; i--)
#define RREP3(i, a, b) for (ll i = (ll)(b)-1; i >= (ll)(a); i--)
#define RREP4(i, a, b, c) for (ll i = (ll)(b)-1; i >= (ll)(a); i -= (ll)(c))
#define rrep(...) \
    OVERLOAD5(__VA_ARGS__, RREP4, RREP3, RREP2, RREP1)(__VA_ARGS__)

#define ALL(x) std::begin(x), std::end(x)
#define RALL(x) std::rbegin(x), std::rend(x)

}  // namespace cp_library