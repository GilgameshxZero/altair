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
		LL N;
		cin >> N;
		array<vector<LL>, 3> A;
		RF(i, 0, 3) {
			A[i].resize(N);
			RF(j, 0, N) {
				cin >> A[i][j];
			}
		}
		array<LL, 2> Y;
		RF(i, 0, 2) {
			Y[i] = 0;
			RF(j, 0, N) {
				bool F{false};
				RF(k, 0, N) {
					if (A[i][k] >= A[i + 1][(j + k) % N]) {
						F = true;
						break;
					}
				}
				Y[i] += !F;
			}
		}
		cout << N * Y[0] * Y[1] << '\n';
	}

	return 0;
}
