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

	LL N, Q;
	cin >> N >> Q;
	vector<LL> A(N), B(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	RF(i, 1, N - 1) {
		if (A[i] <= A[i - 1] && A[i + 1] <= A[i]) {
			B[i] = 1;
		}
	}
	B[0] = A[0] <= A[1];
	B[N - 1] = A[N - 1] <= A[N - 2];
	RF(i, 1, N) {
		B[i] += B[i - 1];
	}
	RF(i, 0, Q) {
		LL L, R;
		cin >> L >> R;
		L--;
		R--;
		if (L == R) {
			cout << 1 << '\n';
		} else if (L + 1 == R) {
			cout << 2 << '\n';
		} else {
			cout << R - L + 1 - (B[R - 1] - B[L]) << '\n';
		}
	}

	return 0;
}
