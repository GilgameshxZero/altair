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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL A, B, C;
	cin >> A >> B >> C;
	LL a{A}, b{B};
	LL T = bitPopcount(C), X, Y;
	if (T > A + B || (A + B - T) % 2 != 0) {
		cout << -1;
	} else {
		LL D{0};
		while (A + B > T) {
			A--;
			B--;
			D++;
		}
		if (A < 0 || B < 0) {
			cout << -1;
			return 0;
		}
		RF(i, 0, 61) {
			if (bitPopcount(C >> i) == A) {
				X = (C >> i) << i;
				Y = C - X;
				break;
			}
		}
		RF(i, 0, 60) {
			if (D == 0) {
				break;
			}
			if (!(C & (1LL << i))) {
				D--;
				X |= 1LL << i;
				Y |= 1LL << i;
			}
		}
		if (D != 0 || bitPopcount(X) != a || bitPopcount(Y) != b || (X ^ Y) != C) {
			cout << -1;
		} else {
			cout << X << ' ' << Y;
		}
	}
	return 0;
}
