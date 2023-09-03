#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		string S;
		cin >> S;
		LL sorted{0}, z{0};
		vector<LL> down;
		bool fail{false};
		RF(i, 0, S.size()) {
			if (S[i] == '+') {
				z++;
			} else if (S[i] == '-') {
				z--;
				if (!down.empty() && down.back() >= z) {
					down.pop_back();
				}
				sorted = min(sorted, z - 1);
			} else if (S[i] == '0') {
				if (z <= 1) {
					fail = true;
					break;
				}
				if (!down.empty() && down.back() == z - 1) {
					continue;
				}
				down.push_back(z - 1);
				if (down.back() <= sorted) {
					fail = true;
					break;
				}
			} else if (S[i] == '1') {
				sorted = z - 1;
				if (!down.empty() && sorted >= down.back()) {
					fail = true;
					break;
				}
			}
		}
		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
