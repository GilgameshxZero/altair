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

	LL N, K;
	cin >> N >> K;

	unordered_set<LL> C;
	RF(i, 0, N) {
		LL X{0};
		RF(j, 0, K) {
			LL Y;
			cin >> Y;
			X = X * 3 + Y;
		}
		C.insert(X);
	}

	LL Z{0};
	for (auto &i : C) {
		LL A{0};
		for (auto &j : C) {
			if (i == j) {
				continue;
			}
			LL I{i}, J{j}, X{0};
			RF(k, 0, K) {
				if (I % 3 == J % 3) {
					X = X * 3 + I % 3;
				} else {
					X = X * 3 + (3 - I % 3 - J % 3);
				}
				I /= 3;
				J /= 3;
			}
			LL Y{0};
			RF(k, 0, K) {
				Y = Y * 3 + X % 3;
				X /= 3;
			}
			A += C.count(Y);
		}
		A /= 2;
		Z += A * (A - 1) / 2;
	}
	cout << Z << '\n';

	return 0;
}
