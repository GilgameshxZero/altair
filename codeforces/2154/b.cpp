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
		LL N;
		cin >> N;
		vector<LL> A(N + 1);
		RF(i, 1, N + 1) {
			cin >> A[i];
		}
		A[0] = LLONG_MAX;
		A.push_back(LLONG_MAX);
		LL Z{0}, Y{A[1]};
		RF(i, 2, N + 1) {
			Y = max(Y, A[i]);
			if (i % 2 == 0) {
				A[i] = Y;
			}
		}
		RF(i, 1, N + 1) {
			if (i % 2 == 1 && A[i] >= min(A[i - 1], A[i + 1])) {
				Z += A[i] - min(A[i - 1], A[i + 1]) + 1;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
