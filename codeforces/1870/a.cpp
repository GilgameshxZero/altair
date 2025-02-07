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
		LL N, K, X;
		cin >> N >> K >> X;
		if (N < K || K > X + 1) {
			cout << -1 << '\n';
			continue;
		}
		LL M{K == X ? X - 1 : X}, R{N - K};
		cout << R * M + K * (K - 1) / 2 << '\n';
	}

	return 0;
}
