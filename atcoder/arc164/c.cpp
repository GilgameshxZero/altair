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

	LL N;
	cin >> N;
	multiset<LL> S[2];
	LL B{0};
	RF(i, 0, N) {
		LL a, b;
		cin >> a >> b;
		B += min(a, b);
		S[a > b].insert(abs(a - b));
	}
	while (!S[0].empty() || !S[1].empty()) {
		if (!S[1].empty()) {
			S[0].insert(*S[1].rbegin());
			S[1].erase(prev(S[1].end()));
		} else {
			for (auto &i : S[0]) {
				B += i;
			}
			break;
		}

		if (!S[1].empty()) {
			B += *S[1].rbegin();
			S[1].erase(prev(S[1].end()));
		} else {
			S[0].erase(S[0].begin());
		}
	}

	cout << B;
	return 0;
}
