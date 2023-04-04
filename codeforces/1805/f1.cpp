#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

namespace Rain::Algorithm {
	// Most significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t mostSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_clzll)
		return 8 * sizeof(unsigned long long) - __builtin_clzll(x) - 1;
#endif
#endif
		for (std::size_t bit{8 * sizeof(Integer) - 1};
				 bit != std::numeric_limits<std::size_t>::max();
				 bit--) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Least significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t leastSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_ctzll)
		return __builtin_ctzll(x);
#endif
#endif
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Count of 1-bits in unsigned integral types of at most long long in size.
	template <typename Integer>
	inline std::size_t bitPopcount(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_popcountll)
		return __builtin_popcountll(x);
#endif
#endif
		std::size_t count{0};
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			count += !!(x & (static_cast<Integer>(1) << bit));
		}
		return count;
	}
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;

	vector<LL> A(N), B(N);
	RF(i, 0, N) {
		cin >> A[i];
	}

	LL shift{0}, MOD{1000000007};
	while (N > 1) {
		sort(A.begin(), A.begin() + N);
		LL low{A[0] + A[1] - 1}, high{A[N - 2] + A[N - 1]}, mid;
		while (low + 1 < high) {
			mid = (low + high) / 2;
			LL cnt{0};
			RF(i, 0, N - 1) {
				cnt += upper_bound(A.begin() + i + 1, A.begin() + N, mid - A[i]) -
					(A.begin() + i + 1);
			}
			if (cnt >= N - 1) {
				high = mid;
			} else {
				low = mid;
			}
		}

		LL N2{0};
		RF(i, 0, N - 1) {
			RF(j, i + 1, N) {
				if (A[i] + A[j] >= high) {
					break;
				}
				if (N2 == N - 1) {
					break;
				}
				B[N2++] = A[i] + A[j];
			}
			if (N2 == N - 1) {
				break;
			}
		}
		while (N2 < N - 1) {
			B[N2++] = high;
		}
		shift = (shift * 2 + B[0]) % MOD;
		RF(i, N2 - 1, -1) {
			B[i] -= B[0];
		}
		swap(A, B);
		N--;
	}
	cout << ((A[0] % MOD) + shift) % MOD;
	return 0;
}
