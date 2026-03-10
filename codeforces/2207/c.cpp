#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N, H;
		cin >> N >> H;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		LL Z{0};
		vector<LL> B(N), C(N);
		RF(i, 0, N) {
			B[i] = A[i] + 1;
			RF(j, i + 1, N) {
				B[j] = max(B[j - 1], A[j] + 1);
			}
			RF(j, i - 1, -1) {
				B[j] = max(B[j + 1], A[j] + 1);
			}
			RF(j, 0, N) {
				C[i] += H + 1 - B[j];
			}
		}
		RF(i, 0, N) {
			LL mhx{i};
			Z = max(Z, C[i]);
			RF(j, i + 1, N) {
				if (A[j] > A[mhx]) {
					mhx = j;
				}
				Z = max(Z, C[i] + C[j] - C[mhx]);
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
