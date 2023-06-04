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

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		LL P[3];
		RF(i, 0, N) {
			LL A;
			cin >> A;
			if (A == 1) {
				P[0] = i;
			} else if (A == 2) {
				P[1] = i;
			} else if (A == N) {
				P[2] = i;
			}
		}
		if (P[0] > P[1]) {
			swap(P[0], P[1]);
		}
		if (P[2] < P[1] && P[2] > P[0]) {
			cout << "1 1\n";
		} else if (P[2] < P[0]) {
			cout << P[2] + 1 << ' ' << P[0] + 1 << '\n';
		} else {
			cout << P[2] + 1 << ' ' << P[1] + 1 << '\n';
		}
	}

	return 0;
}
