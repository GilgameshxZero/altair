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

	LL N, Q;
	cin >> N >> Q;
	vector<LL> A(N);
	RF(i, 0, N) {
		A[i] = i + 1;
	}
	LL O{0};
	RF(i, 0, Q) {
		LL t, p, x, k;
		cin >> t;
		if (t == 1) {
			cin >> p >> x;
			A[(-O + p - 1 + N) % N] = x;
		} else if (t == 2) {
			cin >> p;
			cout << A[(-O + p - 1 + N) % N] << '\n';
		} else {
			cin >> k;
			O = (O - k + N) % N;
		}
	}

	return 0;
}
