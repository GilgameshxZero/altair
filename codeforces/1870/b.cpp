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
		LL N, M;
		cin >> N >> M;
		vector<LL> A(N);
		vector<LL> a(31);
		RF(i, 0, N) {
			cin >> A[i];
			RF(j, 0, 31) {
				a[j] = a[j] ^ ((A[i] >> j) & 1LL);
			}
		}
		LL low{LLONG_MAX / 2}, high{0};
		vector<LL> B(M);
		RF(i, 0, M) {
			cin >> B[i];
		}
		LL b{0};
		RF(i, 0, M) {
			b |= B[i];
		}
		if (N % 2 == 0) {
			LL low{0};
			RF(i, 0, 31) {
				if ((b >> i) & 1) {
				} else {
					low |= (a[i] << i);
				}
			}
			cout << low << ' ';
			LL high{0};
			RF(i, 0, N) {
				high ^= A[i];
			}
			cout << high << '\n';
		} else {
			LL low{0};
			RF(i, 0, N) {
				low ^= A[i];
			}
			cout << low << ' ';
			LL high{0};
			RF(i, 0, 31) {
				if ((b >> i) & 1) {
					high |= (1LL << i);
				} else {
					high |= (a[i] << i);
				}
			}
			cout << high << '\n';
		}
	}

	return 0;
}
