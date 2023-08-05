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
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N);
		LL low{0}, high, mid;
		RF(i, 0, N) {
			cin >> A[i];
			low = max(low, A[i]);
		}
		high = low + 100000000 + 1;
		while (low + 1 < high) {
			mid = (low + high) / 2;
			bool ofail{true};
			RF(i, 0, N) {
				bool fail{true};
				LL Y{0};
				RF(j, i, N) {
					if (A[j] >= mid - (j - i)) {
						fail = false;
						break;
					}
					Y += (mid - (j - i)) - A[j];
				}
				if (!fail && Y <= K) {
					ofail = false;
					break;
				}
			}
			if (ofail) {
				high = mid;
			} else {
				low = mid;
			}
		}
		cout << low << '\n';
	}

	return 0;
}
