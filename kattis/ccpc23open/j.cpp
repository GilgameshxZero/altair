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

	LL N;
	cin >> N;
	LD D;
	cin >> D;

	LD argans{1000};
	string ans;
	RF(i, 0, N) {
		string S;
		LD V, R;
		cin >> S >> V >> R;
		if (R < argans) {
			argans = R;
			ans = S;
		}
	}
	cout << ans;

	return 0;
}
