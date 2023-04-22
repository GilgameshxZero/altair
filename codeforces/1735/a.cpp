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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> X, Y;
		X.push_back((2 * N) / 3 - 3);
		Y.push_back(N - 4 - X.back());
		X.push_back((2 * N) / 3 - 3 + 1);
		Y.push_back(N - 4 - X.back());
		LL Z{0};
		RF(i, 0, 2) {
			Z = max(Z, min(Y[i] - 1, X[i] - Y[i]));
		}
		cout << Z << '\n';
	}

	return 0;
}
