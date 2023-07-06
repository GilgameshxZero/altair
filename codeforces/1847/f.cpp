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
		LL N, Q;
		cin >> N >> Q;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		vector<pair<LL, LL>> X, Y;
		X.push_back({0, A[0]});
		vector<vector<pair<LL, LL>>> B(N);
		B[1].push_back({A[1], 0});
		RF(i, 1, N) {
			if ((B[1].back().first | A[(1 - i + N) % N]) != B[1].back().first) {
				B[1].push_back({B[1].back().first | A[(1 - i + N) % N], i});
			}
		}
		RF(i, 2, N) {
			B[i].push_back({A[i], 0});
			RF(j, 0, B[i - 1].size()) {
				if ((B[i].back().first | B[i - 1][j].first) != B[i].back().first) {
					B[i].push_back(
						{B[i].back().first | B[i - 1][j].first, B[i - 1][j].second + 1});
				}
			}
		}
		RF(i, 1, N) {
			RF(j, 0, B[i].size()) {
				X.push_back({1 + B[i][j].second * (N - 1) + i - 1, B[i][j].first});
			}
		}
		sort(X.begin(), X.end());
		Y.push_back({X[0].second, X[0].first});
		RF(i, 1, X.size()) {
			if (X[i].second > Y.back().first) {
				Y.push_back({X[i].second, X[i].first});
			}
		}

		RF(i, 0, Q) {
			LL x;
			cin >> x;
			auto Z{lower_bound(Y.begin(), Y.end(), pair<LL, LL>(x + 1, 0))};
			cout << (Z == Y.end() ? -1 : Z->second + 1) << '\n';
		}
	}

	return 0;
}
