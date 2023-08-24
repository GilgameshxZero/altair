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

bitset<1000001> P;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL W, F, N;
		cin >> W >> F >> N;
		vector<LL> S(N);
		LL SS{0};
		RF(i, 0, N) {
			cin >> S[i];
			SS += S[i];
		}
		sort(S.begin(), S.end());

		LL low{0}, high{1000000}, mid;
		while (low + 1 < high) {
			mid = (low + high) / 2;
			LL M[2]{mid * W, mid * F};
			if (M[0] > M[1]) {
				swap(M[0], M[1]);
			}

			P.reset();
			P[0] = true;
			LL ss{SS}, upper{0LL}, lower{0LL};
			RF(i, 0, N) {
				RF(j, lower, upper + 1) {
					if (P[j] && j + S[i] <= M[0]) {
						P[j + S[i]] = true;
						upper = max(upper, j + S[i]);
					}
				}
				ss -= S[i];
				lower = max(0LL, upper - ss);
			}

			if (SS - upper <= M[1]) {
				high = mid;
			} else {
				low = mid;
			}
		}
		cout << high << '\n';
	}

	return 0;
}
