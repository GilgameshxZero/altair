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

	LL N, X;
	cin >> N >> X;

	vector<pair<LL, pair<LL, LL>>> S(N);
	RF(i, 0, N) {
		cin >> S[i].first >> S[i].second.first >> S[i].second.second;
	}

	vector<vector<double>> Z(X + 1, vector<double>(1LL << N));
	RF(i, 1, X + 1) {
		RF(k, 0, 1LL << N) {
			RF(j, 0, N) {
				if (i - S[j].second.first < 0) {
					continue;
				}
				if ((k & (1LL << j)) == 0) {
					continue;
				}
				Z[i][k] = max(Z[i][k],
					(Z[i - S[j].second.first][k ^ (1LL << j)] + S[j].first) *
							S[j].second.second / 100 +
						Z[i - S[j].second.first][k] * (100 - S[j].second.second) / 100);
			}
		}
	}
	cout << setprecision(18) << Z[X].back();

	return 0;
}
