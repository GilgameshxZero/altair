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
		vector<pair<LL, LL>> A(N), B;
		RF(i, 0, N) {
			cin >> A[i].first;
			A[i].second = i;
		}
		sort(A.begin(), A.end());
		B = A;
		RF(i, 1, N) {
			B[i].first = B[i].first + B[i - 1].first;
		}
		vector<LL> Z(N, -1);
		RF(i, N - 1, -1) {
			LL nextI =
				upper_bound(A.begin(), A.end(), make_pair(B[i].first, LLONG_MAX)) -
				A.begin() - 1;
			if (nextI == i) {
				Z[A[i].second] = i;
			} else {
				Z[A[i].second] = Z[A[nextI].second];
			}
		}
		RF(i, 0, N) {
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
