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

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		string S;
		cin >> N >> K >> S;
		array<LL, 3> C;
		C.fill(0);
		RF(i, 0, K) {
			C[S[i] - '0']++;
		}
		string Z(N, '+');
		RF(i, C[0], min(N, C[0] + C[2])) {
			Z[i] = '?';
		}
		RF(i, N - 1 - C[1], max(-1LL, N - 1 - C[1] - C[2])) {
			Z[i] = '?';
		}
		RF(i, 0, C[0]) {
			Z[i] = '-';
		}
		RF(i, N - 1, N - 1 - C[1]) {
			Z[i] = '-';
		}
		if (C[0] + C[1] + C[2] >= N) {
			replace(Z.begin(), Z.end(), '?', '-');
		}
		cout << Z << '\n';
	}

	return 0;
}
