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

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		vector<LL> P, NP;
		LL sP{0}, sN{0};
		RF(i, 0, N) {
			LL X;
			cin >> X;
			if (X >= 0) {
				sP += X;
				P.push_back(X);
			} else {
				sN += X;
				NP.push_back(X);
			}
		}
		sort(P.begin(), P.end());
		sort(NP.begin(), NP.end());
		reverse(P.begin(), P.end());
		if (P.empty()) {
			cout << "Yes\n";
			continue;
		}
		if (NP.empty()) {
			cout << "No\n";
			continue;
		}
		LL B{P[0] - NP[0]};
		if (sP > -sN + B) {
			cout << "No" << '\n';
			continue;
		}

		LL cur{0}, p1{0}, p2{0};
		vector<LL> ans(N);
		RF(i, 0, N) {
			if (p1 >= P.size() || p2 < NP.size() && -NP[p2] <= cur) {
				ans[i] = NP[p2];
				cur += NP[p2++];
			} else {
				ans[i] = P[p1];
				cur += P[p1++];
			}
		}
		cout << "Yes\n";
		RF(i, 0, N) {
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
