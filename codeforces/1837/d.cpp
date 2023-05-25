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
		string S;
		cin >> N >> S;

		LL minY{0}, maxY{0}, Y{0};
		RF(i, 0, N) {
			Y += (S[i] == '(' ? 1 : -1);
			minY = min(Y, minY);
			maxY = max(Y, maxY);
		}
		if (Y != 0) {
			cout << "-1\n";
		} else if (minY == 0 || maxY == 0) {
			cout << "1\n";
			RF(i, 0, N) {
				cout << "1 ";
			}
			cout << '\n';
		} else {
			cout << "2\n";
			RF(i, 0, N) {
				Y += (S[i] == '(' ? 1 : -1);
				if (Y == 0) {
					cout << (S[i] == '(' ? 2 : 1);
				} else if (Y < 0) {
					cout << 2;
				} else {
					cout << 1;
				}
				cout << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
