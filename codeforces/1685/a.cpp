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
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		reverse(A.begin(), A.end());
		if (N % 2 == 1) {
			cout << "NO\n";
			continue;
		}
		bool fail{A[0] <= A[N / 2] || A[N / 2 - 1] <= A[N - 1]};
		RF(i, 0, N / 2 - 1) {
			fail |= A[i + 1] <= A[i + N / 2];
		}
		if (fail) {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
		RF(i, 0, N / 2) {
			if (i % 2 == 0) {
				cout << A[i] << ' ';
			} else {
				cout << A[i + N / 2] << ' ';
			}
		}
		RF(i, N / 2 - 1, -1) {
			if (i % 2 == 1) {
				cout << A[i] << ' ';
			} else {
				cout << A[i + N / 2] << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}
