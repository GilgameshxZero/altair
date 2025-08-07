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

LL N, Q;
array<vector<LL>, 200001> E;
array<array<LL, 25>, 200001> A;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> Q;
	RF(i, 2, N + 1) {
		LL a;
		cin >> a;
		E[a].push_back(i);
		A[i][0] = a;
	}
	A[1][0] = A[0][0] = 0;
	RF(j, 1, A[0].size()) {
		RF(i, 0, N + 1) {
			A[i][j] = A[A[i][j - 1]][j - 1];
		}
	}
	RF(i, 0, Q) {
		LL a, b;
		cin >> a >> b;
		LL l{A[0].size() - 1};
		for (; b != 0; l--) {
			if ((1LL << l) <= b) {
				b -= (1LL << l);
				a = A[a][l];
			}
		}
		cout << (a == 0 ? -1 : a) << '\n';
	}

	return 0;
}
