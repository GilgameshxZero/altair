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
		string S;
		cin >> N >> S;
		vector<LL> A(N), B(N), C(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		if (S.back() == '0') {
			B.back() = 0;
			C.back() = -LLONG_MAX / 2;
		} else {
			B.back() = A.back();
			C.back() = 0;
		}
		RF(i, N - 2, -1) {
			if (S[i] == '0') {
				B[i] = max(B[i + 1], C[i + 1] + A[i]);
				C[i] = -LLONG_MAX / 2;
			} else {
				B[i] = A[i] + B[i + 1];
				C[i] = max(B[i + 1], C[i + 1] + A[i]);
			}
		}
		cout << B[0] << '\n';
	}

	return 0;
}
