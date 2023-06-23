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
		string L, R;
		cin >> L >> R;
		if (L.length() < R.length()) {
			swap(L, R);
		}
		if (L.length() == R.length()) {
			reverse(L.begin(), L.end());
			reverse(R.begin(), R.end());
			while (!L.empty() && L.back() == R.back()) {
				L.pop_back();
				R.pop_back();
			}
			reverse(L.begin(), L.end());
			reverse(R.begin(), R.end());
			cout << (R.empty() ? 0 : R[0] - L[0] + (R.length() - 1) * 9) << '\n';
		} else {
			LL sum{0};
			RF(i, 0, L.length() - R.length()) {
				sum += L[i] - '0';
			}
			cout << max(R.length() * 9 + sum, 9 * (L.length() - 1) + L[0] - '1')
					 << '\n';
		}
	}

	return 0;
}
