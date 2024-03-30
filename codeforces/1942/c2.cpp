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
		LL N, X, Y;
		cin >> N >> X >> Y;
		LL R{N};
		vector<LL> A(X);
		RF(i, 0, X) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		LL Z{0}, F{0};
		vector<LL> P;
		RF(i, 0, X - 1) {
			if (A[i + 1] - A[i] == 2) {
				Z++;
			} else if (A[i + 1] - A[i] > 2) {
				LL x{A[i + 1] - A[i] - 1};
				if (x % 2 == 0) {
					F += x / 2;
				} else {
					P.push_back(x / 2 - 1);
				}
			}
			R -= A[i + 1] - A[i] - 1;
		}
		if (A[0] + N - A[X - 1] == 2) {
			Z++;
		} else if (A[0] + N - A[X - 1] > 2) {
			LL x{A[0] + N - A[X - 1] - 1};
			if (x % 2 == 0) {
				F += x / 2;
			} else {
				P.push_back(x / 2 - 1);
			}
		}
		R -= A[0] + N - A[X - 1] - 1;

		sort(P.begin(), P.end());
		RF(i, 0, P.size()) {
			if (P[i] + 1 <= Y) {
				Y -= P[i] + 1;
				Z += 3 + P[i] * 2;
			} else {
				Z += Y * 2;
				Y = 0;
				break;
			}
		}
		Z += 2 * min(Y, F);
		cout << Z + R - 2 << '\n';
	}

	return 0;
}
