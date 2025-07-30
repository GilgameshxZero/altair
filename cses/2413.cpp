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

LL const M{1000000007};
array<LL, 1000001> A, B, C, D;
	
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	A[0] = 0;
	LL S{0}, Y{0};
	RF(i, 1, A.size()) {
		A[i] = S + 1;
		A[i] %= M;
		S += A[i];
		S %= M;
		B[i] = A[i] * A[i];
		B[i] %= M;
	}
	D[1] = 2;
	RF(i, 2, A.size()) {
		D[i] = B[i] + D[i - 1] * 2 + Y;
		D[i] %= M;
		Y = Y * 4 + D[i - 1];
		Y %= M;
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		cout << D[N] << '\n';
	}

	return 0;
}
