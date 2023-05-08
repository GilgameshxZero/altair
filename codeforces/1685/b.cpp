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
		LL A, B, C, D;
		string S;
		cin >> A >> B >> C >> D >> S;
		LL cA{0}, cB{0};
		RF(i, 0, S.length()) {
			cA += S[i] == 'A';
			cB += S[i] == 'B';
		}
		if (A + C + D != cA || B + D + C != cB) {
			cout << "NO\n";
			continue;
		}

		vector<LL> X[2][2];
		LL I{0};
		S.push_back(S.back());
		RF(i, 1, S.length()) {
			if (S[i] == S[i - 1]) {
				X[S[I] - 'A'][S[i - 1] - 'A'].push_back((i - I) / 2);
				I = i;
			}
		}
		S.pop_back();

		I = 0;
		sort(X[0][1].begin(), X[0][1].end());
		for (auto &i : X[0][1]) {
			if (C >= i) {
				C -= i;
			} else {
				I += i - 1;
			}
		}
		sort(X[1][0].begin(), X[1][0].end());
		for (auto &i : X[1][0]) {
			if (D >= i) {
				D -= i;
			} else {
				I += i - 1;
			}
		}
		for (auto &i : X[0][0]) {
			I += i;
		}
		for (auto &i : X[1][1]) {
			I += i;
		}
		if (I >= C + D) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}
