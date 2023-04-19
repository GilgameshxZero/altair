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

	LL P1, T1, P2, T2, H, S;
	cin >> P1 >> T1 >> P2 >> T2 >> H >> S;
	if (T1 > T2) {
		swap(P1, P2);
		swap(T1, T2);
	}

	vector<LL> b1d(5001, 0), b2d{b1d};
	RF(i, 1, b1d.size()) {
		RF(j, 0, i) {
			bool al1{(i - j) * T1 / T2 > 0}, al2{(i - j) * T2 / T1 > 0};
			b1d[i] = max(
				b1d[i], b1d[j] + (i - j) * (P1 - S) + (i - j) * T1 / T2 * (P2 - S) + (al1 ? S : 0));
			b2d[i] = max(
				b2d[i], b2d[j] + (i - j) * (P2 - S) + (i - j) * T2 / T1 * (P1 - S) + (al2 ? S : 0));
		}
	}

	LL ans{LLONG_MAX / 2};
	RF(i, 0, b1d.size()) {
		RF(j, 0, b1d.size()) {
			if (b1d[i] + b2d[j] >= H) {
				ans = min(ans, i * T1 + j * T2);
			}
		}
	}
	cout << ans;

	return 0;
}
