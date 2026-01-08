#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	array<LL, 9> P;
	RF(i, 0, P.size()) {
		P[i] = i + 1;
	}
	unordered_set<LL> Z;
	do {
		RF(i, 1, P.size() - 1) {
			RF(j, i + 1, P.size()) {
				LL A{0}, B{0}, C{0};
				RF(k, 0, i) {
					A = A * 10 + P[k];
				}
				RF(k, i, j) {
					B = B * 10 + P[k];
				}
				RF(k, j, P.size()) {
					C = C * 10 + P[k];
				}
				if (A * B == C) {
					Z.insert(C);
				}
			}
		}
	} while (next_permutation(P.begin(), P.end()));

	LL ZZ{0};
	for (auto &i : Z) {
		ZZ += i;
	}
	cout << ZZ;
	return 0;
}
