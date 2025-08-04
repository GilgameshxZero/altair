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
	vector<LL> X(N + 1);
	RF(i, 1, N + 1) {
		cin >> X[i];
		X[i] += X[i - 1];
	}
	RF(i, 0, Q) {
		LL A, B;
		cin >> A >> B;
		cout << X[B] - X[A - 1] << '\n';
	}

	return 0;
}
