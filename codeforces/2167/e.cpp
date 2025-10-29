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
		LL N, K, X;
		cin >> N >> K >> X;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());

		LL low{0}, high{X + 1}, mid;
		while (low + 1 < high) {
			mid = (low + high) / 2;
			LL z{max(0LL, A[0] - mid + 1)};
			for (LL i{0}; i < N - 1; i++) {
				z += max(0LL, A[i + 1] - A[i] - mid * 2 + 1);
			}
			z += max(0LL, X - (A.back() + mid) + 1);
			if (z >= K) {
				low = mid;
			} else {
				high = mid;
			}
		}

		if (low == 0) {
			RF(i, 0, K) {
				cout << i << ' ';
			}
			cout << '\n';
			continue;
		}

		mid = low;
		vector<LL> Z;
		RF(i, 0, max(0LL, A[i] - mid + 1)) {
			Z.push_back(i);
			if (Z.size() == K) {
				break;
			}
		}
		RF(i, 0, N - 1) {
			for (LL j{A[i] + mid}; j <= A[i + 1] - mid; j++) {
				Z.push_back(j);
				if (Z.size() == K) {
					break;
				}
			}
			if (Z.size() == K) {
				break;
			}
		}
		RF(i, 0, max(0LL, X - (A.back() + mid) + 1)) {
			Z.push_back(X - i);
			if (Z.size() == K) {
				break;
			}
		}
		RF(i, 0, K) {
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
