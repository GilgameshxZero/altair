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

	map<LL, LL> S;
	RF(i, 0, N) {
		RF(j, i + 1, N) {
			auto k{S.find(X - A[i] - A[j])};
			if (k != S.end()) {
				cout << k->second + 1 << ' ' << i + 1 << ' ' << j + 1;
				return 0;
			}
		}
		S[A[i]] = i;
	}
	cout << "IMPOSSIBLE";

	return 0;
}
