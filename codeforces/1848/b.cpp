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
		LL N, K;
		cin >> N >> K;
		vector<vector<LL>> C(K);
		RF(i, 0, K) {
			C[i].push_back(-1);
		}
		RF(i, 0, N) {
			LL c;
			cin >> c;
			C[--c].push_back(i);
		}
		LL Z{LLONG_MAX / 2};
		RF(i, 0, K) {
			C[i].push_back(N);
			multiset<LL> M;
			RF(j, 1, C[i].size()) {
				M.insert(C[i][j] - C[i][j - 1] - 1);
			}
			M.insert((*M.rbegin() - 1) / 2);
			M.insert(*M.rbegin() - (*M.rbegin() - 1) / 2 - 1);
			M.erase(prev(M.end()));
			Z = min(Z, *M.rbegin());
		}
		cout << Z << '\n';
	}

	return 0;
}
