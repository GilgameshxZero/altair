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
array<LL, 200001> D;
array<array<LL, 25>, 200001> A;

void CD(LL i, LL p) {
	A[i][0] = p;
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		D[j] = D[i] + 1;
		CD(j, i);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> Q;
	RF(i, 0, N - 1) {
		LL a, b;
		cin >> a >> b;
		E[a].push_back(b);
		E[b].push_back(a);
	}
	D[0] = 0;
	D[1] = 1;
	CD(1, 0);
	A[0][0] = 0;
	RF(j, 1, A[0].size()) {
		RF(i, 0, N + 1) {
			A[i][j] = A[A[i][j - 1]][j - 1];
		}
	}
	RF(i, 0, Q) {
		LL a, b;
		cin >> a >> b;
		if (D[a] < D[b]) {
			swap(a, b);
		}
		LL r{D[a] - D[b]}, l{A[0].size() - 1}, z{r};
		for (; r != 0; l--) {
			if ((1LL << l) <= r) {
				r -= (1LL << l);
				a = A[a][l];
			}
		}
		if (a == b) {
			cout << z << '\n';
			continue;
		}
		l = A[0].size() - 1;
		for (; l >= 0; l--) {
			if (A[a][l] == A[b][l]) {
				continue;
			}
			a = A[a][l];
			b = A[b][l];
			z += 2 * (1 << l);
		}
		cout << z + 2 << '\n';
	}

	return 0;
}
