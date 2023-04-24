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

	vector<vector<pair<LL, LL>>> B(
		120, vector<pair<LL, LL>>(120, {LLONG_MAX / 2, LLONG_MAX / 2}));
	B[0][0] = {0, 1};
	RF(i, 1, 120) {
		B[0][i].first = 1 + B[0][i - 1].first;
		if (i <= 60) {
			B[0][i].second = B[0][i].first + (1LL << i);
		}

		B[i][0].first = 1 + B[i - 1][0].second;
		if (i <= 60) {
			B[i][0].second = B[i][0].first + (1LL << i);
		}
	}
	RF(i, 1, 120) {
		RF(j, 1, 120) {
			B[i][j] = {1 + B[i - 1][j].second, 1 + B[i][j - 1].first};
			if (B[i][j].first > B[i][j].second) {
				swap(B[i][j].first, B[i][j].second);
			} else if (B[i][j].first == B[i][j].second) {
				if (i + j <= 60) {
					B[i][j].second = B[i][j].first + (1LL << (i + j));
				} else {
					B[i][j].second = LLONG_MAX / 2;
				}
			}
		}
	}

	LL T;
	cin >> T;
	while (T--) {
		LL T, X, Y;
		cin >> T >> X >> Y;
		if (X + Y <= 60) {
			LL S{1LL << (X + Y)};
			if (T % S == B[X][Y].first || T % S == B[X][Y].second) {
				cout << "YES\n";
			} else {
				cout << "NO\n";
			}
		} else {
			if (T == B[X][Y].first || T == B[X][Y].second) {
				cout << "YES\n";
			} else {
				cout << "NO\n";
			}
		}
	}

	return 0;
}
