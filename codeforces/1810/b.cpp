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
		LL N;
		cin >> N;
		vector<LL> ans;
		bool possible{true};
		while (N != 1) {
			if (N % 4 == 1) {
				N++;
				N /= 2;
				ans.push_back(1);
			} else if (N % 4 == 3) {
				N--;
				N /= 2;
				ans.push_back(2);
			} else {
				possible = false;
				break;
			}
		}
		if (!possible) {
			cout << "-1\n";
		} else {
			reverse(ans.begin(), ans.end());
			cout << ans.size() << '\n';
			RF(i, 0, ans.size()) {
				cout << ans[i] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
