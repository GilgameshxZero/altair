#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> p[2];
		RF(i, 0, N) {
			LL X;
			cin >> X;
			p[X].push_back(i);
		}
		reverse(p[1].begin(), p[1].end());
		LL ans{0};
		while (!p[0].empty() && !p[1].empty() && p[0].back() > p[1].back()) {
			p[0].pop_back();
			p[1].pop_back();
			ans++;
		}
		cout << ans << '\n';
	}

	return 0;
}
