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
		vector<vector<LL>> B(K + 1);
		RF(i, 0, N) {
			LL x;
			cin >> x;
			B[x].push_back(i);
		}
		set<LL> S;
		vector<LL> Z(K + 1);
		RF(i, K, 0) {
			RF(j, 0, B[i].size()) {
				S.insert(B[i][j]);
			}
			if (S.empty() || B[i].empty()) {
				Z[i] = 0;
			} else {
				Z[i] = 2 * (*S.rbegin() - *S.begin() + 1);
			}
		}
		RF(i, 1, K + 1) {
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
