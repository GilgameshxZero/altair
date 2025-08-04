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
	vector<array<LL, 30>> X(N);
	RF(i, 0, N) {
		cin >> X[i][0];
	}
	RF(i, 1, X[0].size()) {
		RF(j, 0, N) {
			X[j][i] = min(X[j][i - 1],
				j + (1LL << (i - 1)) < N ? X[j + (1LL << (i - 1))][i - 1] : LLONG_MAX);
		}
	}
	RF(i, 0, Q) {
		LL A, B;
		cin >> A >> B;
		A--;
		B--;
		LL K{B - A + 1}, L{0};
		while ((1LL << L) <= K) {
			L++;
		}
		L--;
		cout << min(X[A][L], X[B - (1LL << L) + 1][L]) << '\n';
	}

	return 0;
}
