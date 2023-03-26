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
		LL M;
		cin >> M;

		unordered_map<LL, LL> fpd;
		RF(i, 0, M) {
			LL N;
			cin >> N;
			RF(j, 0, N) {
				LL A;
				cin >> A;
				fpd[A] = i;
			}
		}

		vector<LL> ans(M, -1);
		for (auto &i : fpd) {
			if (ans[i.second] == -1) {
				ans[i.second] = i.first;
			}
		}

		bool possible{true};
		RF(i, 0, M) {
			possible &= ans[i] != -1;
		}
		if (!possible) {
			cout << -1 << '\n';
		} else {
			RF(i, 0, M) {
				cout << ans[i] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
