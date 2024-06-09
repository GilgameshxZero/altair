#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N + 1);
		LL minA{0};
		A[0] = 0;
		RF(i, 1, N + 1) {
			cin >> A[i];
			A[i] += A[i - 1];
			minA = min(minA, A[i]);
		}
		cout << A.back() - 2 * minA << '\n';
	}

	return 0;
}
