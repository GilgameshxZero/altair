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
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N) {
			cin >> B[i];
		}
		set<LL> splits;
		splits.insert(0);
		splits.insert(N);
		LL ans{0};
		RF(i, 29, -1) {
			vector<LL> newSplits;
			bool possible{true};
			for (auto j{splits.begin()}; j != splits.end(); j++) {
				if (*j == N) {
					break;
				}
				LL p2{*next(j) - 1}, k1, k2;
				for (k1 = *j;; k1++) {
					if (p2 <= k1) {
						break;
					}
					if ((A[k1] & (1LL << i)) > 0) {
						swap(A[k1--], A[p2--]);
					}
				}
				while (k1 < *next(j) && (A[k1] & (1LL << i)) == 0) {
					k1++;
				}
				p2 = *next(j) - 1;
				for (k2 = *j;; k2++) {
					if (p2 <= k2) {
						break;
					}
					if ((B[k2] & (1LL << i)) == 0) {
						swap(B[k2--], B[p2--]);
					}
				}
				while (k2 < *next(j) && (B[k2] & (1LL << i)) > 0) {
					k2++;
				}
				if (k1 != k2) {
					possible = false;
					break;
				}
				newSplits.push_back(k1);
			}
			if (possible) {
				RF(j, 0, newSplits.size()) {
					splits.insert(newSplits[j]);
				}
				ans += (1LL << i);
			}
		}
		cout << ans << '\n';
	}

	return 0;
}
