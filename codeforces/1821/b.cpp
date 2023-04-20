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
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		LL neql{N}, neqh{0};
		RF(i, 0, N) {
			cin >> B[i];
			if (B[i] != A[i]) {
				neql = min(neql, i);
				neqh = max(neqh, i);
			}
		}
		for (; neql > 0; neql--) {
			if (B[neql - 1] > B[neql]) {
				break;
			}
		}
		for (; neqh < N - 1; neqh++) {
			if (B[neqh + 1] < B[neqh]) {
				break;
			}
		}
		cout << neql + 1 << ' ' << neqh + 1 << '\n';
	}

	return 0;
}
