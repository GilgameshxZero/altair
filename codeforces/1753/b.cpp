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

	LL N, X;
	cin >> N >> X;

	vector<LL> cnt(X + 1);
	RF(i, 0, N) {
		LL A;
		cin >> A;
		cnt[A]++;
	}
	RF(i, 1, X) {
		cnt[i + 1] += cnt[i] / (i + 1);
		cnt[i] %= i + 1;
	}

	bool possible{true};
	RF(i, 1, X) {
		possible &= cnt[i] == 0;
	}
	cout << (possible ? "Yes" : "No") << '\n';

	return 0;
}
