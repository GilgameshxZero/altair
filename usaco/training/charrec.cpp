/*
ID: yangchess1
PROG: charrec
LANG: C++
*/

// Note: should actually count corruptions in the most
// corrupted duplicated line.

#define ONLINE_JUDGE

#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__) && !defined(ONLINE_JUDGE)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
#ifdef ONLINE_JUDGE
	std::freopen("charrec.in", "r", stdin);
	std::freopen("charrec.out", "w", stdout);
#endif

	array<string, 27> fontString;
	array<bitset<400>, 27> font;
	array<array<bitset<380>, 20>, 27> fontSmall;
	array<array<bitset<420>, 20>, 27> fontLarge;
	{
#ifdef ONLINE_JUDGE
		ifstream fontIn("font.in");
#else
		ifstream fontIn(
			"../../../usaco/training-pages/font.in");
#endif
		LL i;
		fontIn >> i;
		RF(i, 0, 27) {
			string s;
			RF(j, 0, 20) {
				fontIn >> s;
				fontString[i] += s;
			}
			font[i] = bitset<400>(fontString[i]);
			RF(j, 0, 20) {
				RF(k, 0, j * 20) {
					fontSmall[i][j].set(k, font[i][k]);
				}
				RF(k, (j + 1) * 20, 400) {
					fontSmall[i][j].set(k - 20, font[i][k]);
				}
			}
			RF(j, 0, 20) {
				RF(k, 0, (j + 1) * 20) {
					fontLarge[i][j].set(k, font[i][k]);
				}
				RF(k, j * 20, 400) {
					fontLarge[i][j].set(k + 20, font[i][k]);
				}
			}
			// string ss = fontLarge[i][10].to_string();
			// RF(l, 0, 21) {
			// 	cout << ss.substr(l * 20, 20) << '\n';
			// }
		}
	}

	string const C{" abcdefghijklmnopqrstuvwxyz"};

	LL N;
	cin >> N;
	string S;
	RF(i, 0, N) {
		string s;
		cin >> s;
		S += s;
	}

	vector<pair<LL, string>> Z(N + 1, {LLONG_MAX / 2, ""});
	Z[0] = {0, ""};
	RF(i, 19, N + 1) {
		pair<LL, char> c{LLONG_MAX / 2, '\0'};
		LL mode{0};
		if (i >= 19) {
			bitset<380> b(S, (i - 19) * 20, 380);
			RF(j, 0, 27) {
				RF(k, 0, 20) {
					pair<LL, char> cc{
						(b ^ fontSmall[j][k]).count() + Z[i - 19].first,
						C[j]};
					// if (i == 338 && (C[j] == 'b' || C[j] == 'h')) {
					// 	cout << cc.first << ' ' << cc.second << '\n';
					// }
					if (cc.first < c.first) {
						c = cc;
						mode = 19;
					}
				}
			}
		}
		if (i >= 20) {
			bitset<400> b(S, (i - 20) * 20, 400);
			RF(j, 0, 27) {
				pair<LL, char> cc{
					(b ^ font[j]).count() + Z[i - 20].first, C[j]};
				if (cc.first < c.first) {
					c = cc;
					mode = 20;
				}
			}
		}
		if (i >= 21) {
			bitset<420> b(S, (i - 21) * 20, 420);
			RF(j, 0, 27) {
				RF(k, 0, 20) {
					pair<LL, char> cc{
						(b ^ fontLarge[j][k]).count() + Z[i - 21].first,
						C[j]};
					bitset<20> dupe(fontString[j], k * 20, 20);
					LL overcount(min(
						(dupe ^ bitset<20>(S, (i - 21 + k) * 20, 20))
							.count(),
						(dupe ^
						 bitset<20>(S, (i - 21 + k + 1) * 20, 20))
							.count()));
					cc.first -= overcount;
					// if (i == 338 && (C[j] == 'b' || C[j] == 'h')) {
					// 	cout << cc.first << ' ' << cc.second << '\n';
					// }
					if (cc.first < c.first) {
						c = cc;
						mode = 21;
					}
				}
			}
		}
		Z[i] = {c.first, Z[i - mode].second + c.second};
		// cout << Z[i].first << ' ' << Z[i].second << ' ' <<
		// mode
		// 		 << '\n';
	}
	cout << Z.back().second << '\n';

	return 0;
}