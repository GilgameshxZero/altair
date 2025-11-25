#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		LL X{0}, Y{0}, Z{0};
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
			X += A[i];
		}
		RF(i, 0, N) {
			Y += A[i];
			Z = max(Z, min(Y, X - Y));
		}
		cout << Z << '\n';
	}

	return 0;
}
