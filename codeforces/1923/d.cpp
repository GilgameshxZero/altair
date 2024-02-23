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
		vector<LL> A(N + 2);
		A[0] = A.back() = 0;
		RF(i, 1, N + 1) {
			cin >> A[i];
		}
		vector<LL> B(A);
		RF(i, 1, N + 2) {
			B[i] += B[i - 1];
		}
		vector<LL> C;
		C.push_back(0);
		RF(i, 1, N + 1) {
			if (A[i] != A[i - 1]) {
				C.push_back(i);
			}
		}
		C.push_back(N + 1);

		RF(i, 1, N + 1) {
			LL Z{LLONG_MAX};

			LL lo{1}, hi{i}, md;
			while (lo + 1 < hi) {
				md = (lo + hi) / 2;
				if (B[i - 1] - B[md - 1] > A[i]) {
					lo = md;
				} else {
					hi = md;
				}
			}

			if (B[i - 1] - B[lo - 1] > A[i]) {
				if (i - lo > 1) {
					LL nx{upper_bound(C.begin(), C.end(), lo) - C.begin()}, cr{nx - 1};
					if (C[nx] >= i) {
						lo = C[cr] - 1;
					}
				}
				if (lo > 0) {
					Z = min(Z, i - lo);
				}
			}

			lo = i;
			hi = N;
			while (lo + 1 < hi) {
				md = (lo + hi) / 2;
				if (B[md] - B[i] > A[i]) {
					hi = md;
				} else {
					lo = md;
				}
			}

			if (B[hi] - B[i] > A[i]) {
				if (hi - i > 1) {
					LL nx{upper_bound(C.begin(), C.end(), hi) - C.begin()}, cr{nx - 1};
					if (C[cr] <= i + 1) {
						hi = C[nx];
					}
				}
				if (hi <= N) {
					Z = min(Z, hi - i);
				}
			}

			cout << (Z == LLONG_MAX ? -1 : Z) << ' ';
		}
		cout << '\n';
	}

	return 0;
}
