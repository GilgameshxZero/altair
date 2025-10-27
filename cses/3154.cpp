#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>
#include <rain.hpp>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

using MF = Rain::Algorithm::ModulusField<LL, 1000000007>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << "hi";
	return 0;
}
