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
		LL N, K;
		cin >> N >> K;
		vector<pair<LL, LL>> A(N + 1);
		A[0] = {0, 0};
		RF(i, 1, N + 1) {
			cin >> A[i].second;
		}
		RF(i, 1, N + 1) {
			cin >> A[i].first;
			A[i].first = abs(A[i].first);
		}
		sort(A.begin(), A.end());
		LL carry{0};
		bool fail{false};
		RF(i, 1, N + 1) {
			carry += K * (A[i].first - A[i - 1].first);
			carry -= A[i].second;
			if (carry < 0) {
				fail = true;
			}
		}
		if (fail) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}

	return 0;
}
