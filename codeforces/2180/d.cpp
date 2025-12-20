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

class Info {
	public:
	LL MR, YR, YO;
	pair<LL, LL> RG;
};

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
		P.push_back(LLONG_MAX);
		array<Info, 2> Z;
		Z[0].MR = P[1] - P[0];
		Z[0].RG = {0, 0};
		Z[0].YR = Z[0].YO = 0;
		RF(i, 1, N) {
			Z[1].MR = min(P[i] - P[i - 1], P[i + 1] - P[i]);
			Z[1].YR = 0;
			Z[1].RG = {P[i] - P[i - 1] - Z[0].MR, Z[1].MR};
			if (Z[1].RG.second > Z[1].RG.first) {
				Z[1].YR = 1 + Z[0].YO;
				if (Z[0].RG.second > Z[0].RG.first) {
					if (
						Z[0].RG.second + Z[1].RG.second > P[i] - P[i - 1] &&
						Z[0].RG.first + Z[1].RG.first < P[i] - P[i - 1]) {
						Z[1].RG.first =
							max(Z[1].RG.first, P[i] - P[i - 1] - Z[0].RG.second);
						Z[1].RG.second =
							min(Z[1].RG.second, P[i] - P[i - 1] - Z[0].RG.first);
						Z[1].YR = max(Z[1].YR, 1 + Z[0].YR);
					}
				}
			}
			Z[1].YO = max(Z[0].YR, Z[0].YO);
			swap(Z[0], Z[1]);
		}
		cout << max(Z[0].YO, Z[0].YR) << '\n';
	}

	return 0;
}
