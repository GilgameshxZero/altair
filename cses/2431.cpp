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
		if (N <= 9) {
			cout << N << '\n';
			continue;
		}
		N -= 9;
		LL P{10};
		RF(i, 2, 100) {
			P *= 10;
			if (N > i * (P - P / 10)) {
				N -= i * (P - P / 10);
			} else {
				N--;
				LL X{N / i + P / 10}, R{N - N / i * i};
				cout << to_string(X)[R] << '\n';
				break;
			}
		}
	}

	return 0;
}
