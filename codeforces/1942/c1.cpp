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

	LL T;
	cin >> T;
	while (T--) {
		LL N, X, Y;
		cin >> N >> X >> Y;
		LL R{N};
		vector<LL> A(X);
		RF(i, 0, X) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		LL Z{0};
		RF(i, 0, X - 1) {
			if (A[i + 1] - A[i] == 2) {
				Z++;
			}
			R -= A[i + 1] - A[i] - 1;
		}
		if (A[0] + N - A[X - 1] == 2) {
			Z++;
		}
		R -= A[0] + N - A[X - 1] - 1;
		cout << Z + R - 2 << '\n';
	}

	return 0;
}
