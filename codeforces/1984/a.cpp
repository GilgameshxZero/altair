#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

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
		if (A[0] == A.back()) {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
		if (A[0] == A[1]) {
			cout << "R";
			RF(i, 1, N) {
				cout << "B";
			}
			cout << '\n';
		} else {
			RF(i, 1, N) {
				cout << "B";
			}
			cout << "R";
			cout << '\n';
		}
	}

	return 0;
}
