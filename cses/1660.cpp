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

	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}

	LL P{0}, S{0}, Z{0};
	RF(i, 0, N) {
		S += A[i];
		while (S > X && P < i) {
			S -= A[P++];
		}
		if (S == X) {
			Z++;
		}
	}
	cout << Z;

	return 0;
}
