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
		string S;
		cin >> S;

		array<LL, 10> freq;
		freq.fill(0);
		RF(i, 0, 4) {
			freq[S[i] - '0']++;
		}
		vector<LL> ff;
		RF(i, 0, 10) {
			ff.push_back(freq[i]);
		}
		sort(ff.begin(), ff.end());
		if (ff.back() == 4) {
			cout << -1 << '\n';
		} else if (ff.back() == 3) {
			cout << 6 << '\n';
		} else {
			cout << 4 << '\n';
		}
	}

	return 0;
}
