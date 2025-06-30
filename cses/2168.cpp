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

	LL N;
	cin >> N;

	vector<pair<pair<LL, LL>, LL>> X(N);
	RF(i, 0, N) {
		cin >> X[i].first.first >> X[i].first.second;
		X[i].second = i;
	}

	vector<bool> Z[2];
	Z[0].resize(N, false);
	Z[1].resize(N, false);

	sort(X.begin(),
		X.end(),
		[](pair<pair<LL, LL>, LL> &X, pair<pair<LL, LL>, LL> &Y) {
			if (X.first.first == Y.first.first) {
				return X.first.second > Y.first.second;
			}
			return X.first.first < Y.first.first;
		});
	set<LL> E;
	RF(i, N - 1, -1) {
		if (E.upper_bound(X[i].first.second) != E.begin()) {
			Z[0][i] = true;
		}
		E.insert(X[i].first.second);
	}
	E.clear();
	RF(i, 0, N) {
		if (E.lower_bound(X[i].first.second) != E.end()) {
			Z[1][i] = true;
		}
		E.insert(X[i].first.second);
	}

	vector<LL> R(N);
	RF(i, 0, N) {
		R[X[i].second] = i;
	}

	RF(i, 0, N) {
		cout << (Z[0][R[i]] ? 1 : 0) << ' ';
	}
	cout << '\n';
	RF(i, 0, N) {
		cout << (Z[1][R[i]] ? 1 : 0) << ' ';
	}

	return 0;
}
