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
		vector<LL> P(N);
		RF(i, 0, N) {
			cin >> P[i];
		}
		LL loseMin{P[0]}, winMin{LLONG_MAX / 2};
		vector<bool> W(N);
		W[0] = false;
		RF(i, 1, N) {
			if (loseMin > P[i] && winMin > P[i] || winMin < P[i]) {
				W[i] = false;
				loseMin = min(loseMin, P[i]);
			} else {
				W[i] = true;
				winMin = min(winMin, P[i]);
			}
		}
		LL Z{0};
		RF(i, 0, N) {
			Z += W[i];
		}
		cout << Z << '\n';
	}

	return 0;
}
