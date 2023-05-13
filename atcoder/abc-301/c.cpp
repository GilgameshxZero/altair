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

	string S, T;
	cin >> S >> T;

	array<LL, 128> cS, cT;
	cS.fill(0);
	cT.fill(0);
	RF(i, 0, S.length()) {
		cS[S[i]]++;
		cT[T[i]]++;
	}

	bool fail{false};
	unordered_set<char> Y{'a', 't', 'c', 'o', 'd', 'e', 'r'};
	RF(i, 'a', 'z' + 1) {
		if (Y.count(i)) {
			continue;
		}
		fail |= cS[i] != cT[i];
	}
	for (auto &i : Y) {
		if (cS[i] > cT[i]) {
			cT['@'] -= cS[i] - cT[i];
		} else {
			cS['@'] -= cT[i] - cS[i];
		}
	}
	fail |= cS['@'] < 0 || cT['@'] < 0;

	cout << (fail ? "No" : "Yes");
	return 0;
}
