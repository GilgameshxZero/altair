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
		LL B{~0};
		RF(i, 0, N) {
			cin >> A[i];
			B &= A[i];
		}
		if (B == 0) {
			LL Z{0};
			B = ~0;
			RF(i, 0, N) {
				B &= A[i];
				if (B == 0) {
					B = ~0;
					Z++;
				}
			}
			Z += B == 0;
			cout << Z << '\n';
		} else {
			cout << "1\n";
		}
	}

	return 0;
}
