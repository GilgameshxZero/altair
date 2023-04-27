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
		string A, B;
		cin >> A >> B;

		array<LL, 26 * 26> F;
		F.fill(0);
		RF(i, 0, N) {
			LL X{A[i] - 'a'}, Y{B[N - 1 - i] - 'a'};
			if (X > Y) {
				swap(X, Y);
			}
			F[26 * X + Y]++;
		}

		LL O{0};
		bool fail{false};
		RF(i, 0, F.size()) {
			if (F[i] % 2 != 0) {
				if (i / 26 != i % 26) {
					fail = true;
					break;
				} else {
					O++;
				}
			}
		}
		if (fail) {
			cout << "NO\n";
			continue;
		}
		if (N % 2 == 0 && O == 0 || N % 2 == 1 && O == 1) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}
