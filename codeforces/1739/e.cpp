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

	LL N;
	string H[2];
	cin >> N >> H[0] >> H[1];
	vector<bool> D[2];
	LL TD{0};
	RF(i, 0, N) {
		D[0].push_back(H[0][i] == '1');
		D[1].push_back(H[1][i] == '1');
		TD += D[0][i] + D[1][i];
	}
	D[0].push_back(false);
	D[1].push_back(false);

	vector<LL> Z[2];
	Z[0].resize(N + 2, LLONG_MAX / 2);
	Z[1].resize(N + 2, LLONG_MAX / 2);
	Z[0][0] = 0;
	RF(i, 0, N) {
		RF(j, 0, 2) {
			if (!D[1 - j][i]) {
				Z[j][i + 1] = min(Z[j][i + 1], Z[j][i]);
			} else if (D[j][i + 1]) {
				Z[j][i + 1] = min(Z[j][i + 1], Z[j][i] + 1);
				Z[1 - j][i + 2] = min(Z[1 - j][i + 2], Z[j][i] + 1);
			} else {
				Z[1 - j][i + 1] = min(Z[1 - j][i + 1], Z[j][i]);
				Z[j][i + 1] = min(Z[j][i + 1], Z[j][i] + 1);
			}
		}
	}

	cout << TD - min(Z[0][N], Z[1][N]) << '\n';
	return 0;
}
