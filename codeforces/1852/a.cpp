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
		map<LL, LL> A;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			A[x] = i;
		}
		A[LLONG_MAX / 2] = N;
		LL low{1}, high{100000000000}, mid;
		while (low + 1 < high) {
			// if (low == 12873) {
			// 	LL Z{0};
			// }
			mid = (low + high) / 2;
			bool removed{false};
			LL rank{mid};
			RF(i, 0, K) {
				auto j{A.lower_bound(rank)};
				if (j->first == rank) {
					removed = true;
					j++;
				}
				rank -= j->second;
			}
			if (rank == 0) {
				low = mid + 1;
			} else if (rank == 1) {
				if (removed) {
					high = mid;
				} else {
					low = mid;
					break;
				}
			} else {
				high = mid;
			}
		}
		cout << low << '\n';
	}

	return 0;
}
