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

	LL N, M;
	cin >> N >> M;
	LL X, Y;
	cin >> X >> Y;
	map<LL, LL> A;
	RF(i, 0, N - 2) {
		LL X;
		cin >> X;
		A[X]++;
	}

	LL C{0}, Z{LLONG_MAX / 2};
	auto D{A.begin()}, E{A.begin()};
	while (true) {
		if (C < M) {
			if (D == A.end()) {
				break;
			}
			C += D->second;
			D++;
			continue;
		}

		Z = min(Z, max(0LL, X - E->first) + max(0LL, prev(D)->first - Y));

		C -= E->second;
		E++;
	}

	cout << Z;
	return 0;
}
