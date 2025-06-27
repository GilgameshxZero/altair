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

	LL N;
	cin >> N;
	multimap<LL, LL> M;
	RF(i, 0, N) {
		LL X, Y;
		cin >> X >> Y;
		M.insert({Y, X});
	}
	LL Z{0}, E{-1};
	while (!M.empty()) {
		auto [X, Y] = *M.begin();
		if (Y >= E) {
			E = X;
			Z++;
		}
		M.erase(M.begin());
	}
	cout << Z;

	return 0;
}
