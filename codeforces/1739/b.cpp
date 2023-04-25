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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> D(N);
		RF(i, 0, N) {
			cin >> D[i];
		}

		vector<LL> A(N);
		A[0] = D[0];
		bool fail{false};
		RF(i, 1, N) {
			A[i] = A[i - 1] + D[i];
			if (D[i] != 0 && A[i - 1] >= D[i]) {
				fail = true;
				break;
			}
		}
		if (fail) {
			cout << -1 << '\n';
		} else {
			RF(i, 0, N) {
				cout << A[i] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
