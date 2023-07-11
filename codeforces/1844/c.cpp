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

		if (N == 1) {
			cout << A[0] << '\n';
			continue;
		}

		LL Z{-LLONG_MAX / 2};
		RF(i, 0, N) {
			Z = max(Z, A[i]);
		}
		bool aneg{true};
		RF(i, 0, N) {
			if (A[i] >= 0) {
				aneg = false;
				break;
			}
		}
		if (aneg) {
			cout << Z << '\n';
			continue;
		}

		vector<LL> B[2];
		B[0].resize(N);
		B[1].resize(N);
		B[0][0] = 0;
		B[1][0] = A[0];
		RF(i, 1, N) {
			B[0][i] = max(B[0][i - 1], B[1][i - 1]);
			B[1][i] = A[i] + B[0][i - 1];
		}

		cout << max(B[0].back(), B[1].back()) << '\n';
	}

	return 0;
}
