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

	LL T;
	cin >> T;
	while (T--) {
		map<LL, LL> F;
		LL N, K;
		cin >> N >> K;
		RF(i, 0, N) {
			LL X;
			cin >> X;
			F[X]++;
		}
		LL Z{0};
		for (auto &i : F) {
			auto j{F.find(K - i.first)};
			if (j != F.end()) {
				Z += min(i.second, j->second);
			}
		}
		cout << Z / 2 << '\n';
	}

	return 0;
}
