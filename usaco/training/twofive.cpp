/*
ID: yangchess1
PROG: twofive
LANG: C++
*/

// #define ONLINE_JUDGE

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

LL Z{0};

void count(string &s, bitset<26> &c, LL i) {
	if (i == 10) {
		// cout << s << '\n';
		Z++;
		return;
	}

	char req{'a' - 1};
	if (i % 5 != 0) {
		req = max(req, s[i - 1]);
	}
	if (i >= 5) {
		req = max(req, s[i - 5]);
	}

	RF(j, req - 'a' + 1, 26) {
		if (!c[j]) {
			continue;
		}
		s[i] = j + 'a';
		c[j] = false;
		count(s, c, i + 1);
		c[j] = true;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#ifdef ONLINE_JUDGE
	std::freopen("twofive.in", "r", stdin);
	std::freopen("twofive.out", "w", stdout);
#endif

	string s(25, '_');
	bitset<26> c;
	c.set();
	count(s, c, 0);
	cout << Z << '\n';
	return 0;

	char C;
	cin >> C;
	if (C == 'N') {
		LL N;
		cin >> N;
	} else {
		string W;
		cin >> W;
	}

	return 0;
}
