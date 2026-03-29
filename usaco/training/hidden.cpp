/*
ID: yangchess1
PROG: hidden
LANG: C++
*/

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
	cin.tie(nullptr);
#ifdef ONLINE_JUDGE
	std::freopen("hidden.in", "r", stdin);
	std::freopen("hidden.out", "w", stdout);
#endif

	LL L;
	string S;
	cin >> L >> S;
	while (S.length() < L) {
		string s;
		cin >> s;
		S += s;
	}

	vector<LL> O(L);
	{
		vector<pair<char, LL>> o(L);
		RF(i, 0, L) {
			o[i] = {S[i], i};
		}
		stable_sort(o.begin(), o.end());
		LL c{0};
		O[o[0].second] = 0;
		RF(i, 1, L) {
			if (o[i].first != o[i - 1].first) {
				c++;
			}
			O[o[i].second] = c;
		}
		// RF(i, 0, L) {
		// 	cout << O[i] << ' ';
		// }
		// cout << '\n';
	}
	for (LL i{1}; i < L; i *= 2) {
		vector<pair<pair<LL, LL>, LL>> o(L);
		RF(j, 0, L) {
			o[j] = {{O[j], O[(j + i) % L]}, j};
		}
		stable_sort(o.begin(), o.end());
		LL c{0};
		O[o[0].second] = 0;
		RF(j, 1, L) {
			if (o[j].first != o[j - 1].first) {
				c++;
			}
			O[o[j].second] = c;
		}
		// RF(i, 0, L) {
		// 	cout << O[i] << ' ';
		// }
		// cout << '\n';
	}
	RF(i, 0, L) {
		if (O[i] == 0) {
			cout << i << '\n';
			break;
		}
	}

	return 0;
}