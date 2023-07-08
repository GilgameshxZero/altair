#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL A, B;
	cin >> A >> B;
	A--;
	B--;
	LL a, b, c, d;
	a = A / 3;
	b = A % 3;
	c = B / 3;
	d = B % 3;
	cout << ((a == c && abs(b - d) == 1) ? "Yes" : "No") << '\n';

	return 0;
}
