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

#pragma hdrstop	 // ------------------------------------------------------------

LL const CS{1000000000000}, CK{CS + 1};

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		string S;
		cin >> S;

		char prev{'0'};
		LL c0{0}, c1{0};
		// vector<LL> runs(1, 0);
		RF(i, 0, S.length()) {
			c0 += S[i] == '0';
			c1 += S[i] == '1';
			// if (prev != S[i]) {
			// 	prev = S[i];
			// 	runs.push_back(1);
			// } else {
			// 	runs.back()++;
			// }
		}

		// LL f0{runs[0]}, f1{runs.size() % 2 == 0 ? runs.back() : 0},
		// 	ans{min((c0 - f0) * CK, (c1 - f1) * CK)};
		// if (runs.size() >= 3) {
		// 	LL s0{runs[1]},
		// 		s1{runs.size() % 2 == 0 ? runs[runs.size() - 2] : runs.back()},
		// 		t0{runs[2]},
		// 		t1{
		// 			runs.size() % 2 == 0 ? runs[runs.size() - 3] : runs[runs.size() -
		// 2]}; 	if (s0 == 1 && t0 >= 1) { 		ans = min(ans, (c0 - f0 - 1) * CK +
		// CS);
		// 	}
		// 	if (s1 == 1 && t1 >= 1) {
		// 		ans = min(ans, (c1 - f1 - 1) * CK + CS);
		// 	}
		// }

		LL ans{LLONG_MAX}, cum0{0};
		ans = min(ans, CK * c0);
		RF(i, 0, S.length()) {
			cum0 += S[i] == '0';
			if (i + 1 < S.length() && S[i] == '1' && S[i + 1] == '0') {
				ans = min(ans, CS + CK * (c0 - cum0 - 1 + i + 1 - cum0 - 1));
			}
			ans = min(ans, CK * (c0 - cum0 + i + 1 - cum0));
		}
		cout << ans << '\n';
	}

	return 0;
}
