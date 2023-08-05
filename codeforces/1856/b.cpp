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
		vector<LL> A(N), B(N);
		LL R{0};
		RF(i, 0, N) {
			cin >> A[i];
			B[i] = A[i] == 1 ? 2 : 1;
			R += A[i] - B[i];
		}
		if (N == 1) {
			cout << "NO\n";
		} else if (R < 0) {
			cout << "NO\n";
		} else if (R == 0) {
			cout << "YES\n";
		} else if (R >= 2) {
			cout << "YES\n";
		} else {
			bool fail{true};
			RF(i, 0, N) {
				if (B[i] + 1 != A[i]) {
					fail = false;
					break;
				}
			}
			cout << (fail ? "NO" : "YES") << '\n';
		}
	}

	return 0;
}
