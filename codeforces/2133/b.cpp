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
		LL N;
		cin >> N;
		vector<LL> G(N);
		if (N % 2 == 1) {
			G.push_back(0);
		}
		RF(i, 0, N) {
			cin >> G[i];
		}
		sort(G.begin(), G.end());
		LL Z{0};
		RF(i, 0, G.size() / 2) {
			Z += max(G[i * 2], G[i * 2 + 1]);
		}
		cout << Z << '\n';
	}

	return 0;
}
