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

	LL N, K;
	cin >> N >> K;
	vector<LL> C(N), V(N);
	vector<pair<LL, LL>> R;
	RF(i, 0, N) {
		cin >> C[i] >> V[i];
	}
	R.push_back({V[0], C[0]});
	RF(i, 1, N) {
		if (R.back().second == C[i]) {
			R.back().first = max(R.back().first, V[i]);
		} else {
			R.push_back({V[i], C[i]});
		}
	}
	LL Z{0};
	RF(i, 0, R.size()) {
		Z += R[i].first;
	}
	K -= (N - R.size());
	if (K < 0) {
		cout << -1;
	} else if (K == 0) {
		cout << Z;
	} else {
		vector<pair<pair<LL, LL>, LL>> C(R.size()), D(R.size());
		C[0] = {{R[0].first, R[0].second}, LLONG_MIN};
		RF(i, 1, R.size()) {
			C[i] = {{C[i - 1].first.first + R[i].first, R[i].second}, LLONG_MIN};
		}
		RF(i, 1, K + 1) {
			D[i - 1] = {{0, -1}, LLONG_MIN};
			RF(j, i, R.size()) {
				if (R[j].second == D[j - 1].first.second) {
					D[j] = {{R[j].first + D[j - 1].second, R[j].second}, LLONG_MIN};
				} else {
					D[j] = {{R[j].first + D[j - 1].first.first, R[j].second}, LLONG_MIN};
				}
				if (C[j - 1].first.first > D[j].first.first) {
					if (D[j].first.second == C[j - 1].first.second) {
						D[j] = {
							{C[j - 1].first.first, C[j - 1].first.second}, C[j - 1].second};
					} else {
						D[j] = {
							{C[j - 1].first.first, C[j - 1].first.second},
							max(D[j].first.first, C[j - 1].second)};
					}
				} else {
					if (D[j].first.second == C[j - 1].first.second) {
						D[j] = {D[j].first, C[j - 1].second};
					} else {
						D[j] = {D[j].first, C[j - 1].first.first};
					}
				}
			}
			swap(C, D);
		}
		cout << C.back().first.first;
	}

	return 0;
}
