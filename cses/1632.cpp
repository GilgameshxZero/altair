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
	vector<pair<LL, LL>> A(N);
	RF(i, 0, N) {
		cin >> A[i].second >> A[i].first;
	}
	sort(A.begin(), A.end());

	multiset<LL> S;
	RF(i, 0, K) {
		S.insert(0);
	}
	LL Z{0};
	RF(i, 0, N) {
		auto j{S.upper_bound(A[i].second)};
		if (j == S.begin()) {
			continue;
		}
		j--;
		S.erase(j);
		S.insert(A[i].first);
		Z++;
	}
	cout << Z;

	return 0;
}
