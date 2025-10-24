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
		vector<LL> A(N + 1);
		RF(i, 0, N + 1) {
			cin >> A[i];
		}
		if (N == 1) {
			cout << 1 << '\n';
			continue;
		}
		bool fail{false};
		RF(i, 1, N) {
			if (A[i] == -1 || A[i] == 0 || A[i] == i) {
				continue;
			}
			if (A[i] > N) {
				fail = true;
				break;
			}
			if (A[A[i]] == -1) {
				A[A[i]] = i;
			}
			if (A[A[i]] == 0 || A[A[i]] != i) {
				fail = true;
				break;
			}
		}
		if (fail) {
			cout << 0 << '\n';
			continue;
		}
		vector<LL> Z(N + 1);
		LL F{A[1] == -1}, FP{1};
		Z[0] = 1;
		Z[1] = A[1] == -1 ? 2 : 1;
		RF(i, 2, N + 1) {
			if (A[i] == -1) {
				Z[i] = (Z[i - 1] + (i == N ? 0 : Z[i - 1]) + F * FP) % 1000000007;
				F++;
				FP = Z[i - 1];
			} else {
				Z[i] = Z[i - 1];
			}
		}
		cout << Z[N] << '\n';
	}
}
