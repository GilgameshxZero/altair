#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N, M, K;
		cin >> N >> M >> K;
		if (K == 1 || K == N) {
			cout << min(N, 1 + (M + 1) / 2) << '\n';
		} else {
			LL U{min(K - 1, N - K)}, V{N - U - 1},
				Z{min((M + 1) / 3, U) * 2 + 1};
			Z = max(Z, 2 * min((M + 2) / 3, U));
			if (M >= U * 3 - 1) {
				Z = max(Z, min(V, (M + 1 - U) / 2) + U + 1);
			}
			cout << Z << '\n';
		}
	}

	return 0;
}
