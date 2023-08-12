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
		LL N;
		cin >> N;
		map<LL, LL> A;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			A[x]++;
		}
		if (A.size() == 1) {
			cout << -1 << '\n';
			continue;
		}
		cout << N - A.rbegin()->second << ' ' << A.rbegin()->second << '\n';
		while (A.size() > 1) {
			RF(i, 0, A.begin()->second) {
				cout << A.begin()->first << ' ';
			}
			A.erase(A.begin());
		}
		cout << '\n';
		RF(i, 0, A.begin()->second) {
			cout << A.begin()->first << ' ';
		}
		cout << '\n';
	}

	return 0;
}
