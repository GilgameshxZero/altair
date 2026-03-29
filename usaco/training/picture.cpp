/*
ID: yangchess1
PROG: picture
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
	std::freopen("picture.in", "r", stdin);
	std::freopen("picture.out", "w", stdout);
#endif

	LL N;
	cin >> N;

	LL const SHIFT{10000};
	vector<pair<LL, pair<LL, LL>>> RB, RE, CB, CE;
	unordered_set<LL> HXS, HYS;
	RF(i, 0, N) {
		LL a, b, c, d;
		cin >> a >> b >> c >> d;
		a += SHIFT;
		b += SHIFT;
		c += SHIFT;
		d += SHIFT;
		RB.push_back({a, {b, d}});
		RE.push_back({c, {b, d}});
		CB.push_back({b, {a, c}});
		CE.push_back({d, {a, c}});
		HXS.insert(a);
		HXS.insert(c);
		HYS.insert(b);
		HYS.insert(d);
	}
	sort(RB.begin(), RB.end());
	sort(RE.begin(), RE.end());
	sort(CB.begin(), CB.end());
	sort(CE.begin(), CE.end());
	vector<LL> HX, HY;
	for (auto &i : HXS) {
		HX.push_back(i);
	}
	sort(HX.begin(), HX.end());
	for (auto &i : HYS) {
		HY.push_back(i);
	}
	sort(HY.begin(), HY.end());

	multiset<pair<LL, LL>> RA, CA;
	LL RBi{0}, REi{0}, CBi{0}, CEi{0};
	for (; RBi < RB.size() && RB[RBi].first <= HX[0]; RBi++) {
		RA.insert(RB[RBi].second);
	}
	for (; CBi < CB.size() && CB[CBi].first <= HY[0]; CBi++) {
		CA.insert(CB[CBi].second);
	}
	LL Z{0};
	RF(i, 1, HX.size()) {
		LL p{-1}, c{0};
		for (auto &j : RA) {
			if (j.first > p) {
				c++;
			}
			p = max(p, j.second);
		}
		Z += (HX[i] - HX[i - 1]) * 2 * c;
		// cout << HX[i - 1] << ' ' << HX[i] << ' ' << c << '\n';
		for (; REi < RE.size() && RE[REi].first <= HX[i];
				 REi++) {
			RA.erase(RA.find(RE[REi].second));
		}
		for (; RBi < RB.size() && RB[RBi].first <= HX[i];
				 RBi++) {
			RA.insert(RB[RBi].second);
		}
	}
	// cout << Z << '\n';
	RF(i, 1, HY.size()) {
		LL p{-1}, c{0};
		for (auto &j : CA) {
			if (j.first > p) {
				c++;
			}
			p = max(p, j.second);
		}
		Z += (HY[i] - HY[i - 1]) * 2 * c;
		// cout << HY[i - 1] << ' ' << HY[i] << ' ' << c << '\n';
		for (; CEi < CE.size() && CE[CEi].first <= HY[i];
				 CEi++) {
			CA.erase(CA.find(CE[CEi].second));
		}
		for (; CBi < CB.size() && CB[CBi].first <= HY[i];
				 CBi++) {
			CA.insert(CB[CBi].second);
		}
	}
	cout << Z << '\n';
	// cout << CBi << ' ' << CEi << ' ' << RBi << ' ' << REi
	// 		 << '\n';

	return 0;
}