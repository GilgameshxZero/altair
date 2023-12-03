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
	vector<LL> X(N), Y(N);
	RF(i, 0, N) {
		cin >> X[i] >> Y[i];
	}
	cout << 2 *
			(2 + *max_element(X.begin(), X.end()) - *min_element(X.begin(), X.end()) +
			 2 + *max_element(Y.begin(), Y.end()) - *min_element(Y.begin(), Y.end()))
			 << '\n';

	return 0;
}
