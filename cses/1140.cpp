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
	X.push_back({{LLONG_MIN, LLONG_MIN}, 0});
	RF(i, 0, N) {
		cin >> X[i].first.second >> X[i].first.first >> X[i].second;
	}
	sort(X.begin(), X.end());
	vector<LL> Z(N + 1);
	Z[0] = 0;
	RF(i, 1, N + 1) {
		auto j{upper_bound(X.begin(),
			X.end(),
			make_pair(make_pair(X[i].first.second, LLONG_MIN), LLONG_MIN))};
		j--;
		Z[i] = max(Z[i - 1], X[i].second + Z[j - X.begin()]);
	}
	cout << Z.back();

	return 0;
}
