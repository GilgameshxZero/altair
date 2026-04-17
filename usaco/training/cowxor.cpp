/*
ID: yangchess1
LANG: C++
PROB: cowxor
*/

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

array<pair<int, int>, 900000> T;
int TS{1};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#ifndef _DEBUG
	std::freopen("cowxor.in", "r", stdin);
	std::freopen("cowxor.out", "w", stdout);
#endif

	LL const MM{20};
	pair<LL, LL> Z{0, 1};
	LL N;
	cin >> N;

	vector<int> S(N + 1);
	S[0] = 0;
	{
		LL l{0};
		RF(i, MM, -1) {
			LL nl(TS);
			T[l].first = nl;
			TS++;
			l = nl;
		}
	}
	RF(i, 1, N + 1) {
		LL j;
		cin >> j;
		S[i] = S[i - 1] ^ j;
		LL l{0};
		RF(k, MM, -1) {
			bool d{0 != ((1LL << k) & S[i])};
			LL nl;
			nl = d ? T[l].first : T[l].second;
			if (nl == 0) {
				nl = d ? T[l].second : T[l].first;
			}
			l = nl;
		}
		LL z{S[Z.second] ^ S[Z.first]},
			z2{S[i] ^ S[-T[l].first]};
		if (z2 > z) {
			Z = {-T[l].first, i};
		}
		// cout << z2 << '\n';

		l = 0;
		RF(k, MM, -1) {
			bool d{0 != ((1LL << k) & S[i])};
			LL nl;
			nl = d ? T[l].second : T[l].first;
			if (nl == 0) {
				nl = TS;
				if (d) {
					T[l].second = nl;
				} else {
					T[l].first = nl;
				}
				TS++;
			}
			l = nl;
		}
		T[l].first = -i;
	}

	// RF(i, 0, S.size()) {
	// 	cout << S[i] << ' ';
	// }
	// cout << '\n';
	// RF(i, 0, T.size()) {
	// 	cout << T[i].first << ' ' << T[i].second << '\n';
	// }
	cout << (S[Z.second] ^ S[Z.first]) << ' ' << Z.first + 1
			 << ' ' << Z.second << '\n';

	return 0;
}
