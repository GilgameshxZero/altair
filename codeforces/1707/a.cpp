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
		LL N, Q;
		cin >> N >> Q;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		string Z(N, '0');
		LL Y{0};
		RF(i, N - 1, -1) {
			if (Q > 0 && A[i] >= Y + 1) {
				Y++;
				Q--;
				Z[i] = '1';
			} else if (A[i] <= Y) {
				Z[i] = '1';
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
