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
		vector<LL> Z(N);
		Z[0] = 1;
		LL Y{2};
		cout << "1 ";
		RF(i, 1, N) {
			LL s{A[i] - A[i - 1] - 1};
			if (s == i) {
				Z[i] = Y++;
			} else {
				Z[i] = Z[i - 1 - s];
			}
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
