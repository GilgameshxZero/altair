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

	LL N;
	cin >> N;
	vector<LL> X(N);
	RF(i, 0, N) {
		cin >> X[i];
	}

	map<LL, LL> M;
	M[X[0]] = 1;
	RF(i, 1, N) {
		auto j{M.lower_bound(X[i])};
		LL k{j == M.begin() ? 1 : (--j)->second + 1};
		while (j != M.end()) {
			if (j->first >= X[i] && j->second <= k) {
				j = M.erase(j);
			} else if (j->first >= X[i] && j->second > k) {
				break;
			} else {
				j++;
			}
		}
		M[X[i]] = max(M[X[i]], k);
	}
	cout << M.rbegin()->second;

	return 0;
}
