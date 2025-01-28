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
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N - 1) {
			LL B{min(A[i], A[i + 1])};
			A[i] -= B;
			A[i + 1] -= B;
		}
		vector<LL> B(A);
		sort(B.begin(), B.end());
		if (A == B) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}
