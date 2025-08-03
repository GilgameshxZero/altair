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

	vector<array<LL, 30>> T(N);
	RF(i, 0, N) {
		cin >> T[i][0];
		T[i][0]--;
	}
	RF(i, 1, 30) {
		RF(j, 0, N) {
			T[j][i] = T[T[j][i - 1]][i - 1];
		}
	}

	RF(i, 0, Q) {
		LL X, K;
		cin >> X >> K;
		X--;

		LL j{29};
		while (K != 0) {
			while ((1LL << j) > K) {
				j--;
			}
			K -= (1LL << j);
			X = T[X][j];
		}
		cout << X + 1 << '\n';
	}

	return 0;
}
