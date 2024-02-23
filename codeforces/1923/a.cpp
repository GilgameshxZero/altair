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
		LL N, C{0};
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
			C += A[i];
		}
		LL lA{0};
		RF(i, 0, N) {
			if (A[i] == 1) {
				lA = i;
				break;
			}
		}
		LL Z{0};
		RF(i, N - 1, -1) {
			if (A[i] == 1) {
				if (C == i - lA + 1) {
					break;
				}
				A[i] = 0;
				RF(j, i - 1, -1) {
					if (A[j] == 0) {
						A[j] = 1;
						Z++;
						break;
					}
				}
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
