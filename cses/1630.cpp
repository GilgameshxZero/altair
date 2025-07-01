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

	vector<pair<LL, LL>> A(N);
	RF(i, 0, N) {
		cin >> A[i].first >> A[i].second;
	}
	sort(A.begin(), A.end());

	LL Z{0}, C{0};
	RF(i, 0, N) {
		C += A[i].first;
		Z += A[i].second - C;
	}
	cout << Z;

	return 0;
}
