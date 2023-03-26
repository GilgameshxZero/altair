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
		string S;
		cin >> S;

		LL ans{0};
		vector<LL> F(2 * N, -1);
		RF(i, 2 * N - 2, -1) {
			if (S[i] == ')') {
				continue;
			}
			LL cur{i + 1};
			while (S[cur] == '(') {
				cur = 1 + F[cur];
			}
			F[i] = cur;
			if (cur == 2 * N - 1 || cur < 2 * N - 1 && S[cur + 1] == ')') {
				ans++;
			}
		}
		cout << ans << '\n';
	}

	return 0;
}
