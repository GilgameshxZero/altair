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
		vector<LL> A(N + 1);
		RF(i, 1, N + 1) {
			cin >> A[i];
		}
		A[0] = 0;
		sort(A.begin(), A.end());
		vector<LL> P(N + 1);
		P[0] = 0;
		RF(i, 1, N + 1) {
			P[i] = P[i - 1] + A[i];
		}
		LL Z{P.back()};
		RF(i, 1, N + 1) {
			LL low{1}, high{min((i - 1 + K - 1) / K, N - i) + 1}, mid[2];
			while (low + 2 < high) {
				mid[0] = (low * 2 + high) / 3;
				mid[1] = (low + high * 2) / 3;
				LL res[2];
				RF(j, 0, 2) {
					LL l[4];
					l[0] = min(i - 1, K * mid[j]);
					l[1] = i - 1 - l[0];
					l[2] = 1 + mid[j];
					l[3] = N - i - mid[j];
					res[j] = (l[0] + l[2]) * A[i] + (P[N] - P[N - l[3]]) +
						(P[i - 1] - P[i - 1 - l[1]]);
				}
				if (res[0] <= res[1]) {
					low = mid[0];
				} else {
					high = mid[1];
				}
			}
			mid[0] = low;
			mid[1] = low + 1;
			LL res[2]{0, 0};
			RF(j, mid[0] < high ? 0 : 1, mid[1] < high ? 2 : 1) {
				LL l[4];
				l[0] = min(i - 1, K * mid[j]);
				l[1] = i - 1 - l[0];
				l[2] = 1 + mid[j];
				l[3] = N - i - mid[j];
				res[j] = (l[0] + l[2]) * A[i] + (P[N] - P[N - l[3]]) +
					(P[i - 1] - P[i - 1 - l[1]]);
			}
			Z = max(Z, max(res[0], res[1]));
		}
		cout << Z << '\n';
	}

	return 0;
}
