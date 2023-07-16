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

// inline LL fastForward(LL S, LL N) {
// 	if (N <= 0) {
// 		return S;
// 	}
// 	if (S % 10 == 0) {
// 		return S;
// 	}
// 	if (S % 2 == 1) {
// 		return fastForward(S + S % 10, N - 1);
// 	}
// 	if (N < 4) {
// 		return fastForward(S + S % 10, N - 1);
// 	}
// 	return fastForward(S + 20 * (N / 4), N % 4);
// }

LL const B{1};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL S, K;
		cin >> S >> K;

		LL Z{0};
		if (K < 15) {
			RF(i, 0, K) {
				Z = max(Z, S * (K - i));
				S += S % 10;
			}
			cout << Z << '\n';
			continue;
		}

		if (S % 10 == 0 || S % 10 == 5) {
			cout << max(S * K, (S + S % 10) * (K - 1)) << '\n';
			continue;
		}

		Z = S * K;
		S += S % 10;
		K--;

		LL s{S}, k{K}, best;
		RF(i, 0, 4) {
			best = max(0LL, min(k / 4, (5 * k - s) / 40));
			// Z = max(Z, (s + 20 * best) * (k - best * 4));
			// best++;
			// Z = max(Z, (s + 20 * best) * (k - best * 4));
			RF(j, max(0LL, best - B), min(k / 4, best + B) + 1) {
				Z = max(Z, (s + 20 * j) * (k - j * 4));
			}
			s += s % 10;
			k--;
		}
		cout << Z << '\n';

		// LL low{0}, high{K};
		// // while (low + 100 < high) {
		// // 	LL mid[2]{(2 * low + high) / 3, (low + 2 * high) / 3};
		// // 	LL res[2]{0, 0};
		// // 	RF(i, mid[0] - 2, mid[0] + 3) {
		// // 		res[0] += fastForward(S, i) * (K - i);
		// // 	}
		// // 	RF(i, mid[1] - 2, mid[1] + 3) {
		// // 		res[1] += fastForward(S, i) * (K - i);
		// // 	}
		// // 	if (res[0] <= res[1]) {
		// // 		low = mid[0];
		// // 	} else {
		// // 		high = mid[1];
		// // 	}
		// // }
		// low = high = (5 * K - S) / 10;
		// LL Z{0}, b{max((low - B), 0LL)}, j{fastForward(S, b)};
		// RF(i, b, min(high + B, K) + 1) {
		// 	// RF(i, low, high + 1) {
		// 	Z = max(Z, j * (K - i));
		// 	j += j % 10;
		// }
		// cout << Z << '\n';
	}

	return 0;
}
