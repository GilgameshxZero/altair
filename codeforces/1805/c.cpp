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
		LL N, M;
		cin >> N >> M;

		vector<LL> K(N);
		RF(i, 0, N) {
			cin >> K[i];
		}
		sort(K.begin(), K.end());

		RF(i, 0, M) {
			LL A, B, C;
			cin >> A >> B >> C;
			if (A * C < 0) {
				cout << "NO\n";
				continue;
			}

			LD kl{B - 2 * sqrt((LD)A * C)}, kh{B + 2 * sqrt((LD)A * C)};
			auto cand{upper_bound(K.begin(), K.end(), kl)};
			if (cand != K.end() && *cand < kh) {
				cout << "YES\n" << *cand << '\n';
			} else {
				cout << "NO\n";
			}
		}
	}

	return 0;
}
