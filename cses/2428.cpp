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

	LL N, K;
	cin >> N >> K;
	vector<LL> X(N);
	RF(i, 0, N) {
		cin >> X[i];
	}

	unordered_map<LL, LL> M;
	LL L{0}, Z{0};
	RF(i, 0, N) {
		M[X[i]]++;
		while (M.size() > K) {
			auto j{M.find(X[L])};
			j->second--;
			if (j->second == 0) {
				M.erase(j);
			}
			L++;
		}
		Z += i - L + 1;
	}
	cout << Z;

	return 0;
}
