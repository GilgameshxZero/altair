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
		LL N, M;
		cin >> N >> M;
		vector<string> G(N);
		RF(i, 0, N) {
			cin >> G[i];
		}
		string S{"akiv"};
		bool fail{true};
		RF(i, 0, M) {
			RF(j, 0, N) {
				if (S.back() == G[j][i]) {
					S.pop_back();
					break;
				}
			}
			if (S.empty()) {
				fail = false;
				break;
			}
		}
		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
